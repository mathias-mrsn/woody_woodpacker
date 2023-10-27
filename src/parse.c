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
    for (int i = 0; i < (elf->e_h)->e_shnum; i++) // find the .text header
    {
        //printf("text section = %s\n", (char *)(sf->ptr + elf->s_h[(elf->e_h)->e_shstrndx].sh_offset + elf->s_h[i].sh_name));
        //! // TODO replace with libft strcmp
        if (!strcmp(".text", (char *)(sf->ptr + elf->s_h[(elf->e_h)->e_shstrndx].sh_offset + elf->s_h[i].sh_name)))
            return i;
    }
    return -1;
}

int find_text_segment(const ELF64_FORMAT *elf, int32_t idx)
{
    for (int i = 1; i < (elf->e_h->e_phnum); i++)
    {
        if (elf->s_h[idx].sh_offset >= elf->p_h[i - 1].p_offset && elf->s_h[idx].sh_offset <= elf->p_h[i].p_offset)
        {
            if (((PF_X | PF_R) & elf->p_h[i - 1].p_flags) == (PF_X | PF_R))
                return i - 1;
        }
    }
    return -1;
}

int find_section_endof_segment(const ELF64_FORMAT *elf, int32_t idx)
{
    for (int i = (elf->e_h->e_shnum) - 1; i >= 1; i--)
    {
        if (elf->s_h[i].sh_offset >= (elf->p_h[idx].p_offset + elf->p_h[idx].p_filesz) && elf->s_h[i - 1].sh_offset <= (elf->p_h[idx].p_offset + elf->p_h[idx].p_filesz))
            return i - 1;
    }
    return -1;
}