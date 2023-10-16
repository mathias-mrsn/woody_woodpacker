#ifndef STORED_FILE_H
#define STORED_FILE_H

#include <stdio.h>
#include <stdint.h>

enum
{
    SF_UNUSED = 1 << 0x0,
    SF_OPEN = 1 << 0x1,
    SF_CLOSE = 1 << 0x2,

    SF_READ = 1 << 0x3,
    SF_WRITE = 1 << 0x4
};

/**
 * @brief A structure representing a stored file in memory.
 *
 * The STORED_FILE structure is used to represent a file that has been opened
 * and read into memory using the sfopen function. It stores information about
 * the file's contents, including a pointer to the memory-mapped data, file
 * descriptor, size, filename, and open status.
 */
typedef struct __sSTORED_FILE
{
    void *ptr;   /**< Pointer to the memory-mapped data of the file. */
    int32_t fd;  /**< File descriptor associated with the file. */
    size_t size; /**< Size of the stored file in bytes. */

    const char *_name; /**< Name of the file, typically the file path. */
    int32_t _flags;    /**< Flags indicating the file's open status. */
} STORED_FILE;

/*
 * @brief Open a file and store its contents in memory.
 *
 * This function opens a file specified by the 'file' parameter and reads its
 * contents into memory. It returns a pointer to a STORED_FILE structure
 * containing information about the opened file.
 *
 * @param file  The path to the file to be opened.
 * @param flags The file open flags, such as O_RDONLY or O_RDWR.
 *
 * @return A pointer to a dynamically allocated STORED_FILE structure on
 *         success, or NULL on failure.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       STORED_FILE structure using free() when it's no longer needed.
 * @note If an error occurs, this function prints error messages to stderr
 *       using perror().
 */
extern STORED_FILE *
sfopen(const char *,
       const int32_t);

/**
 * @brief Close a stored file and release associated resources.
 *
 * This function is used to close a stored file previously opened with `sfopen`.
 * It releases the memory mapping, closes the file descriptor, and frees the
 * memory allocated for the STORED_FILE structure.
 *
 * @param sf A pointer to the STORED_FILE structure to be closed.
 *
 * @return 0 on success, or a non-zero value on failure. A non-zero return value
 *         indicates that one or more of the cleanup operations failed.
 *
 * @note The caller should check the return value to determine if any errors
 *       occurred during the cleanup process. Error messages may be printed to
 *       stderr using perror().
 * @note After calling this function, the 'sf' pointer is no longer valid, and
 *       the memory associated with the STORED_FILE structure is freed.
 * @note It is essential to close stored files using this function to prevent
 *       resource leaks and memory mapping issues.
 */
extern int
sfclose(STORED_FILE *);

/**
 * @brief Get a pointer to a specified range within a stored file.
 *
 * This function is used to obtain a pointer to a specified range within a
 * stored file previously opened with `sfopen`. The 'offset' parameter specifies
 * the starting position within the file, and the 'len' parameter indicates the
 * length of the range to access.
 *
 * @param sf     A pointer to the STORED_FILE structure representing the file.
 * @param offset The offset, in bytes, from the beginning of the file.
 * @param len    The length, in bytes, of the range to access.
 *
 * @return A pointer to the specified range within the file, or NULL if the
 *         requested range exceeds the file's size.
 *
 * @note The caller is responsible for ensuring that the provided 'offset' and
 *       'len' values do not exceed the size of the stored file to prevent
 *       accessing out-of-bounds memory.
 * @note If the requested range is beyond the file's size, this function returns
 *       NULL and prints an error message to stderr.
 * @note The returned pointer allows read-only access to the specified file
 *       range. Any modifications to the returned data may affect the underlying
 *       file data.
 */
extern void *
sfat(const STORED_FILE *,
     const off_t,
     const size_t);

#ifdef COMPILATION_DEBUG

/*
 * @brief Display information about a stored file.
 *
 * This function is used to display information about a stored file, including its
 * filename, size, open status, and memory address. It provides a convenient way
 * to inspect the attributes of the STORED_FILE structure.
 *
 * @param sf A pointer to the STORED_FILE structure representing the file.
 *
 * @note This function does not modify the stored file or its contents; it is
 *       for informational purposes only.
 */
extern void
sf_display_data(const STORED_FILE *);

#else

static __inline void
sf_display_data(__attribute__((__unused__)) const STORED_FILE *sf) {}

#endif /* COMPOLATION_DEBUG */

#endif /* STORED_FILE_H */
