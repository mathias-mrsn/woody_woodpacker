
#include "stored_file.h"
#include <stdio.h>

int
main ( int ac, char **av)
{
    if (ac != 2)
    {
        fprintf(stderr, "Error: invalid argument.\n");
        fprintf(stderr, "Usage: woody <ELF_file>\n");
        return (1);
    }
    
    STORED_FILE * sf = sfopen(av[1], SF_READ);
    sf_display_data(sf);
    sfclose(sf);
    return (0);
}
