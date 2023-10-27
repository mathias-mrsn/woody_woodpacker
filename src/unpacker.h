#ifndef UNPACKER_H
#define UNPACKER_H

#include <stdint.h>
#include <stdbool.h>

#define UNPACKER_SIZE_64 (&decrypt_64_end - &decrypt_64)

#define UNPACKER_SIZE_32 (&decrypt_32_end - &decrypt_32)

#define DOUBLE_WORD 4
#define QUAD_WORD 8

#define OLD_START_REVERSE_OFFSET_64 64
#define TEXT_ADDR_REVERSE_OFFSET_64 56
#define TEXT_LEN_REVERSE_OFFSET_64 48
#define KEY_LEN_REVERSE_OFFSET_64 40
#define KEY_ADDR_REVERSE_OFFSET_64 32

#define OLD_START_REVERSE_OFFSET_32 62
#define TEXT_ADDR_REVERSE_OFFSET_32 56
#define TEXT_LEN_REVERSE_OFFSET_32 48
#define KEY_LEN_REVERSE_OFFSET_32 40
#define KEY_ADDR_REVERSE_OFFSET_32 32

#ifndef KEY_LENGTH
#define KEY_LENGTH 128 // in bits
#endif

/**
 * @brief Create an unpacker for decrypting data with RC4 encryption.
 *
 * This function creates an unpacker code that can be injected to autodecrypt data encrypted
 * using the RC4 encryption algorithm previously. The unpacker contains both the RC4 decryption
 * code and the necessary parameters for decryption.
 *
 * @param old_start The starting address of the original code to be decrypted.
 * @param key A pointer to the encryption key used for RC4 decryption.
 * @param text A pointer to the encrypted data to be decrypted.
 * @param key_len The length of the encryption key.
 * @param text_len The length of the encrypted data.
 * @param is_64 A boolean value specifying whether the architecture is 64-bit (true) or 32-bit (false).
 *
 * @return A pointer to the dynamically allocated unpacker code, or NULL on failure.
 *
 * @warning The caller is responsible for freeing the memory allocated for the unpacker.
 */
uint8_t *
get_unpacker(const void *,
             const void *,
             const void *,
             const uint64_t,
             const uint64_t,
             const bool);

#endif
