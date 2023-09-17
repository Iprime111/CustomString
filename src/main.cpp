#include <string.h>
#include <time.h>

#include "CustomAssert.h"
#include "TextTypes.h"
#include "Onegin.h"
#include "string.h"
#include "FileIO.h"
#include "ConsoleParser.h"

static char *input_file  = "texts/hamlet.txt";
static char *output_file = "texts/hamlet_out.txt";

void specify_output_file (char **file_path);
void specify_input_file  (char **file_path);

int main(int argc, char **argv){
    PushLog (1);

    register_flag ("--output", "-o", specify_output_file, 1);
    register_flag ("--input",  "-i", specify_input_file,  1);

    custom_assert (parse_flags (argc, argv) >= 0, invalid_arguments, 0);

    FILE_BUFFER file_buffer = {};
    TEXT_BUFFER text_lines  = {};

    create_file_buffer (&file_buffer, input_file);

    read_file_lines (input_file, &file_buffer, &text_lines);

    int out_file_descriptor = -1;

    custom_assert ((out_file_descriptor = open_file_write (output_file)) != -1, cannot_open_file, 0);

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

void specify_output_file (char **file_path){
    PushLog (3);

    custom_assert (file_path != NULL, pointer_is_null, (void)0);
    custom_assert (*file_path != NULL, pointer_is_null, (void)0);

    output_file = *file_path;

    RETURN;
}

void specify_input_file  (char **file_path){
    PushLog (3);

    custom_assert (file_path != NULL, pointer_is_null, (void)0);
    custom_assert (*file_path != NULL, pointer_is_null, (void)0);

    input_file = *file_path;

    RETURN;
}


