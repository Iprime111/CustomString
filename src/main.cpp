#include <string.h>
#include <time.h>

#include "CustomAssert.h"
#include "TextTypes.h"
#include "Onegin.h"
#include "string.h"
#include "FileIO.h"

int main(){
    PushLog (1);

    char filename[] = "texts/hamlet.txt"; // TODO read file name from cli args with default value of "hanlet.txt"

    FILE_BUFFER file_buffer = {};
    TEXT_BUFFER text_lines  = {};

    create_file_buffer (&file_buffer, filename);

    read_file_lines (filename, &file_buffer, &text_lines);

    int out_file_descriptor = -1;
    custom_assert ((out_file_descriptor = open_file_write ("texts/hamlet_out.txt")) != -1, cannot_open_file, 0);

    char delimiter [] = "------------------------------------------------------------------";
    TEXT_LINE delimiter_line = {delimiter, sizeof (delimiter)};

    qsort_custom (text_lines.lines, text_lines.line_count, compare_lines,         sizeof (TEXT_LINE));
    write_lines (out_file_descriptor, &text_lines);
    write_line   (out_file_descriptor, &delimiter_line);

    qsort_custom (text_lines.lines, text_lines.line_count, compare_lines_reverse, sizeof (TEXT_LINE));
    write_lines  (out_file_descriptor, &text_lines);
    write_line   (out_file_descriptor, &delimiter_line);


    write_buffer (out_file_descriptor, file_buffer.buffer, file_buffer.buffer_size);

    close_file (out_file_descriptor);
    destroy_file_buffer (&file_buffer);
    free (text_lines.lines);

    RETURN 0;
}


