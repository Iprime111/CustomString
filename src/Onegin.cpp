#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "Onegin.h"
#include "CustomAssert.h"

enum COMPARE_RESULT compare_chars (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    const char first_char  = *((const char *) first_pointer);
    const char second_char = *((const char *) second_pointer);

    if (first_char > second_char){
        RETURN GREATER;
    }

    if (first_char < second_char){
        RETURN LESS;
    }

    RETURN EQUAL;
}

enum COMPARE_RESULT compare_ints (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    const int first_int  = *((const int *) first_pointer);
    const int second_int = *((const int *) second_pointer);

    if (first_int > second_int){
        RETURN GREATER;
    }

    if (first_int < second_int){
        RETURN LESS;
    }

    RETURN EQUAL;
}

enum COMPARE_RESULT compare_strings (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    const char *first_string  = *((const char * const *) first_pointer);
    const char *second_string = *((const char * const *) second_pointer);

    while (!is_string_end (*first_string) && !is_string_end (*second_string)){

        if (is_punctuation_character (*first_string)){
            first_string++;
            continue;
        }

        if (is_punctuation_character (*second_string)){
            second_string++;
            continue;
        }

        if (*first_string > *second_string){
            RETURN GREATER;
        } else if (*first_string < *second_string){
            RETURN LESS;
        }

        first_string ++;
        second_string++;
    }

    if (!is_string_end (*first_string) && is_string_end (*second_string)){
        RETURN GREATER;
    }

    if (is_string_end (*first_string)  && !is_string_end (*second_string)){
        RETURN LESS;
    }

    RETURN EQUAL;
}

enum COMPARE_RESULT compare_strings_reverse (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    const char *first_string_begin  = *((const char * const *) first_pointer);
    const char *second_string_begin = *((const char * const *) second_pointer);

    const size_t first_string_len  = line_len (first_string_begin);
    const size_t second_string_len = line_len (second_string_begin);

    const char *first_string  = first_string_begin  + first_string_len;
    const char *second_string = second_string_begin + second_string_len;


    while (first_string != first_string_begin && second_string != second_string_begin){

        if (is_punctuation_character (*first_string)){
            first_string--;
            continue;
        }

        if (is_punctuation_character (*second_string)){
            second_string--;
            continue;
        }

        if (*first_string > *second_string){
            RETURN GREATER;
        } else if (*first_string < *second_string){
            RETURN LESS;
        }

        first_string --;
        second_string--;
    }

    if (first_string != first_string_begin && second_string == second_string_begin){
        RETURN GREATER;
    }

    if (first_string == first_string_begin && second_string != second_string_begin){
        RETURN LESS;
    }

    RETURN EQUAL;
}

size_t line_len (const char *line){
    PushLog (4);

    size_t length = 0;

    while (!is_string_end (*(line + length))){
        length++;
    }

    RETURN length;
}

bool is_punctuation_character (char ch){
    PushLog (4);

    RETURN !isalpha (ch) && !isdigit (ch);
}

bool is_string_end (char ch){
    PushLog (4);

    RETURN ch == '\n' || ch == '\0';
}

void swap_elements (void *element_1, void *element_2, size_t element_size){
    PushLog (4);

    if (element_1 == element_2){
        RETURN ;
    }

    char *element_1_char = (char *) element_1;
    char *element_2_char = (char *) element_2;

    char temp = 0;

    for (size_t byte_index = 0; byte_index < element_size; byte_index++){
        temp = *(element_1_char + byte_index);
        *(element_1_char + byte_index) = *(element_2_char + byte_index);
        *(element_2_char + byte_index) = temp;
    }

    RETURN ;
}

void qsort_custom (void *sort_array, const size_t length, enum COMPARE_RESULT (*comparator)(const void *, const void *), size_t element_size){
    PushLog (3);

    char *sort_array_char = (char *) sort_array;

    custom_assert (sort_array_char != NULL, pointer_is_null, (void)0);

    if (length < 2){
        RETURN ;
    }

    if (length == 2){
        if ((*comparator) (sort_array_char, sort_array_char + element_size) > 0){
            swap_elements (sort_array_char, sort_array_char + element_size, element_size);
        }

        RETURN ;
    }

    size_t pivot_index = (length + 1) / 2;

    swap_elements (sort_array_char + pivot_index * element_size, sort_array_char, element_size);

    pivot_index = 0;

    size_t greater_count = 0;
    size_t less_count    = 0;

    size_t pivot_count = 1;

    for (size_t index = 1; index < length; index++){
        switch ((*comparator) (sort_array_char + index * element_size,
            sort_array_char + pivot_index * element_size)){

            case GREATER:
                greater_count++;
                break;

            case EQUAL:
                swap_elements (sort_array_char + (pivot_index + pivot_count) * element_size,
                        sort_array_char + index * element_size, element_size);

                pivot_count++;
                break;

            case LESS:
                if (index == pivot_index + pivot_count){
                    swap_elements (sort_array_char + pivot_index * element_size,
                            sort_array_char + index * element_size, element_size);
                }else{
                    swap_elements (sort_array_char + pivot_index * element_size,
                            sort_array_char + (pivot_index + pivot_count) * element_size, element_size);

                    swap_elements (sort_array_char + pivot_index * element_size,
                            sort_array_char + index * element_size, element_size);
                }
                pivot_index++;
                less_count++;
                break;

            default:
                custom_assert (0, undefined_variable, (void)0);
                break;
        };
    }

    qsort_custom (sort_array_char,                                             less_count,    comparator, element_size);
    qsort_custom (sort_array_char + (less_count + pivot_count) * element_size, greater_count, comparator, element_size);
}

