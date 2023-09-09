#include <string.h>
#include <time.h>

#include "CustomAssert.h"
#include "Onegin.h"
#include "string.h"
#include "FileIO.h"

int main(){
    PushLog (1);

    char *filename = "texts/hamlet.txt";

    int out_file_descriptor = -1;
    custom_assert ((out_file_descriptor = open_file_w ("texts/hamlet_out.txt")) != -1, cannot_open_file, 0);

    ssize_t file_size  = get_file_size (filename);
    custom_assert (file_size > 0, invalid_value, 0);

    char *file_buffer = (char *) calloc ((size_t) file_size + 1, sizeof (char));

    read_file (filename, file_buffer, file_size);

    size_t new_line_count = split_buffer (file_buffer, NULL);
    char **text_lines     = (char **) calloc (new_line_count, sizeof (char *));

    split_buffer (file_buffer, text_lines);

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


