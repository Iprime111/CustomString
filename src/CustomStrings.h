#ifndef CUSTOM_STRINGS
#define CUSTOM_STRINGS

#include <stdio.h>

int puts_custom(const char *str);
char *strchr_custom (const char *str, int ch);
size_t strlen_custom (const char *str);
char *strcpy_custom (char *dst, const char *src);
char *strncpy_custom (char *dst, const char *src, size_t sz);
/*char *strcat_custom (char *restrict dst, const char *restrict src);
char *strncat_custom (char *restrict dst, const char src[restrict .sz], size_t sz);
char *fgets_custom (char s[restrict .size], int size, FILE *restrict stream);
char *strdup_custom (const char *s);
ssize_t getline_custom (char **restrict lineptr, size_t *restrict n, FILE *restrict stream);*/

#endif
