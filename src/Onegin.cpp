#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "Onegin.h"
#include "CustomAssert.h"
#include "TextTypes.h"

#define element(element_index) get_element (sort_array_char, element_index, element_size)

size_t set_pivot (char *sort_array_char, size_t length, size_t element_size);

void partition_old (char *sort_array_char, size_t length, size_t element_size, size_t *less_count, size_t *greater_count, size_t *pivot_count, compare_function_t comparator);
void hoare_partition (char *sort_array_char, size_t length, size_t element_size, size_t *less_count, size_t *greater_count, compare_function_t comparator);

inline char *get_element (char *array, size_t index, size_t element_size){
    return array + index * element_size;
}

int compare_chars (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    RETURN *((const char *) first_pointer) - *((const char *) second_pointer);
}

int compare_ints (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    RETURN *((const char *) first_pointer) - *((const char *) second_pointer);
}

int compare_lines (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    const char *first_string  = ((const TEXT_LINE*) first_pointer)-> pointer;
    const char *second_string = ((const TEXT_LINE*) second_pointer)->pointer;

    while (!is_string_end (*first_string) && !is_string_end (*second_string)){

        if (is_punctuation_character (*first_string)){
            first_string++;
            continue;
        }

        if (is_punctuation_character (*second_string)){
            second_string++;
            continue;
        }

        if (*first_string != *second_string){
            RETURN *first_string - *second_string;
        }

        first_string ++;
        second_string++;
    }

    if (!is_string_end (*first_string) && is_string_end (*second_string)){
        RETURN 1;
    }

    if (is_string_end (*first_string)  && !is_string_end (*second_string)){
        RETURN -1;
    }

    RETURN 0;
}

int compare_lines_reverse (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    const TEXT_LINE *first_line  = (const TEXT_LINE*) first_pointer;
    const TEXT_LINE *second_line = (const TEXT_LINE*) second_pointer;

    const char *first_string  = first_line->pointer  + first_line->length;
    const char *second_string = second_line->pointer + second_line->length;

    while (first_string != first_line->pointer && second_string != second_line->pointer){

        if (is_punctuation_character (*first_string)){
            first_string--;
            continue;
        }

        if (is_punctuation_character (*second_string)){
            second_string--;
            continue;
        }

        if (*first_string != *second_string){
            RETURN *first_string - *second_string;
        }

        first_string --;
        second_string--;
    }

    if (first_string != first_line->pointer && second_string == second_line->pointer){
        RETURN 1;
    }

    if (first_string == first_line->pointer && second_string != second_line->pointer){
        RETURN -1;
    }

    RETURN 0;
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
        RETURN;
    }

    char *element_1_char = (char *) element_1;
    char *element_2_char = (char *) element_2;

    char temp = 0;

    for (size_t byte_index = 0; byte_index < element_size; byte_index++){
        temp = element_1_char [byte_index];
        element_1_char [byte_index] = element_2_char [byte_index];
        element_2_char [byte_index] = temp;
    }

    RETURN;
}

void qsort_custom (void *sort_array, const size_t length, compare_function_t comparator, size_t element_size){
    PushLog (3);

    char *sort_array_char = (char *) sort_array;

    custom_assert (sort_array_char != NULL, pointer_is_null, (void)0);

    if (small_array_optimization (sort_array_char, length, comparator, element_size)){
        RETURN;
    }

    size_t greater_count = 0;
    size_t less_count    = 0;

    lomuto_partition (sort_array_char, length, element_size, &less_count, &greater_count, comparator);

    qsort_custom (element (0),              less_count,    comparator, element_size);
    qsort_custom (element (less_count), greater_count, comparator, element_size);
}

size_t set_pivot (char *sort_array_char, size_t length, size_t element_size){
    size_t pivot_index = (length + 1) / 2;

    swap_elements (element (length - 1), element (pivot_index), element_size);
    pivot_index = length - 1;

    return pivot_index;
}

void lomuto_partition (char *sort_array_char, size_t length, size_t element_size, size_t *less_count, size_t *greater_count, compare_function_t comparator){
    size_t pivot_index = set_pivot (sort_array_char, length, element_size);

    size_t left_index = 0;

    for (size_t index = 1; index < length; index++){
        if (comparator (element (index), element (pivot_index)) <= 0){
            left_index++;
            if (index != left_index){
                if (left_index == pivot_index){
                    pivot_index = index;
                }else if (index == pivot_index){
                    pivot_index = left_index;
                }

                swap_elements (element (left_index), element (index), element_size);
            }
        }
    }

    *less_count = left_index;
    *greater_count = length - *less_count;

}

