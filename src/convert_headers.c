#include "convert_headers.h"

void test(STORED_FILE *sf)
{
    Elf32_Ehdr *e_h;
    Elf32_Phdr *p_h;
    Elf32_Shdr *s_h;
    // e_h = malloc(sizeof(Elf32_Ehdr));
    // p_h = malloc(sizeof(Elf32_Phdr));
    // s_h = malloc(sizeof(Elf32_Shdr));
    e_h = sf->ptr;
    s_h = sf->ptr + (e_h)->e_shoff;
    p_h = sf->ptr + (e_h)->e_phoff;
    Elf64_Ehdr *e_h64;
    Elf64_Phdr *p_h64;
    Elf64_Shdr *s_h64;
    e_h64 = malloc(sizeof(Elf64_Ehdr));
    p_h64 = malloc(sizeof(Elf64_Phdr) * e_h->e_phnum);
    s_h64 = malloc(sizeof(Elf64_Shdr));
    Elf32_Ehdr *e_h32;
    Elf32_Phdr *p_h32;
    Elf32_Shdr *s_h32;
    e_h32 = malloc(sizeof(Elf32_Ehdr));
    p_h32 = malloc(sizeof(Elf32_Phdr) * e_h->e_phnum);
    s_h32 = malloc(sizeof(Elf32_Shdr));
    e_h64->e_ehsize = e_h->e_ehsize;
    e_h64->e_entry = e_h->e_entry;
    e_h64->e_flags = e_h->e_flags;
    for (int i = 0; e_h->e_ident[i]; i++)
        e_h64->e_ident[i] = e_h->e_ident[i];
    e_h64->e_machine = e_h->e_machine;
    e_h64->e_phentsize = e_h->e_phentsize;
    e_h64->e_phnum = e_h->e_phnum;
    e_h64->e_phoff = e_h->e_phoff;
    e_h64->e_shentsize = e_h->e_shentsize;
    e_h64->e_shnum = e_h->e_shnum;
    e_h64->e_shoff = e_h->e_shoff;
    e_h64->e_shstrndx = e_h->e_shstrndx;
    e_h64->e_type = e_h->e_type;
    e_h64->e_version = e_h->e_version;

    for (int i = 0; i < e_h64->e_phnum; i++)
    {
        p_h64[i].p_align = p_h[i].p_align;
        p_h64[i].p_filesz = p_h[i].p_filesz;
        p_h64[i].p_flags = p_h[i].p_flags;
        p_h64[i].p_memsz = p_h[i].p_memsz;
        p_h64[i].p_offset = p_h[i].p_offset;
        p_h64[i].p_paddr = p_h[i].p_paddr;
        p_h64[i].p_type = p_h[i].p_type;
        p_h64[i].p_vaddr = p_h[i].p_vaddr;
        // p_h64 = heap_alloc(-86, p_h64);
        // p_h = (Elf64_Phdr *)(char *)p_h + 24;
    }
    e_h32->e_ehsize = e_h64->e_ehsize;
    e_h32->e_entry = e_h64->e_entry;
    e_h32->e_flags = e_h64->e_flags;
    for (int i = 0; e_h64->e_ident[i]; i++)
        e_h32->e_ident[i] = e_h64->e_ident[i];
    e_h32->e_machine = e_h64->e_machine;
    e_h32->e_phentsize = e_h64->e_phentsize;
    e_h32->e_phnum = e_h64->e_phnum;
    e_h32->e_phoff = e_h64->e_phoff;
    e_h32->e_shentsize = e_h64->e_shentsize;
    e_h32->e_shnum = e_h64->e_shnum;
    e_h32->e_shoff = e_h64->e_shoff;
    e_h32->e_shstrndx = e_h64->e_shstrndx;
    e_h32->e_type = e_h64->e_type;
    e_h32->e_version = e_h64->e_version;
    for (int i = 0; i < e_h->e_phnum; i++)
    {
        p_h32[i].p_align = p_h64[i].p_align;
        p_h32[i].p_filesz = p_h64[i].p_filesz;
        p_h32[i].p_flags = p_h64[i].p_flags;
        p_h32[i].p_memsz = p_h64[i].p_memsz;
        p_h32[i].p_offset = p_h64[i].p_offset;
        p_h32[i].p_paddr = p_h64[i].p_paddr;
        p_h32[i].p_type = p_h64[i].p_type;
        p_h32[i].p_vaddr = p_h64[i].p_vaddr;
    }
}

ELF32_FORMAT *convert64_32(ELF64_FORMAT *src)
{
    ELF32_FORMAT *dest;
    dest = malloc(sizeof(ELF32_FORMAT));
    dest->e_h = malloc(sizeof(Elf32_Ehdr));
    dest->p_h = malloc(sizeof(Elf32_Phdr) * src->e_h->e_phnum);
    dest->s_h = malloc(sizeof(Elf32_Shdr) * src->e_h->e_shnum);
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
    dest = malloc(sizeof(ELF64_FORMAT));
    dest->e_h = malloc(sizeof(Elf64_Ehdr));
    dest->p_h = malloc(sizeof(Elf64_Phdr) * src->e_h->e_phnum);
    dest->s_h = malloc(sizeof(Elf64_Shdr) * src->e_h->e_shnum);
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