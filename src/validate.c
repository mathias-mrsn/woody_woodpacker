#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "elf.h"
#include "stored_file.h"

static inline int32_t
_is_magic_number_valid (uint8_t * e_ident)
{
    if (memcmp(e_ident, (uint8_t[4]){EI_MAG0, EI_MAG1, EI_MAG2, EI_MAG3}, 4)) {
        write(STDERR_FILENO, "_is_magic_number_valid(): invalid magic number.", 47);
        return (1);
    }
    return (0);
}

static inline int32_t
_is_bit_valid (uint8_t * e_ident)
{
    if (!(e_ident[EI_CLASS] == 1 || e_ident[EI_CLASS] == 2)) {
        write(STDERR_FILENO, "is_bit_valid(): invalid bit format.\n", 36);
        return (1);
    }
#ifdef COMPILATION_DEBUG
    printf("debug: the executable is %d bits.", (e_ident[EI_CLASS] * 32));
#endif
    return (0);
}

static inline int32_t
_is_endian_valid (uint8_t * e_ident)
{
    if (!(e_ident[EI_DATA] == 1 || e_ident[EI_DATA] == 2)) {
        write(STDERR_FILENO, "is_bit_valid(): invalid endian format.\n", 39);
        return (1);
    }
#ifdef COMPILATION_DEBUG
    const char * bits[3] = {"", "little", "big"};
    printf("debug: the executable is %s endian.", bits[e_ident[EI_DATA]]);
#endif
    return (0);
}

static inline int32_t
_is_version_valid (uint8_t * e_ident)
{
    if (!(e_ident[EI_VERSION] == 1)) {
        write(STDERR_FILENO, "is_version_valid(): invalid version.\n", 37);
        return (1);
    }
#ifdef COMPILATION_DEBUG
    printf("debug: the executable version is %d.", e_ident[EI_VERSION]);
#endif
    return (0);
}

static inline int32_t
_is_os_valid (uint8_t * e_ident)
{
    if (!(e_ident[EI_VERSION] >= 0x0 && e_ident[EI_VERSION] <= 0x12)) {
        write(STDERR_FILENO, "is_os_valid(): invalid os.\n", 27);
        return (1);
    }
#ifdef COMPILATION_DEBUG
    const char * os[0x12] = {"System V", "HP=UX", "NetBSD", "Linux", "GNU Hurd",
        "Solaris", "AIX", "IRIX", "FreeBSD", "Tru64", "Novell Modesto", "OpenBSD",
        "OpenVMS", "NonStop Kernel", "AROS", "FenixOS", "Nuxi CloudABI",
        "Stratus Tech OpenVOS"};
    printf("debug: the executable os is %s.", os[e_ident[EI_VERSION]]);
#endif
    return (0);
}

uint8_t *
validate_ident (const STORED_FILE * sf)
{
    const void * ptr = sfat(sf, 0, EI_NIDENT);
    if (ptr == NULL) {
        write(2, "validate_ident(): invalid ELF header file too small.\n", 53); 
        return (NULL);
    }

    uint8_t * e_ident;
    if ((e_ident = (uint8_t*)malloc(EI_NIDENT)) == NULL) {
        perror("malloc()");
        return (NULL);
    }

    memcpy(e_ident, sf->ptr, EI_NIDENT);
    if (_is_magic_number_valid(e_ident) || _is_bit_valid(e_ident) ||
        _is_endian_valid(e_ident) || _is_version_valid(e_ident) ||
        _is_os_valid(e_ident))
    {
        free(e_ident);
        return (NULL);
    }
    
    return (e_ident);
}
