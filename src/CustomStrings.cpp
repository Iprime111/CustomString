#include "CustomStrings.h"
#include "CustomAssert.h"

int puts_custom(const char *str){
    custom_assert (str != NULL, pointer_is_null, EOF);

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
    custom_assert (str != NULL, pointer_is_null, NULL);

    while (*str != ch && *str != '\0')
        str++;

    if(*str == '\0')
        return NULL;

    return (char *)str;
}

size_t strlen_custom (const char *str){
    custom_assert (str != NULL, pointer_is_null, 0);

    size_t len = 0;

    while (*str != '\0'){
        len++;
        str++;
    }

    return len;
}

char *strcpy_custom (char *dst, const char *src){
    custom_assert (dst != NULL,  pointer_is_null,        NULL);
    custom_assert (src != NULL,  pointer_is_null,        NULL);
    custom_assert (dst != src,   not_enough_pointers,    NULL);

    char* dst_ret = dst;

    while (*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }

    *dst = *src;

    return dst_ret;
}

char *strncpy_custom (char *dst, const char *src, size_t sz){
    custom_assert (dst != NULL,  pointer_is_null,        NULL);
    custom_assert (src != NULL,  pointer_is_null,        NULL);
    custom_assert (dst != src,   not_enough_pointers,    NULL);

    char* dst_ret = dst;

    size_t n_copy = 0;

    while (*src != '\0' && n_copy < sz){
        *dst = *src;
        dst++;
        src++;
        n_copy++;
    }

    while (n_copy < sz){
        *dst = '\0';
        dst++;
        n_copy++;
    }

    return dst_ret;
}

char *strcat_custom (char *dst, const char *src){
    custom_assert (dst != NULL,  pointer_is_null,        NULL);
    custom_assert (src != NULL,  pointer_is_null,        NULL);
    custom_assert (dst != src,   not_enough_pointers,    NULL);

    char* dst_ret = dst;

    while (*dst != '\0'){
        dst++;
    }

    strcpy_custom (dst, src);

    return dst_ret;
}

char *strncat_custom (char *dst, const char *src, size_t sz){
    custom_assert (dst != NULL,  pointer_is_null,        NULL);
    custom_assert (src != NULL,  pointer_is_null,        NULL);
    custom_assert (dst != src,   not_enough_pointers,    NULL);

    char* dst_ret = dst;

    while (*dst != '\0'){
        dst++;
    }

    size_t n_copy = 0;

    while (*src != '\0' && n_copy < sz){
        *dst = *src;
        dst++;
        src++;
        n_copy++;
    }

    *dst = '\0';

    return dst_ret;
}

char *fgets_custom (char *str, int size, FILE *stream){
    custom_assert (str != NULL,     pointer_is_null,        NULL);
    custom_assert (stream != NULL,  pointer_is_null,        NULL);

    char *str_ret = str;
    int cur_read = 0;
    int cur_ch = 0;

    while (cur_read < size - 1){
        cur_ch = getc(stream);

        if(ferror(stream))
            return NULL;

        if (cur_ch == EOF){
            if(cur_read == 0)
                return NULL;

            *str = '\0';
            return str_ret;
        }

        if (cur_ch == '\n'){
            *str = '\n';
            *(str + 1) = '\0';
            return str_ret;
        }

        *str = (char)cur_ch;

        str++;
        cur_read++;
    }

    *str = '\0';
    return str_ret;
}

char *strdup_custom (const char *str){
    custom_assert(str != NULL, pointer_is_null, NULL);

    size_t len = strlen_custom (str);

    char *new_str = (char *) malloc (sizeof(char) * (len + 1));

    if (new_str == NULL)
        return NULL;

    return strcpy_custom (new_str, str);
}

ssize_t getline_custom (char **lineptr, size_t *sz, FILE *stream){
    custom_assert (sz != NULL,       pointer_is_null, -1);
    custom_assert (stream != NULL,   pointer_is_null, -1);

    if(*lineptr == NULL){
        *sz = DEFAULT_BUFFER_SIZE;
        *lineptr = (char*) malloc (sizeof (char) * (*sz));

        custom_assert (*lineptr != NULL, pointer_is_null, -1);
    }

    char *buf_ptr = *lineptr;

    int cur_ch = getc (stream);
    size_t written_symbols = 0;

    while (cur_ch != '\n' && cur_ch != EOF){
        custom_assert (!ferror (stream), file_reading_error, -1);

        if (written_symbols + 2 >= *sz){
            *sz += ADDITIONAL_BUFFER_SIZE;
            *lineptr = (char *) realloc (*lineptr, *sz);
        }

        *buf_ptr = (char) cur_ch;
        written_symbols++;

        cur_ch = getc (stream);
        buf_ptr++;
    }

    if (cur_ch == '\n'){
        *buf_ptr = '\n';
        written_symbols++;

        *(buf_ptr + 1) = '\0';
    }else{
        *buf_ptr = '\0';
    }

    return (ssize_t) written_symbols;
}

char *strstr_custom (const char *haystack, const char *needle){
    custom_assert (haystack != NULL,    pointer_is_null,        NULL);
    custom_assert (needle != NULL,      pointer_is_null,        NULL);
    custom_assert (haystack != needle,  not_enough_pointers,    NULL);

    bool found_substr = false;
    bool found_substr_begin = false;
    const char *needle_begin = needle;
    const char *last_substr_begin = NULL;

    while (!found_substr && *haystack != '\0'){
        if (!found_substr_begin)
            needle = needle_begin;

        if (*needle == '\0'){
            found_substr = true;
            break;
        }

        if (*needle == *haystack){
            if (!found_substr_begin){
                last_substr_begin = haystack;
            }

            found_substr_begin = true;
            needle++;
        }else{
            if(*haystack == *needle_begin){
                needle = needle_begin + 1;
                last_substr_begin = haystack;
            }else{
                found_substr_begin = false;
                last_substr_begin = NULL;
            }
        }

        haystack++;
    }

    return (char *) last_substr_begin;
}
