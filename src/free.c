#include "exploit.h"

void *free_exploit_info(EXPLOIT_INFO *info)
{
    if (info != NULL)
    {
        (info->key_ptr) ? free(info->key_ptr) : 0;
        (info->payload) ? free(info->payload) : 0;
        free(info);
    }
    return NULL;
}
void *free_elf64_struct(ELF64_FORMAT *elf)
{
    if (elf != NULL)
    {
        (elf->e_h) ? free(elf->e_h) : 0;
        (elf->p_h) ? free(elf->p_h) : 0;
        (elf->s_h) ? free(elf->s_h) : 0;
        free(elf);
    }
    return NULL;
}
void *free_elf32_struct(ELF32_FORMAT *elf)
{
    if (elf != NULL)
    {
        (elf->e_h) ? free(elf->e_h) : 0;
        (elf->p_h) ? free(elf->p_h) : 0;
        (elf->s_h) ? free(elf->s_h) : 0;
        free(elf);
    }
    return NULL;
}