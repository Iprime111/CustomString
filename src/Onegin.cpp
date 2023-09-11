#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "Onegin.h"
#include "CustomAssert.h"
#include "TextTypes.h"

#define element(element_index) get_element (sort_array_char, element_index, element_size)

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

    // TODO "+1" -- сомнительно но окээээй
    size_t pivot_index = (length + 1) / 2;

    swap_elements (element (pivot_index),
            element (0), element_size);

    pivot_index = 0;

    size_t greater_count = 0;
    size_t less_count    = 0;

    size_t pivot_count = 1;

    // TODO as I told you, write function called "paritation" or somehow else
    // because it's actually a separated logic
    for (size_t index = 1; index < length; index++){
        int compare_result = (*comparator) (element (index),
                        element (pivot_index));

        if (compare_result > 0){
            greater_count++;
//TODO too many swaps, let me explain paritation algo to you
//TODO maybe you can avoid so many swaps by moving pivot at zero position, like I told you, but okaaay...
//
//imagine you have an array of nums
// [5, 0, 6, 7, 5, 4, 9, 2, 1]
//
// you've picked 5 as your pivot moved it to 0-position and wanna pariatate your array now
// let's do it step-by-step
//
// first, let's get two counters (left and right)
// left  (l) goes left-to-right and right (r) goes right-to-left
//
// there is an invariant... (things are called invariant if them stays unchanged for whole algorithm)
// ...that 'left' should always point at element that are smaller than pivot
// and 'right' should always point at element that are bigger than pivot
//
// lets do some steps:
//
// 1. l=0 < 5 okay
//    r=1 < 5 (not okay)
//
//    now we need something larger than 5 to swap with
//    so we just continue moving l, but not r
//  [5, 0, 6, 7, 5, 4, 9, 2, 1]
//      ^                    ^
//      l                    r
//
// 2. moving l until l points to somethin bigger than 5
// [5, 0, 6, 7, 5, 4, 9, 2, 1]
//       ^                  ^
//       l                  r
//  l = 6 > 5 (not okay)
//  r = 1 < 5 (not okay)
//
// so now we swap elements pointed by l and r:
// [5, 0, 1, 7, 5, 4, 9, 2, 6]
//        ^                 ^
//        l                 r
//
// and moving next:
// [5, 0, 6, 7, 5, 4, 9, 2, 1]
//           ^           ^
//           l           r
//
// same situation, so we swap again:
// [5, 0, 1, 2, 5, 4, 9, 7, 6]
//           ^           ^
//           l           r
//
// and moving next:
// [5, 0, 1, 2, 5, 4, 9, 7, 6]
//              ^     ^
//              l     r
// now "l" is eqaul to pivot and as we previously desided, less-or-equal elements are on the left
// "r" is also saves its invariant
//  so moving next...
// [5, 0, 1, 2, 5, 4, 9, 7, 6]
//                 ^
//                l,r
// now l and r positions are equal, so the last thing we have to do is to move pivot element back: just after "l" element:
//
// [0, 1, 2, 5, 4, 5, 9, 7, 6]
//              ^
//             l,r
//  and our array is fully paritated!
//  please, code it now)
//
//
        }else if (compare_result < 0){
            if (index == pivot_index + pivot_count){
                swap_elements (element (pivot_index),element (index), element_size);

            }else{
                swap_elements (element (pivot_index), element (pivot_index + pivot_count), element_size);

                swap_elements (element (pivot_index), element (index), element_size);
            }
            pivot_index++;
            less_count++;

        }else{
            swap_elements (element (pivot_index + pivot_count), element (index), element_size);

            pivot_count++;
        }
    }

    qsort_custom (element (0),                        less_count,    comparator, element_size);
    qsort_custom (element (less_count + pivot_count), greater_count, comparator, element_size);
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


