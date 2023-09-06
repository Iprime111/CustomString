#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "Onegin.h"
#include "CustomAssert.h"

enum COMPARE_RESULT compare_chars (char first_char, char second_char){
    PushLog (4);

    if (first_char > second_char){
        RETURN GREATER;
    }

    if (first_char < second_char){
        RETURN LESS;
    }

    RETURN EQUAL;
}

void qsort_char (char *sort_string, const size_t length){
    PushLog (3);

    //printf ("%lu %p ", length, sort_string);
    //printf ("%s\n", sort_string);

    custom_assert (sort_string != NULL, pointer_is_null, (void)0);

    if (length < 2){
        RETURN ;
    }

    size_t pivot_index = (length + 1) / 2;

    char pivot = *(sort_string + pivot_index);

    char *greater_chars = (char *) calloc (length, sizeof (char));
    char *less_chars    = (char *) calloc (length, sizeof (char));

    size_t greater_chars_index = 0;
    size_t less_chars_index    = 0;

    size_t pivot_count = 0;

    for (size_t char_index = 0; char_index < length; char_index++){
        char current_char = *(sort_string + char_index);

        switch (compare_chars (current_char, pivot)){

            case GREATER:
                greater_chars [greater_chars_index] = current_char;
                greater_chars_index++;
                break;

            case EQUAL:
                pivot_count += 1;
                break;

            case LESS:
                less_chars [less_chars_index] = current_char;
                less_chars_index++;
                break;

            default:
                custom_assert (0, undefined_variable, (void)0);
                break;
        };
    }

    for (size_t index = 0; index < less_chars_index; index++){
        *(sort_string + index) = less_chars [index];
    }

    for (size_t index = less_chars_index; index < less_chars_index + pivot_count; index++){
        *(sort_string + index) = pivot;
    }

    for (size_t index = 0; index < greater_chars_index; index++){
        *(sort_string + index + less_chars_index + pivot_count) = greater_chars [index];
    }

    //printf ("%lu %lu %lu\n", less_chars_index, greater_chars_index, pivot_count);

    free (greater_chars);
    free (less_chars);

    qsort_char (sort_string,                                  less_chars_index);
    qsort_char (sort_string + less_chars_index + pivot_count, greater_chars_index);
}

void delete_punctuation (char *line){
    PushLog (3);

    while (*line != '\0'){
        if (!isalpha (*line) && !isdigit (*line)){
            *line = ' ';
        }
    }

    RETURN ;
}
