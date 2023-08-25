#ifndef CUSTOM_STRINGS
#define CUSTOM_STRINGS

#include <stdio.h>
#include <stdlib.h>

const size_t DEFAULT_BUFFER_SIZE = 20;
const size_t ADDITIONAL_BUFFER_SIZE = 10;

/*!
    @brief          Writes the string str and a trailing newline to stdout
    @param[in] str  String to write
    @return         EOF if error is occuried, 0 if not
*/
int puts_custom(const char *str);

/*!
    @brief          Returns a pointer to the first occurrence of the character ch in the string str
    @param[in] str  Input string
    @param[in] ch   Character to find
    @return         A pointer to the first occurrence of the character in the string
*/
char *strchr_custom (const char *str, int ch);

/*!
    @brief          Returns lenth of the given string str
    @param[in] str  Input string
    @return         Length of the given string
*/
size_t strlen_custom (const char *str);

/*!
    @brief          Copies content of the given src string to dst string
    @param[out] dst Destination string
    @param[in] src  Source string
    @return         Pointer to the target string or NULL if error occuried
*/
char *strcpy_custom (char *dst, const char *src);

/*!
    @brief          Copies src string to dst string with limited sz size. If src length is less than sz fills left space with '\0' symbols
    @param[out] dst Destination string
    @param[in] src  Source string
    @param[in] sz   Max size of copied string
    @return         Pointer to dst string or NULL if error occuried
    @note           Do not places '\0' at the end of resulting string if src length is greater than sz
*/
char *strncpy_custom (char *dst, const char *src, size_t sz);

/*!
    @brief          Catenates the string pointed to by src, after the string pointed to by dst
    @param[out] dst Destination string
    @param[in] src  Source string
    @return         Pointer to dst buffer or NULL if error is occuried
*/
char *strcat_custom (char *dst, const char *src);

/*!
    @brief          Catenates the string contained in a null-padded fixed-size buffer str, into a string at the buffer pointed to by dst
    @param[out] dst Destination string
    @param[in] src  Source string
    @param[in] sz   Buffer size
    @return         Pointer to dst buffer or NULL if error is occuried
*/
char *strncat_custom (char *dst, const char *src, size_t sz);

/*!
    @brief              Reads size - 1 sybmbols from stream and stops when EOF or newline is found. Adds a null byte ('\0') at the end of sequence
    @param[out] str     Output buffer
    @param[in] size     Characters count
    @param[in] stream   Stream pointer
    @return             Pointer to output buffer or NULL if error is occuried
*/
char *fgets_custom (char *str, int size, FILE *stream);

/*!
    @brief          Duplicates string by creating a new bufer with malloc()
    @param[in] str  String to duplicate
    @return         Pointer to duplicated string or NULL if error is occuried
    @note           User must call 'free()' after working with allocated memory
*/
char *strdup_custom (const char *str);

/*!
    @brief Gets line from standart input and creates dynamic buffer if lineptr has NULL value
    @param[out] lineptr Pointer to pointer to input buffer
    @param[out] sz Buffer size
    @param[in] stream Stream pointer
*/
ssize_t getline_custom (char **lineptr, size_t *n, FILE *stream);

/*!
    @brief Finds the first occurrence of the substring needle in the string haystack
    @param[in] haystack Input string
    @param[in] needle Substring
    @return Pointer to the begginning of the locate substring
*/
char *strstr_custom (const char *haystack, const char *needle);

#endif
