#ifndef ASM_H
# define ASM_H

# include <stddef.h>

/**
 * @brief Generate a key to encrypt a file.
 *
 * This function opens the /dev/urandom file on your system, reads N characters,
 * and stores them inside the ptr pointer. The number of characters read
 * depends on the key_size parameter. Finally, the /dev/urandom file is closed.
 *
 * @param key_size The number of characters to read, which will be your key size.
 *
 * @note The ptr must be allocated inside the C code; this function won't
 *       allocate the necessary memory.
 *
 * @note This function doesn't check any memory boundaries and may lead to
 *       memory errors.
 *
 */
extern void
keygen (const int key_size, void * ptr);

/**
 * @brief Encrypt text with RC4 algorithm.
 *
 * This function takes text and encrypts it using the RC4 algorithm.
 * The algorithm takes a key as a parameter with its length, and the output
 * of this encryption is stored in a pointer that must be allocated beforehand.
 *
 * @param text The text or data to encrypt.
 * @param text_len The length of the text to avoid any overflow.
 * @param key The key to encrypt the text.
 * @param key_len The length of the key.
 * @param cipher Pointer to store the output of the encryption.
 *
 * @note Every pointer must not be NULL, and the cipher must be allocated;
 *       otherwise, it may lead to memory errors and crashes.
 */
extern void 
encrypt (const char * text,
             const size_t text_len,
             const char * key,
             const size_t key_len,
             const char * cipher);

extern void
decrypt_64 (void);

extern void
decrypt_64_end (void);

extern void
decrypt_32 (void);

extern void
decrypt_32_end (void);

#endif
