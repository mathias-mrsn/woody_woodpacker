#include "commun.h"
#include "stored_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "elf.h"
#include "unpacker.h"
#include "validate.h"
#include "asm.h"
#include "exploit.h"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        write(2, "Error: invalid argument.\nUsage: woody <ELF_file>\n", 49);
        return (EXIT_FAILURE);
    }

    STORED_FILE *sf = sfopen(av[1], SF_READ);

    // char text[] = "This is a text";
    // char key[] = "hdoyyfduishnckcxknbgbvhhdskjyteriow4321uiyrfuei3^*fyudsia^-3i^3usiao^&3*asy4*&3say43-21=8-9_sa";
    // char *cipher = malloc(100);
    // encrypt(text, 14, key, 94, cipher);

    // write(1, cipher, 14);

    sf_display_data(sf);
    if (validate_ident(sf) == ERROR)
    {
        write(2, "validate_ident(): failed.", 25);
        goto _err;
    }
    /*
    char *key = calloc(KEY_LENGTH / 8, 1);
    keygen(KEY_LENGTH / 8, key);

    // segv
    printf("the key is:");
    for (int i = 0; i < KEY_LENGTH / 8; i++)
    {
        if (i % 8 == 0)
        {
            printf("\n");
        }
        printf("0x%02x ", (char)key[i] & 0xff);
    }
    printf("\n\n");

    char text[] = "This is a text et je suis pas vraiment sur que cette fonction marche\0";
    const int text_len = strlen(text);

    printf("original text is:");
    for (int i = 0; i < text_len; i++)
    {
        if (i % 8 == 0)
        {
            printf("\n");
        }
        printf("0x%02x ", (char)text[i] & 0xff);
    }
    printf("\n\n");

    char *cipher = calloc(text_len, 1);
    encrypt(text, text_len, key, KEY_LENGTH / 8, cipher);

    printf("encrypted text is:");
    for (int i = 0; i < text_len; i++)
    {
        if (i % 8 == 0)
        {
            printf("\n");
        }
        printf("0x%02x ", (char)cipher[i] & 0xff);
    }
    printf("\n\n");

    get_unpacker(0, key, cipher, KEY_LENGTH / 8, text_len, 0);

    printf("decrypted text is:");
    for (int i = 0; i < text_len; i++)
    {
        if (i % 8 == 0)
        {
            printf("\n");
        }
        printf("0x%02x ", (char)cipher[i] & 0xff);
    }
    printf("\n\n");
    */

    if (exploit(sf))
        goto _err;

_err:
    sfclose(sf);
    return (EXIT_SUCCESS);
}
