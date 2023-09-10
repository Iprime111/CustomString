#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "Onegin.h"
#include "CustomAssert.h"

int compare_chars (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    RETURN *((const char *) first_pointer) - *((const char *) second_pointer);
}

int compare_ints (const void *first_pointer, const void *second_pointer){
    PushLog (4);

    RETURN *((const char *) first_pointer) - *((const char *) second_pointer);
}

int compare_strings (const void *first_pointer, const void *second_pointer){
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

int compare_strings_reverse (const void *first_pointer, const void *second_pointer){
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

        if (*first_string != *second_string){
            RETURN *first_string - *second_string;
        }

        first_string --;
        second_string--;
    }

    if (first_string != first_string_begin && second_string == second_string_begin){
        RETURN 1;
    }

    if (first_string == first_string_begin && second_string != second_string_begin){
        RETURN -1;
    }

    RETURN 0;
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

    // TODO why are you gay?
    // Actually, why are you hate operator[] :c
    //
    for (size_t byte_index = 0; byte_index < element_size; byte_index++){
        temp = *(element_1_char + byte_index);
        *(element_1_char + byte_index) = *(element_2_char + byte_index);
        *(element_2_char + byte_index) = temp;
    }

    RETURN ;
}

void qsort_custom (void *sort_array, const size_t length, compare_function_t comparator, size_t element_size){
    PushLog (3);

    char *sort_array_char = (char *) sort_array;

    custom_assert (sort_array_char != NULL, pointer_is_null, (void)0);

    // TODO so good naming!
    // It's well-known all of us has a friend called Sadgewick who invented some sorting optimizations...
    if (sadgewick_optimization (sort_array_char, length, comparator, element_size)){
        RETURN ;
    }

    // TODO "+1" -- сомнительно но окээээй
    size_t pivot_index = (length + 1) / 2;

    // TODO maybe it is a good time to introduce get_element_function(array, idx, element_size)?
    swap_elements (sort_array_char + pivot_index * element_size, sort_array_char, element_size);

    pivot_index = 0;

    size_t greater_count = 0;
    size_t less_count    = 0;

    size_t pivot_count = 1;

    // TODO as I told you, write function called "paritation" or somehow else
    // because it's actually a separated logic
    for (size_t index = 1; index < length; index++){
        int compare_result = (*comparator) (sort_array_char + index * element_size,
                        sort_array_char + pivot_index * element_size);

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

        }else{
            swap_elements (sort_array_char + (pivot_index + pivot_count) * element_size,
                    sort_array_char + index * element_size, element_size);

            pivot_count++;
        }
    }

    qsort_custom (sort_array_char,                                             less_count,    comparator, element_size);
    qsort_custom (sort_array_char + (less_count + pivot_count) * element_size, greater_count, comparator, element_size);
}


// TODO okay, I got it, but rename this function like "small_array_size_optimization" or something....
bool sadgewick_optimization (char *sort_array, const size_t length, compare_function_t comparator, size_t element_size){
    PushLog (3);

    if (length < 2){
        RETURN true;
    }

    if (length == 2){
        if ((*comparator) (sort_array, sort_array + element_size) > 0){
            swap_elements (sort_array, sort_array + element_size, element_size);
        }

        RETURN true;
    }

    if (length == 3){
        int compare_first_second = (*comparator) (sort_array, sort_array + element_size);
        int compare_second_third = (*comparator) (sort_array + element_size, sort_array + element_size * 2);
        int compare_first_third  = (*comparator) (sort_array, sort_array + element_size * 2);

        if (compare_first_second > 0){
            if (compare_second_third < 0){
                swap_elements (sort_array, sort_array + element_size, element_size);

                if (compare_first_third > 0){
                    swap_elements (sort_array + element_size, sort_array + element_size * 2, element_size);
                }
            }else{
                swap_elements (sort_array, sort_array + 2 * element_size, element_size);
            }
        }else if (compare_first_second < 0){
            if (compare_second_third > 0){
                swap_elements (sort_array + element_size, sort_array + 2 * element_size, element_size);

                if (compare_first_third > 0){
                    swap_elements (sort_array, sort_array + element_size, element_size);
                }
            }else if(compare_second_third > 0){
                swap_elements (sort_array + element_size, sort_array + 2 * element_size, element_size);
            }
        }else{
            if (compare_second_third > 0){
                swap_elements (sort_array, sort_array + 2 * element_size, element_size);
            }
        }

        RETURN true;
    }

    RETURN false;
}


