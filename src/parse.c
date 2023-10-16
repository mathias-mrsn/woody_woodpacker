#include "exploit.h"

/*
! // TODO Section Header may not be present in an ELF file...
! The following function may crash if this is the case
*/
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int get_text_section(const STORED_FILE *sf, const ELF64_FORMAT *elf)
{
    for (int i = 0; i < ((elf->e_h)->e_shnum); i++) // find the .text header
    {
        char *res = (char *)(sf->ptr + elf->s_h[(elf->e_h)->e_shstrndx].sh_offset + elf->s_h[i].sh_name);
        //! // TODO replace with libft strcmp
        if (!strcmp(".text", (char *)(sf->ptr + elf->s_h[(elf->e_h)->e_shstrndx].sh_offset + elf->s_h[i].sh_name)))
            return i;
    }
    return -1;
}

int find_text_segment(const STORED_FILE *sf, const ELF64_FORMAT *elf, int32_t idx)
{
    for (int i = 1; i <= elf->e_h->e_phnum; i++)
    {
        if (elf->s_h[idx].sh_offset >= elf->p_h[i - 1].p_offset && elf->s_h[idx].sh_offset <= elf->p_h[i].p_offset)
            return i - 1;
    }
}