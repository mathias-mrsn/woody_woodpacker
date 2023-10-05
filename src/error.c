
#include <stdio.h>

void
show_usage ( const char* str )
{
    fprintf(stderr, "Error: %s\n", str);
    fprintf(stderr, "Usage: woody <ELF_file>\n");
    fprintf(stderr, "Description: This program takes an ELF file as input.\n");
}

