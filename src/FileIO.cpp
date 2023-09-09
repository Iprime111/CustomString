#include <sys/io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "FileIO.h"
#include "CustomAssert.h"

ssize_t get_file_size (char *filename){
    PushLog (3);

    struct stat file_statistics;

    custom_assert (stat(filename, &file_statistics) == 0, cannot_open_file, 0);

    RETURN file_statistics.st_size;
}

void read_file (char *filename, char *buffer, ssize_t file_size){
    PushLog (3);

    custom_assert (filename != NULL,   pointer_is_null,     (void)0);
    custom_assert (buffer   != NULL,   pointer_is_null,     (void)0);
    custom_assert (filename != buffer, not_enough_pointers, (void)0);
    custom_assert (file_size > 0,      invalid_value,       (void)0);

    int file_descriptor = -1;

    custom_assert ((file_descriptor = open (filename, O_RDONLY)) != -1, cannot_open_file, (void)0);

    custom_assert (read (file_descriptor, buffer, (size_t) file_size) == file_size, cannot_open_file, (void)0);

    custom_assert (close (file_descriptor) == 0, file_close_error, (void) 0);

    RETURN ;
}

size_t split_buffer (char *file_buffer, char **line_buffer){
    PushLog (3);

    custom_assert (file_buffer != NULL, pointer_is_null, 0);

    char *current_symbol = file_buffer;
    size_t new_line_index = 0;

    while (*current_symbol != '\0'){
        if (line_buffer != NULL){
            *(line_buffer + new_line_index) = current_symbol;
        }

        if ((current_symbol = strchr (current_symbol, '\n')) == NULL)
            break;

        new_line_index++;
        current_symbol++;
    }

    RETURN new_line_index;

}

void write_line(int file_descriptor, const char *line){
    PushLog (3);

    custom_assert (line != NULL,        pointer_is_null, (void)0);
    custom_assert (file_descriptor > 0, invalid_value,   (void)0);

    ssize_t length = 0;

    while (*(line + length) != '\0' && *(line + length) != '\n'){
        length++;
    }

    if (length == 0){
        RETURN ;
    }

    write_buffer (file_descriptor, line, length);
    write_buffer (file_descriptor, "\n", 1);

    RETURN ;
}

void write_lines (int file_descriptor, char **lines, size_t line_count){
    PushLog (3);

    custom_assert (lines != NULL,       pointer_is_null, (void)0);
    custom_assert (file_descriptor > 0, invalid_value,   (void)0);

    for (size_t line = 0; line < line_count; line++){
        write_line (file_descriptor, *(lines + line));
    }

    RETURN ;
}

void write_buffer (int file_descriptor, const char *buffer, ssize_t buffer_size){
    PushLog (3);

    custom_assert (buffer != NULL,      pointer_is_null, (void)0);
    custom_assert (file_descriptor > 0, invalid_value,   (void)0);
    custom_assert (buffer_size >= 0,    invalid_value,   (void)0);

    custom_assert (write (file_descriptor, buffer, (size_t)buffer_size) == buffer_size, cannot_open_file, (void)0);

    RETURN ;
}

int open_file_w (char *filename){
    PushLog (4);

    int file_descriptor = -1;

    custom_assert ((file_descriptor = open (filename, O_WRONLY | O_CREAT)) != -1, cannot_open_file, -1);

    RETURN file_descriptor;
}

void close_file (int file_descriptor){
    PushLog (4);

    custom_assert (close (file_descriptor) == 0, file_close_error, (void) 0);

    RETURN ;
}
