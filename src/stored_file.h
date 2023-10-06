#ifndef STORED_FILE_H
#define STORED_FILE_H

#include <stdio.h>
#include <sys/cdefs.h>

enum {
    SF_UNUSED = 1 << 0x0,
    SF_OPEN = 1 << 0x1,
    SF_CLOSE = 1 << 0x2,

    SF_READ = 1 << 0x3,
    SF_WRITE = 1 << 0x4
};

typedef struct __sSTORED_FILE
{
    void*   ptr;
    int     fd;
    size_t size;

    const char *_name;
    int     _flags;
} STORED_FILE;


STORED_FILE *
sfopen (const char *,
        const int);

int
sfclose  (STORED_FILE*);

void *
sfat (const STORED_FILE *,
      const off_t,
      const size_t);

#ifdef COMPILATION_DEBUG
extern void
sf_display_data (const STORED_FILE *);
#else
static inline void
sf_display_data (__unused const STORED_FILE * sf) {}
#endif /* COMPOLATION_DEBUG */

#endif /* STORED_FILE_H */
