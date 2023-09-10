#ifndef ONEGIN_H_
#define ONEGIN_H_

enum COMPARE_RESULT{
    LESS    = -1,
    EQUAL   = 0,
    GREATER = 1
};

typedef int compare_function_t (const void *first_pointer, const void *second_pointer);

int compare_chars           (const void *first_pointer, const void *second_pointer);
int compare_ints            (const void *first_pointer, const void *second_pointer);
int compare_strings         (const void *first_pointer, const void *second_pointer);
int compare_strings_reverse (const void *first_pointer, const void *second_pointer);

void swap_elements          (void *element_1, void *element_2, size_t element_size);
void qsort_custom           (void *sort_array, const size_t length, compare_function_t comparator, size_t element_size);
bool sadgewick_optimization (char *sort_array, const size_t length, compare_function_t comparator, size_t element_size);

bool is_punctuation_character (char ch);
bool is_string_end            (char ch);

size_t line_len (const char *line);

#endif
