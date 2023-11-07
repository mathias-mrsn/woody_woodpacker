#include "exploit.h"

bool is_sstrip(void *e_h, size_t fsize, int class)
{
    if (class == ELFCLASS64)
        return (((((Elf64_Ehdr *)e_h)->e_shoff + (sizeof(Elf64_Shdr) * ((Elf64_Ehdr *)e_h)->e_shnum)) > fsize) || ((Elf64_Ehdr *)e_h)->e_shoff == 0);
    else if (class == ELFCLASS32)
        return (((((Elf32_Ehdr *)e_h)->e_shoff + (sizeof(Elf32_Shdr) * ((Elf32_Ehdr *)e_h)->e_shnum)) > fsize) || ((Elf32_Ehdr *)e_h)->e_shoff == 0);
    else
        return true;
}

void h_cpy32(Elf64_Ehdr *dest, Elf32_Ehdr *src)
{
    (dest)->e_ehsize = (src)->e_ehsize;
    (dest)->e_entry = (src)->e_entry;
    (dest)->e_flags = (src)->e_flags;
    for (int i = 0; (src)->e_ident[i]; i++)
        (dest)->e_ident[i] = (src)->e_ident[i];
    (dest)->e_machine = (src)->e_machine;
    (dest)->e_phentsize = (src)->e_phentsize;
    (dest)->e_phnum = (src)->e_phnum;
    (dest)->e_phoff = (src)->e_phoff;
    (dest)->e_shentsize = (src)->e_shentsize;
    (dest)->e_shnum = (src)->e_shnum;
    (dest)->e_shoff = (src)->e_shoff;
    (dest)->e_shstrndx = (src)->e_shstrndx;
    (dest)->e_type = (src)->e_type;
    (dest)->e_version = (src)->e_version;
}
void h_cpy64(Elf32_Ehdr *dest, Elf64_Ehdr *src)
{
    (dest)->e_ehsize = (src)->e_ehsize;
    (dest)->e_entry = (src)->e_entry;
    (dest)->e_flags = (src)->e_flags;
    for (int i = 0; (src)->e_ident[i]; i++)
        (dest)->e_ident[i] = (src)->e_ident[i];
    (dest)->e_machine = (src)->e_machine;
    (dest)->e_phentsize = (src)->e_phentsize;
    (dest)->e_phnum = (src)->e_phnum;
    (dest)->e_phoff = (src)->e_phoff;
    (dest)->e_shentsize = (src)->e_shentsize;
    (dest)->e_shnum = (src)->e_shnum;
    (dest)->e_shoff = (src)->e_shoff;
    (dest)->e_shstrndx = (src)->e_shstrndx;
    (dest)->e_type = (src)->e_type;
    (dest)->e_version = (src)->e_version;
}
void sh_cpy32(Elf64_Shdr *dest, Elf32_Shdr *src, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        dest[i].sh_addr = src[i].sh_addr;
        dest[i].sh_addralign = src[i].sh_addralign;
        dest[i].sh_entsize = src[i].sh_entsize;
        dest[i].sh_flags = src[i].sh_flags;
        dest[i].sh_info = src[i].sh_info;
        dest[i].sh_link = src[i].sh_link;
        dest[i].sh_name = src[i].sh_name;
        dest[i].sh_offset = src[i].sh_offset;
        dest[i].sh_size = src[i].sh_size;
        dest[i].sh_type = src[i].sh_type;
    }
}
void sh_cpy64(Elf32_Shdr *dest, Elf64_Shdr *src, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        dest[i].sh_addr = src[i].sh_addr;
        dest[i].sh_addralign = src[i].sh_addralign;
        dest[i].sh_entsize = src[i].sh_entsize;
        dest[i].sh_flags = src[i].sh_flags;
        dest[i].sh_info = src[i].sh_info;
        dest[i].sh_link = src[i].sh_link;
        dest[i].sh_name = src[i].sh_name;
        dest[i].sh_offset = src[i].sh_offset;
        dest[i].sh_size = src[i].sh_size;
        dest[i].sh_type = src[i].sh_type;
    }
}

void ph_cpy32(Elf64_Phdr *dest, Elf32_Phdr *src, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        dest[i].p_align = src[i].p_align;
        dest[i].p_filesz = src[i].p_filesz;
        dest[i].p_flags = src[i].p_flags;
        dest[i].p_memsz = src[i].p_memsz;
        dest[i].p_offset = src[i].p_offset;
        dest[i].p_paddr = src[i].p_paddr;
        dest[i].p_type = src[i].p_type;
        dest[i].p_vaddr = src[i].p_vaddr;
    }
}

