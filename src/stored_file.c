/*
 * Docs:
 * https://www.youtube.com/watch?v=m7E9piHcfr4
 * */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

#include "stored_file.h"

/*
 * TODO : sfopen must be able to write new file.
 * */

STORED_FILE *
sfopen (const char *    file,
        const int32_t   flags)
{
    STORED_FILE sfile = {};

    sfile._name = file;
    sfile.fd = open(file, flags);
    if (sfile.fd < 0) {
        perror("open()");
        return (NULL);
    }

    sfile._flags = SF_OPEN;
    sfile.size = lseek(sfile.fd, 0, SEEK_END);    
    if (sfile.size < 0) {
        perror("lseek()");
        goto err;
    }
    
    sfile.ptr = mmap(NULL, sfile.size, PROT_READ, MAP_PRIVATE, sfile.fd, 0);
    if (sfile.ptr == MAP_FAILED) {
        perror("mmap()");
        goto err;
    }

    STORED_FILE * heap_sfile = NULL;

    heap_sfile = (STORED_FILE*)malloc(sizeof(STORED_FILE));
    if (heap_sfile == NULL) {
        perror("malloc()");
        goto err;
    }

    memcpy(heap_sfile, &sfile, sizeof(STORED_FILE));

    return (heap_sfile);

err:
    close(sfile.fd);
    unlink(file);

    return (NULL);
}

int32_t
sfclose (STORED_FILE* sf)
{
    int32_t r = 0;
    if (sf->_flags != SF_OPEN)
        fprintf(stderr, "sfclose(): cannot close file \'%s\'\n", sf->_name);

    r |= munmap(sf->ptr, sf->size);
    if (r < 0)
        perror("mummap()");

    r |= close(sf->fd);
    if (r < 0)
        perror("close()");

    free(sf);
    return (!!r);
}

void *
sfat (const STORED_FILE *   sf,
      const off_t           offset,
      const size_t          len)
{
    if (offset + len >= sf->size) {
        write(STDERR_FILENO, "sfat(): Failed because you re trying to reach a range of file bigger than the file.\n", 84);
        return (NULL);
    }
    return (sf->ptr + offset);
}

#ifdef COMPILATION_DEBUG

void
sf_display_data (const STORED_FILE * sf)
{
    printf("sf_display_data():\n");
    printf("\tfilename: %s\n", sf->_name);
    printf("\tsize: %lu\n", sf->size);
    printf("\tis open: %d\n", (sf->_flags == SF_OPEN));
    printf("\taddress: %p\n", sf->ptr);
}
#endif


