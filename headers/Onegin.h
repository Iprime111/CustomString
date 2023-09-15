#ifndef ONEGIN_H_
#define ONEGIN_H_

typedef int compare_function_t (const void *first_pointer, const void *second_pointer);

int compare_chars         (const void *first_pointer, const void *second_pointer);
int compare_ints          (const void *first_pointer, const void *second_pointer);
int compare_lines         (const void *first_pointer, const void *second_pointer);
int compare_lines_reverse (const void *first_pointer, const void *second_pointer);

void swap_elements            (void *element_1, void *element_2, size_t element_size);
void qsort_custom             (void *sort_array,      const size_t length, compare_function_t comparator, size_t element_size);
bool small_array_optimization (char *sort_array_char, const size_t length, compare_function_t comparator, size_t element_size);

bool is_punctuation_character (char ch);
bool is_string_end            (char ch);

size_t line_len (const char *line);

void lomuto_partition (char *sort_array_char, size_t length, size_t element_size, size_t *less_count, size_t *greater_count, compare_function_t comparator);

#endif
