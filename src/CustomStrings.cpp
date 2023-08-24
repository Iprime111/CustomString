#include "CustomStrings.h"

int puts_custom(const char *str){
    while (*str != '\0'){
        if (putc (*str, stdout) == EOF && ferror (stdout))
            return EOF;
        str++;
    }
    if (putc ('\n', stdout) == EOF && ferror (stdout))
        return EOF;
    return 0;
}

char *strchr_custom (const char *str, int ch){
    while (*str != ch && *str != '\0')
        str++;

    if(*str == '\0')
        return NULL;

    return (char *)str;
}

size_t strlen_custom(const char *str){
    size_t len = 0;
    while(*str != '\0'){
        len++;
        str++;
    }
    return len;
}

char *strcpy_custom (char *dst, const char *src){
    char* dst_ret = dst;

    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }

    return dst_ret;
}

char *strncpy_custom (char *dst, const char *src, size_t sz);
