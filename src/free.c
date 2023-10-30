#include "exploit.h"

void *free_exploit_info(EXPLOIT_INFO *info)
{
    if (info != NULL)
    {
        free(info->key_ptr);
        free(info->payload);
        free(info);
    }
    return NULL;
}
void *free_elf64_struct(ELF64_FORMAT *elf)
{
    if (elf != NULL)
    {
        free(elf->e_h);
        free(elf->p_h);
        free(elf->s_h);
        free(elf);
    }
    return NULL;
}
void *free_elf32_struct(ELF32_FORMAT *elf)
{
    if (elf != NULL)
    {
        free(elf->e_h);
        free(elf->p_h);
        free(elf->s_h);
        free(elf);
    }
    return NULL;
}