#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unpacker.h"
#include "../asm/asm.h"

uint8_t *
get_unpacker (  const void * old_start,
                const void * key,
                const void * text,
                const uint64_t key_len,
                const uint64_t text_len,
                const bool     is_64)
{
    uint8_t * unpacker = NULL;

    if (is_64 == true)
    {
        unpacker = calloc(1, UNPACKER_SIZE_64 + 100);
        if (unpacker == NULL) {
            return (NULL);
        }

        memcpy(unpacker, &decrypt_64, UNPACKER_SIZE_64);
        memcpy((unpacker + UNPACKER_SIZE_64) - OLD_START_REVERSE_OFFSET_64, &old_start, QUAD_WORD); 
        memcpy((unpacker + UNPACKER_SIZE_64) - TEXT_ADDR_REVERSE_OFFSET_64, &text, QUAD_WORD); 
        memcpy((unpacker + UNPACKER_SIZE_64) - TEXT_LEN_REVERSE_OFFSET_64, &text_len, QUAD_WORD); 
        memcpy((unpacker + UNPACKER_SIZE_64) - KEY_LEN_REVERSE_OFFSET_64, &key_len, QUAD_WORD); 
        memcpy((unpacker + UNPACKER_SIZE_64) - KEY_ADDR_REVERSE_OFFSET_64, key, KEY_LENGTH / 8);

        // memcpy((&decrypt_64 + UNPACKER_SIZE_64) - OLD_START_REVERSE_OFFSET_64, &old_start, QUAD_WORD); 
        // memcpy((&decrypt_64 + UNPACKER_SIZE_64) - TEXT_ADDR_REVERSE_OFFSET_64, &text, QUAD_WORD); 
        // memcpy((&decrypt_64 + UNPACKER_SIZE_64) - TEXT_LEN_REVERSE_OFFSET_64, &text_len, QUAD_WORD); 
        // memcpy((&decrypt_64 + UNPACKER_SIZE_64) - KEY_LEN_REVERSE_OFFSET_64, &key_len, QUAD_WORD); 
        // memcpy((&decrypt_64 + UNPACKER_SIZE_64) - KEY_ADDR_REVERSE_OFFSET_64, key, KEY_LENGTH / 8);
        //
        // decrypt_64();

        // printf("-----------------------------");
        // for(int i = 0; i < UNPACKER_SIZE_64; i++) {
        //     if (i > 0 && i % 8 == 0) {
        //         printf("\n");
        //     }
        //     printf("0x%02x ", unpacker[i]);
        // }
        // printf("-----------------------------\n");

    } else {

        unpacker = calloc(1, UNPACKER_SIZE_32 + 100);
        if (unpacker == NULL) {
            return (NULL);
        }

        const int size = UNPACKER_SIZE_32;


        printf("%d\n", size);

        memcpy(unpacker, &decrypt_32, UNPACKER_SIZE_32);
        memcpy((unpacker + UNPACKER_SIZE_32) - OLD_START_REVERSE_OFFSET_32, &old_start, DOUBLE_WORD); 
        memcpy((unpacker + UNPACKER_SIZE_32) - TEXT_ADDR_REVERSE_OFFSET_32, &text, DOUBLE_WORD); 
        memcpy((unpacker + UNPACKER_SIZE_32) - TEXT_LEN_REVERSE_OFFSET_32, &text_len, DOUBLE_WORD); 
        memcpy((unpacker + UNPACKER_SIZE_32) - KEY_ADDR_REVERSE_OFFSET_32, &key, DOUBLE_WORD);
        memcpy((unpacker + UNPACKER_SIZE_32) - KEY_LEN_REVERSE_OFFSET_32, &key_len, DOUBLE_WORD); 

        for(int i = 0; i < UNPACKER_SIZE_32; i++) {
            if (i > 0 && i % 8 == 0) {
                printf("\n");
            }
            printf("0x%02x ", unpacker[i]);
        }
        printf("\n");
    }



    return (unpacker);
}