void hoare_partition (char *sort_array_char, size_t length, size_t element_size, size_t *less_count, size_t *greater_count, compare_function_t comparator){

    char *pivot =  element ((length + 1) / 2);

    printf ("pivot = %c\n", *pivot);

    *greater_count = 0;
    *less_count = 0;

    char *left_pointer = element (0);
    char *right_pointer = element (length - 1);

    while (1){
        int left_comparison  = comparator (left_pointer,  pivot);
        int right_comparison = comparator (right_pointer, pivot);

        while (left_comparison < 0){
            printf ("left = %c\n", *left_pointer);
            left_pointer += element_size;
            left_comparison  = comparator (left_pointer,  pivot);
        }

        while (right_comparison > 0){
            printf ("right = %c\n", *right_pointer);
            right_pointer -= element_size;
            right_comparison = comparator (right_pointer, pivot);
        }

        if (left_pointer >= right_pointer){
            *less_count = (size_t)(right_pointer - sort_array_char) / element_size;
            *greater_count = length - *less_count;

            return;
        }

        if (left_pointer  == pivot){
            pivot = right_pointer;
        }else if (right_pointer == pivot){
            pivot = left_pointer;
        }

        printf ("Swapping values %c[%lu] and %c[%lu], ", *left_pointer, (size_t)(left_pointer - element (0)) / element_size, *right_pointer, (size_t)(right_pointer - element (0)) / element_size);

        /*
            ababaBaba
             ^      ^
            aaabaBabb
               ^   ^
            aaabaBabb
                 ^^
            aaabaaBbb

        */

        swap_elements (left_pointer, right_pointer, element_size);

        printf ("pivot = %c\n", *pivot);

        left_pointer += element_size;
        right_pointer -= element_size;
    }
}

void partition_old (char *sort_array_char, size_t length, size_t element_size, size_t *less_count, size_t *greater_count, size_t *pivot_count, compare_function_t comparator){
    size_t pivot_index = set_pivot (sort_array_char, length, element_size);

    for (size_t index = 1; index < length; index++){
        int compare_result = comparator (element (index), element (pivot_index));

        if (compare_result > 0){
            greater_count++;
        }else if (compare_result < 0){
            if (index == pivot_index + *pivot_count){
                swap_elements (element (pivot_index),element (index), element_size);

            }else{
                swap_elements (element (pivot_index), element (pivot_index + *pivot_count), element_size);

                swap_elements (element (pivot_index), element (index), element_size);
            }
            pivot_index++;
            less_count++;

        }else{
            swap_elements (element (pivot_index + *pivot_count), element (index), element_size);

            *pivot_count += 1;
        }
    }
}

bool small_array_optimization (char *sort_array_char, const size_t length, compare_function_t comparator, size_t element_size){
    PushLog (3);

    if (length < 2){
        RETURN true;
    }

    if (length == 2){
        if ((*comparator) (element (0), element (1)) > 0){

            swap_elements (element (0), element (1), element_size);
        }

        RETURN true;
    }

    if (length == 3){
        int compare_first_second = (*comparator) (element (0), element (1));
        int compare_second_third = (*comparator) (element (1), element (2));
        int compare_first_third  = (*comparator) (element (0), element (2));

        if (compare_first_second > 0){
            if (compare_second_third < 0){
                swap_elements (element (0), element (1), element_size);

                if (compare_first_third > 0){
                    swap_elements (element (1), element (2), element_size);
                }
            }else{
                swap_elements (element (0), element (2), element_size);
            }
        }else if (compare_first_second < 0){
            if (compare_second_third > 0){
                swap_elements (element (1), element (2), element_size);

                if (compare_first_third > 0){
                    swap_elements (element (0), element (1), element_size);
                }
            }else if(compare_second_third > 0){
                swap_elements (element (1), element (2), element_size);
            }
        }else{
            if (compare_second_third > 0){
                swap_elements (element (0), element (2), element_size);
            }
        }

        RETURN true;
    }

    RETURN false;
}


