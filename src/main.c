#include "stored_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "elf.h"
#include "validate.h"
#include "asm.h"

int
main ( int ac, char **av)
{
    if (ac != 2)
    {
        write(2, "Error: invalid argument.\nUsage: woody <ELF_file>\n", 49);
        return (EXIT_FAILURE);
    }
    
    STORED_FILE * sf = sfopen(av[1], SF_READ);
   
    // char *key = malloc(1000);
    //
    // int value = 64;
    // const char * str = keygen(64, (void*)key);
    // (void)str;
//    write(1, key, 64);

    char text[] = "This is a text";
    char key[] = "hdoyyfduishnckcxknbgbvhhdskjyteriow4321uiyrfuei3^*fyudsia^-3i^3usiao^&3*asy4*&3say43-21=8-9_sa";
    char *cipher = malloc(100);
    encrypt(text, 14, key, 94, cipher);

    write(1, cipher, 14);

    sf_display_data(sf);
    uint8_t * e_ident = validate_ident(sf);   

    free(e_ident);

    sfclose(sf);
    return (EXIT_SUCCESS);
}
