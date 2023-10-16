#ifndef VALIDATE_H
#define VALIDATE_H

#include "stored_file.h"
#include <stdint.h>

/**
 * @brief Validate and extract the ELF header identifier from a stored file.
 *
 * This function validates and extracts the ELF header identifier from the
 * specified stored file. The ELF header identifier is typically the first
 * 16 bytes of an ELF (Executable and Linkable Format) file.
 *
 * @param sf A pointer to the STORED_FILE structure representing the file.
 *
 * @return ERROR if check failed and SUCCESS otherwise.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       returned identifier using free() when it's no longer needed.
 */
uint32_t
validate_ident (const STORED_FILE * sf);

#endif
