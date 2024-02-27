#include "exploit.h"

/**
 *@brief - Check in the dynamics sections if FLAGS_1
 *          is set to 0x800000.
 *          Meaning that the ELF is a dynamic lib
 * @param STORED_FILE structure.
 * @param ELF64_FORMAT structure.
 * @return   1 if the flag has been found.
 *           0 otherwise.
 */
bool check_dyn_lib(const STORED_FILE *sf, ELF64_FORMAT *elf)
{
    Elf64_Off sh_offset;
    Elf64_Xword sh_size;
    for (int idx = 0; idx < elf->e_h->e_shnum; idx++)
    {
        if (elf->s_h[idx].sh_type != SHT_DYNAMIC)
            continue;
        sh_size = elf->s_h[idx].sh_size;
        if (sh_size == 0)
            continue;
        sh_offset = elf->s_h[idx].sh_offset;
        for (int inc = 0; inc < sh_size; inc += 16)
        {
            int *flag = (int *)(sf->ptr + sh_offset + inc);
            if (*flag == DT_FLAGS_1)
            {
                int *bitand = (int *)(sf->ptr + sh_offset + inc + 8);
                if ((*bitand&0x08000000) == 0)
                    return true;
            }
        }
    }
    return false;
}

bool code_cave_available(EXPLOIT_INFO *info, ELF64_FORMAT *elf)
{
    Elf64_Addr memsz_align = info->explt_p->p_memsz % 0x1000;
    if ((memsz_align + ((info->bin_arch == ELFCLASS64) ? UNPACKER_SIZE_64 : UNPACKER_SIZE_32) < 1000))
        return true;
    return false;
}
EXPLOIT_INFO_NOTE get_note_info(const STORED_FILE *sf, const ELF64_FORMAT *elf, EXPLOIT_INFO **info)
{
    EXPLOIT_INFO_NOTE tmp;
    tmp.max_addr = tmp.max_memsz = 0;
    tmp.n_p_idx = -1;
    for (int i = (elf->e_h->e_phnum) - 1; i > 0; i--)
    {
        if (elf->p_h[i].p_type == PT_NOTE)
        {
            tmp.n_p_idx = i;
            break;
        }
    }
    for (int i = (elf->e_h->e_phnum) - 1; i > 0; i--)
    {
        if (elf->p_h[i].p_vaddr + elf->p_h[i].p_memsz > tmp.max_addr)
        {
            tmp.max_addr = elf->p_h[i].p_vaddr + elf->p_h[i].p_memsz;
        }
    }
    tmp.note_vaddr = tmp.max_addr + (0x1000 - ((tmp.max_addr) % 0x1000));
    return tmp;
}

EXPLOIT_INFO *get_exploit_info(const STORED_FILE *sf, const ELF64_FORMAT *elf, EXPLOIT_INFO **info)
{

    if (!((*info) = calloc(1, sizeof(EXPLOIT_INFO))))
        return NULL;
    if (!(((*info))->key_ptr = calloc(1, KEY_LENGTH)))
        return NULL;
    keygen(KEY_LENGTH, ((*info))->key_ptr);
    (*info)->page_size = sysconf(_SC_PAGE_SIZE);
    if (((*info)->text_s_idx = get_text_section(sf, elf)) != -1)
        goto _sh_full;
    (*info)->sh_less = true;
    if ((elf->e_h->e_type & ET_DYN) == ET_DYN)
        (*info)->pie = true;
    else
        (*info)->pie = false;
    if (!((*info)->e_p_idx = find_executable_segment(elf)))
        return NULL;
_end:
    (*info)->explt_p = &(elf->p_h[(*info)->e_p_idx]);
    (*info)->old_entry = &(elf->e_h->e_entry);
    (*info)->bin_arch = elf->e_h->e_ident[EI_CLASS];
    (*info)->note = get_note_info(sf, elf, info);
    return (*info);

_sh_full:
    (*info)->e_p_idx = find_text_segment(elf, (*info)->text_s_idx);
    (*info)->e_s_idx = find_section_endof_segment(elf, (*info)->e_p_idx);
    (*info)->text_s = &(elf->s_h[(*info)->text_s_idx]);
    (*info)->explt_s = &(elf->s_h[(*info)->e_s_idx]);
    (*info)->sh_less = false;
    goto _end;
}

ELF64_FORMAT *extract_headers_from_sf(const STORED_FILE *sf, ELF64_FORMAT **elf)
{
    char *bin_arch = sf->ptr + 4;
    if (*bin_arch == ELFCLASS64)
    {
        if (!(*elf = calloc(1, sizeof(ELF64_FORMAT))))
            return NULL;
        if (!((*elf)->e_h = calloc(1, sizeof(Elf64_Ehdr))))
            return NULL;
        memcpy((*elf)->e_h, sf->ptr, sizeof(Elf64_Ehdr));
        if (!((*elf)->p_h = calloc(1, sizeof(Elf64_Phdr) * (*elf)->e_h->e_phnum)))
            return NULL;

        memcpy((*elf)->p_h, (sf->ptr + (*elf)->e_h->e_phoff), sizeof(Elf64_Phdr) * (*elf)->e_h->e_phnum);
        if ((((*elf)->e_h->e_shoff + (sizeof(Elf32_Shdr) * (*elf)->e_h->e_shnum)) > sf->size) || ((*elf)->e_h->e_shoff == 0))
            goto _end;
        if (!((*elf)->s_h = calloc(1, sizeof(Elf64_Shdr) * (*elf)->e_h->e_shnum)))
            return NULL;
        memcpy((*elf)->s_h, (sf->ptr + (*elf)->e_h->e_shoff), sizeof(Elf64_Shdr) * (*elf)->e_h->e_shnum);
    }
    else
    {
        ELF32_FORMAT *tmp;
        if (!(tmp = calloc(1, sizeof(ELF32_FORMAT))))
            return NULL;
        tmp->e_h = (Elf32_Ehdr *)sf->ptr;
        tmp->s_h = (Elf32_Shdr *)(sf->ptr + tmp->e_h->e_shoff);
        tmp->p_h = (Elf32_Phdr *)(sf->ptr + tmp->e_h->e_phoff);
        *elf = convert32_64(tmp, sf);
        free(tmp);
    }
_end:
    return *elf;
}
