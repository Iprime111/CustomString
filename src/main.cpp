#include <string.h>
#include <time.h>

#include "CustomAssert.h"
#include "Onegin.h"
#include "string.h"
#include "FileIO.h"

int main(){
    PushLog (1);

    char *filename = "texts/hamlet.txt";

    char **text_lines = NULL;
    char *file_buffer = NULL;

    ssize_t file_size = -1;

    size_t new_line_count = get_file_lines (filename, &file_buffer, &file_size, &text_lines);

    int out_file_descriptor = -1;
    custom_assert ((out_file_descriptor = open_file_w ("texts/hamlet_out.txt")) != -1, cannot_open_file, 0);

    qsort_custom (text_lines, new_line_count, compare_strings, sizeof (char *));

    write_lines (out_file_descriptor, text_lines, new_line_count);

    qsort_custom (text_lines, new_line_count, compare_strings_reverse, sizeof (char *));

    write_line   (out_file_descriptor, "------------------------------------------------------------------");
    write_lines  (out_file_descriptor, text_lines, new_line_count);
    write_line   (out_file_descriptor, "------------------------------------------------------------------");
    write_buffer (out_file_descriptor, file_buffer, file_size);

    close_file (out_file_descriptor);

    free (file_buffer);
    free (text_lines);

    RETURN 0;
}


