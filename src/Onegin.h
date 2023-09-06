#ifndef ONEGIN_H_
#define ONEGIN_H_

enum COMPARE_RESULT{
    LESS    = -1,
    EQUAL   = 0,
    GREATER = 1
};

enum COMPARE_RESULT compare_chars (char first_char, char second_char);
void qsort_char (char *sort_string, const size_t length);
void clean_line (char *line);
void delete_punctuation (char *line);

#endif
