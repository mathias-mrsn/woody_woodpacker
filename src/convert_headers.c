#include "exploit.h"

ELF32_FORMAT *convert64_32(ELF64_FORMAT *src)
{
    ELF32_FORMAT *dest;
    if (!(dest = xmalloc(sizeof(ELF32_FORMAT))))
        return NULL;
    if (!(dest->e_h = xmalloc(sizeof(Elf32_Ehdr))))
        return free_elf32_struct(dest);
    if (!(dest->p_h = xmalloc(sizeof(Elf32_Phdr) * src->e_h->e_phnum)))
        return free_elf32_struct(dest);
    if (!(dest->s_h = xmalloc(sizeof(Elf32_Shdr) * src->e_h->e_shnum)))
        return free_elf32_struct(dest);
    (dest->e_h)->e_ehsize = (src->e_h)->e_ehsize;
    (dest->e_h)->e_entry = (src->e_h)->e_entry;
    (dest->e_h)->e_flags = (src->e_h)->e_flags;
    for (int i = 0; (src->e_h)->e_ident[i]; i++)
        (dest->e_h)->e_ident[i] = (src->e_h)->e_ident[i];
    (dest->e_h)->e_machine = (src->e_h)->e_machine;
    (dest->e_h)->e_phentsize = (src->e_h)->e_phentsize;
    (dest->e_h)->e_phnum = (src->e_h)->e_phnum;
    (dest->e_h)->e_phoff = (src->e_h)->e_phoff;
    (dest->e_h)->e_shentsize = (src->e_h)->e_shentsize;
    (dest->e_h)->e_shnum = (src->e_h)->e_shnum;
    (dest->e_h)->e_shoff = (src->e_h)->e_shoff;
    (dest->e_h)->e_shstrndx = (src->e_h)->e_shstrndx;
    (dest->e_h)->e_type = (src->e_h)->e_type;
    (dest->e_h)->e_version = (src->e_h)->e_version;
    for (int i = 0; i < (dest->e_h)->e_phnum; i++)
    {
        dest->p_h[i].p_align = src->p_h[i].p_align;
        dest->p_h[i].p_filesz = src->p_h[i].p_filesz;
        dest->p_h[i].p_flags = src->p_h[i].p_flags;
        dest->p_h[i].p_memsz = src->p_h[i].p_memsz;
        dest->p_h[i].p_offset = src->p_h[i].p_offset;
        dest->p_h[i].p_paddr = src->p_h[i].p_paddr;
        dest->p_h[i].p_type = src->p_h[i].p_type;
        dest->p_h[i].p_vaddr = src->p_h[i].p_vaddr;
    }
    for (int i = 0; i < (dest->e_h)->e_shnum; i++)
    {
        dest->s_h[i].sh_addr = src->s_h[i].sh_addr;
        dest->s_h[i].sh_addralign = src->s_h[i].sh_addralign;
        dest->s_h[i].sh_entsize = src->s_h[i].sh_entsize;
        dest->s_h[i].sh_flags = src->s_h[i].sh_flags;
        dest->s_h[i].sh_info = src->s_h[i].sh_info;
        dest->s_h[i].sh_link = src->s_h[i].sh_link;
        dest->s_h[i].sh_name = src->s_h[i].sh_name;
        dest->s_h[i].sh_offset = src->s_h[i].sh_offset;
        dest->s_h[i].sh_size = src->s_h[i].sh_size;
        dest->s_h[i].sh_type = src->s_h[i].sh_type;
    }
    return dest;
}
ELF64_FORMAT *convert32_64(const ELF32_FORMAT *src)
{
    printf("filesz = %u\n", src->p_h[3].p_filesz);
    ELF64_FORMAT *dest;
    if (!(dest = xmalloc(sizeof(ELF64_FORMAT))))
        return NULL;
    if (!(dest->e_h = xmalloc(sizeof(Elf64_Ehdr))))
        return free_elf64_struct(dest);
    if (!(dest->p_h = xmalloc(sizeof(Elf64_Phdr) * src->e_h->e_phnum)))
        return free_elf64_struct(dest);
    if (!(dest->s_h = xmalloc(sizeof(Elf64_Shdr) * src->e_h->e_shnum)))
        return free_elf64_struct(dest);
    (dest->e_h)->e_ehsize = (src->e_h)->e_ehsize;
    (dest->e_h)->e_entry = (src->e_h)->e_entry;
    (dest->e_h)->e_flags = (src->e_h)->e_flags;
    for (int i = 0; (src->e_h)->e_ident[i]; i++)
        (dest->e_h)->e_ident[i] = (src->e_h)->e_ident[i];
    (dest->e_h)->e_machine = (src->e_h)->e_machine;
    (dest->e_h)->e_phentsize = (src->e_h)->e_phentsize;
    (dest->e_h)->e_phnum = (src->e_h)->e_phnum;
    (dest->e_h)->e_phoff = (src->e_h)->e_phoff;
    (dest->e_h)->e_shentsize = (src->e_h)->e_shentsize;
    (dest->e_h)->e_shnum = (src->e_h)->e_shnum;
    (dest->e_h)->e_shoff = (src->e_h)->e_shoff;
    (dest->e_h)->e_shstrndx = (src->e_h)->e_shstrndx;
    (dest->e_h)->e_type = (src->e_h)->e_type;
    (dest->e_h)->e_version = (src->e_h)->e_version;
    for (int i = 0; i < (dest->e_h)->e_phnum; i++)
    {
        dest->p_h[i].p_align = src->p_h[i].p_align;
        dest->p_h[i].p_filesz = src->p_h[i].p_filesz;
        dest->p_h[i].p_flags = src->p_h[i].p_flags;
        dest->p_h[i].p_memsz = src->p_h[i].p_memsz;
        dest->p_h[i].p_offset = src->p_h[i].p_offset;
        dest->p_h[i].p_paddr = src->p_h[i].p_paddr;
        dest->p_h[i].p_type = src->p_h[i].p_type;
        dest->p_h[i].p_vaddr = src->p_h[i].p_vaddr;
    }
    for (int i = 0; i < (dest->e_h)->e_shnum; i++)
    {
        dest->s_h[i].sh_addr = src->s_h[i].sh_addr;
        dest->s_h[i].sh_addralign = src->s_h[i].sh_addralign;
        dest->s_h[i].sh_entsize = src->s_h[i].sh_entsize;
        dest->s_h[i].sh_flags = src->s_h[i].sh_flags;
        dest->s_h[i].sh_info = src->s_h[i].sh_info;
        dest->s_h[i].sh_link = src->s_h[i].sh_link;
        dest->s_h[i].sh_name = src->s_h[i].sh_name;
        dest->s_h[i].sh_offset = src->s_h[i].sh_offset;
        dest->s_h[i].sh_size = src->s_h[i].sh_size;
        dest->s_h[i].sh_type = src->s_h[i].sh_type;
    }
    return dest;
}