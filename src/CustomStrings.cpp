#include "CustomStrings.h"
#include "CustomAssert.h"

int puts_custom(const char *str){
    PushLog (3);

    custom_assert (str != NULL, pointer_is_null, EOF);

    while (*str != '\0'){
        if (putc (*str, stdout) == EOF && ferror (stdout)){
            RETURN EOF;
        }
        str++;
    }

    if (putc ('\n', stdout) == EOF && ferror (stdout)){
        RETURN EOF;
    }

    RETURN 0;
}

char *strchr_custom (const char *str, int ch){
    PushLog (3);

    custom_assert (str != NULL, pointer_is_null, NULL);

    while (*str != ch && *str != '\0')
        str++;

    if(*str == '\0'){
        RETURN NULL;
    }

    RETURN const_cast <char *> (str);
}

size_t strlen_custom (const char *str){
    PushLog (3);

    custom_assert (str != NULL, pointer_is_null, 0);

    size_t len = 0;

    while (*str != '\0'){
        len++;
        str++;
    }

    RETURN len;
}

char *strcpy_custom (char *dst, const char *src){
    PushLog (3);

    custom_assert (dst != NULL, pointer_is_null,     NULL);
    custom_assert (src != NULL, pointer_is_null,     NULL);
    custom_assert (dst != src,  not_enough_pointers, NULL);

    char* dst_ret = dst;

    while (*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }

    *dst = *src;

    RETURN dst_ret;
}

char *strncpy_custom (char *dst, const char *src, size_t sz){
    PushLog (3);

    custom_assert (dst != NULL, pointer_is_null,     NULL);
    custom_assert (src != NULL, pointer_is_null,     NULL);
    custom_assert (dst != src,  not_enough_pointers, NULL);

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

    RETURN dst_ret;
}

char *strcat_custom (char *dst, const char *src){
    PushLog (3);

    custom_assert (dst != NULL, pointer_is_null,     NULL);
    custom_assert (src != NULL, pointer_is_null,     NULL);
    custom_assert (dst != src,  not_enough_pointers, NULL);

    char* dst_ret = dst;

    while (*dst != '\0'){
        dst++;
    }

    strcpy_custom (dst, src);

    RETURN dst_ret;
}

char *strncat_custom (char *dst, const char *src, size_t sz){
    PushLog (3);

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

    RETURN dst_ret;
}

char *fgets_custom (char *str, int size, FILE *stream){
    PushLog (3);

    custom_assert (str != NULL,    pointer_is_null, NULL);
    custom_assert (stream != NULL, pointer_is_null, NULL);

    char *str_ret = str;
    int cur_read = 0;
    int cur_ch = 0;

    while (cur_read < size - 1){
        cur_ch = getc(stream);

        if(ferror(stream)){
            RETURN NULL;
        }

        if (cur_ch == EOF){
            if(cur_read == 0){
                RETURN NULL;
            }

            *str = '\0';
            RETURN str_ret;
        }

        if (cur_ch == '\n'){
            *str = '\n';
            *(str + 1) = '\0';
            RETURN str_ret;
        }

        *str = (char)cur_ch;

        str++;
        cur_read++;
    }

    *str = '\0';
    RETURN str_ret;
}

char *strdup_custom (const char *str){
    PushLog (3);

    custom_assert(str != NULL, pointer_is_null, NULL);

    size_t len = strlen_custom (str);

    char *new_str = (char *) malloc (sizeof(char) * (len + 1));

    if (new_str == NULL){
        RETURN NULL;
    }

    RETURN strcpy_custom (new_str, str);
}

ssize_t getline_custom (char **lineptr, size_t *sz, FILE *stream){
    PushLog (3);

    custom_assert (sz != NULL,     pointer_is_null, -1);
    custom_assert (stream != NULL, pointer_is_null, -1);

    if(*lineptr == NULL){
        *sz = DEFAULT_BUFFER_SIZE;
        *lineptr = (char*) malloc (sizeof (char) * (*sz));

        custom_assert (*lineptr != NULL, pointer_is_null, -1);
    }

    char *buf_ptr = *lineptr;

    int cur_ch = getc (stream);
    size_t written_symbols = 0;

    while (cur_ch != '\n' && cur_ch != EOF){
        custom_assert (!ferror (stream), cannot_open_file, -1);

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

    RETURN (ssize_t) written_symbols;
}

char *strstr_custom_naive (const char *haystack, const char *needle){
    PushLog (3);

    custom_assert (haystack != NULL,   pointer_is_null,     NULL);
    custom_assert (needle   != NULL,   pointer_is_null,     NULL);
    custom_assert (haystack != needle, not_enough_pointers, NULL);

    bool found_substr        = false;
    bool found_substr_begin  = false;

    const char *needle_begin      = needle;
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

    RETURN const_cast <char *> (last_substr_begin);
}


char *strstr_custom (const char *haystack, const char *needle){
    PushLog (3);

    custom_assert (haystack != NULL,   pointer_is_null,     NULL);
    custom_assert (needle   != NULL,   pointer_is_null,     NULL);
    custom_assert (haystack != needle, not_enough_pointers, NULL);

    size_t needle_sz   = strlen_custom (needle);
    size_t processed_sym = 0;

    const char *haystack_begin = haystack;

    int hash = 0;
    int needle_hash = compute_needle_hash(needle);

    const char *first_occurrence = NULL;

    bool is_running = true;

    while (is_running){
        if (processed_sym < needle_sz){
            hash += *haystack;
            processed_sym++;
            haystack++;
            continue;
        }

        if (hash == needle_hash){
            first_occurrence = haystack_begin + processed_sym - needle_sz;

            if (is_substr_in_str (first_occurrence, needle, needle_sz)){
                RETURN const_cast <char *> (first_occurrence);
            }

            first_occurrence = NULL;
        }

        if (*haystack == '\0'){
            is_running = false;
        }

        hash -= *(haystack - needle_sz);
        hash += *haystack;

        processed_sym++;
        haystack++;
    }

    RETURN const_cast <char *> (first_occurrence);
}

bool is_substr_in_str (const char *str, const char* substr, size_t substr_sz){
    PushLog (4);

    custom_assert (str != NULL,    pointer_is_null,     false);
    custom_assert (substr != NULL, pointer_is_null,     false);
    custom_assert (str != substr,  not_enough_pointers, false);

    for(ssize_t i = (ssize_t) substr_sz - 1; i >= 0; i--){
        if (*(str + i) != *(substr + i)){
            RETURN false;
        }
    }

    RETURN true;
}

int compute_needle_hash (const char *needle){
    PushLog (4);

    custom_assert (needle != NULL, pointer_is_null, -1);

    int needle_hash = 0;

    while (*needle != '\0'){
        needle_hash += *needle;
        needle++;
    }

    RETURN needle_hash;
}

