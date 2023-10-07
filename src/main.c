#include "stored_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "elf.h"
#include "validate.h"

int
main ( int ac, char **av)
{
    if (ac != 2)
    {
        write(2, "Error: invalid argument.\nUsage: woody <ELF_file>\n", 49);
        return (EXIT_FAILURE);
    }
    
    STORED_FILE * sf = sfopen(av[1], SF_READ);
    
    sf_display_data(sf);
    validate_ident(sf);   

    sfclose(sf);
    return (EXIT_SUCCESS);
}