void ph_cpy64(Elf32_Phdr *dest, Elf64_Phdr *src, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        dest[i].p_align = src[i].p_align;
        dest[i].p_filesz = src[i].p_filesz;
        dest[i].p_flags = src[i].p_flags;
        dest[i].p_memsz = src[i].p_memsz;
        dest[i].p_offset = src[i].p_offset;
        dest[i].p_paddr = src[i].p_paddr;
        dest[i].p_type = src[i].p_type;
        dest[i].p_vaddr = src[i].p_vaddr;
    }
}
void h_cpy(void *dest, void *src, const int dest_format, const int src_format)
{
    if (src_format == ELFCLASS32 && dest_format == ELFCLASS64)
    {
        h_cpy32((Elf64_Ehdr *)dest, (Elf32_Ehdr *)src);
    }
    if (src_format == ELFCLASS64 && dest_format == ELFCLASS32)
    {
        h_cpy64((Elf32_Ehdr *)dest, (Elf64_Ehdr *)src);
    }
}
void sh_cpy(void *dest, void *src, size_t len, const int dest_format, const int src_format)
{
    if (src_format == ELFCLASS32 && dest_format == ELFCLASS64)
    {
        sh_cpy32((Elf64_Shdr *)dest, (Elf32_Shdr *)src, len);
    }
    if (src_format == ELFCLASS64 && dest_format == ELFCLASS32)
    {
        sh_cpy64((Elf32_Shdr *)dest, (Elf64_Shdr *)src, len);
    }
}
/**
 * @param type type of the source
 */
void ph_cpy(void *dest, void *src, size_t len, int dest_format, const int src_format)
{
    if (src_format == ELFCLASS32 && dest_format == ELFCLASS64)
    {
        ph_cpy32((Elf64_Phdr *)dest, (Elf32_Phdr *)src, len);
    }
    if (src_format == ELFCLASS64 && dest_format == ELFCLASS32)
    {
        ph_cpy64((Elf32_Phdr *)dest, (Elf64_Phdr *)src, len);
    }
}

ELF32_FORMAT *convert64_32(ELF64_FORMAT *src, const STORED_FILE *sf)
{
    ELF32_FORMAT *dest;
    if (!(dest = calloc(1, sizeof(ELF32_FORMAT))))
        return NULL;
    if (!(dest->e_h = calloc(1, sizeof(Elf32_Ehdr))))
        return free_elf32_struct(dest);
    if (!(dest->p_h = calloc(1, sizeof(Elf32_Phdr) * src->e_h->e_phnum)))
        return free_elf32_struct(dest);
    if (!(dest->s_h = calloc(1, sizeof(Elf32_Shdr) * src->e_h->e_shnum)))
        return free_elf32_struct(dest);
    h_cpy(dest->e_h, src->e_h, ELFCLASS32, ELFCLASS64);
    ph_cpy(dest->p_h, src->p_h, (src->e_h)->e_phnum, ELFCLASS32, ELFCLASS64);
    if (!is_sstrip(src->e_h, sf->size, ELFCLASS64))
        sh_cpy(dest->s_h, src->s_h, (src->e_h)->e_shnum, ELFCLASS32, ELFCLASS64);
    return dest;
}
ELF64_FORMAT *convert32_64(const ELF32_FORMAT *src, const STORED_FILE *sf)
{
    ELF64_FORMAT *dest;
    if (!(dest = calloc(1, sizeof(ELF64_FORMAT))))
        return NULL;
    if (!(dest->e_h = calloc(1, sizeof(Elf64_Ehdr))))
        return free_elf64_struct(dest);
    if (!(dest->p_h = calloc(1, sizeof(Elf64_Phdr) * src->e_h->e_phnum)))
        return free_elf64_struct(dest);
    if (!(dest->s_h = calloc(1, sizeof(Elf64_Shdr) * src->e_h->e_shnum)))
        return free_elf64_struct(dest);
    h_cpy(dest->e_h, src->e_h, ELFCLASS64, ELFCLASS32);
    ph_cpy(dest->p_h, src->p_h, (src->e_h)->e_phnum, ELFCLASS64, ELFCLASS32);
    if (!is_sstrip(src->e_h, sf->size, ELFCLASS32))
        sh_cpy(dest->s_h, src->s_h, (src->e_h)->e_shnum, ELFCLASS64, ELFCLASS32);
    return dest;
}