#include <sys/io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "FileIO.h"
#include "CustomAssert.h" //
                          // TODO move all headers file to "include/" dir, then add "-Iinclude" flag to compiler
                          // It will separate public interface of all of your functions from its private interface and realizations

// TODO It's unclear to me what this function does
// According to "get_file_size" I assumed that function just to
// count line numbers in file
// But actually this function allocates file buffer, reads file in the buffer, then splits file into array of lines etc.
// Please, either rename it or split into gifferent functions
size_t get_file_lines (const char *filename, char **file_buffer, ssize_t *file_size, char ***text_lines){
    PushLog (2);

    *file_size  = get_file_size (filename);
    custom_assert (*file_size > 0, invalid_value, 0);

    *file_buffer = (char *) calloc ((size_t) *file_size + 1, sizeof (char));

    read_file (filename, *file_buffer, *file_size);

    size_t new_line_count = split_buffer (*file_buffer, NULL); // TODO why is it "new"? Where are olg good classical "line_count"?))
    *text_lines           = (char **) calloc (new_line_count, sizeof (char *));

    split_buffer (*file_buffer, *text_lines);

    RETURN new_line_count;
}

ssize_t get_file_size (const char *filename){
    PushLog (3);

    struct stat file_statistics;

    custom_assert (stat(filename, &file_statistics) == 0, cannot_open_file, 0);

    RETURN file_statistics.st_size;
}

void read_file (const char *filename, char *buffer, ssize_t file_size){
    PushLog (3);

    custom_assert (filename != NULL,   pointer_is_null,     (void)0);
    custom_assert (buffer   != NULL,   pointer_is_null,     (void)0);
    custom_assert (filename != buffer, not_enough_pointers, (void)0);
    custom_assert (file_size > 0,      invalid_value,       (void)0);

    int file_descriptor = -1;

    custom_assert ((file_descriptor = open (filename, O_RDONLY)) != -1, cannot_open_file, (void)0);

    custom_assert (read (file_descriptor, buffer, (size_t) file_size) == file_size, cannot_open_file, (void)0);

    custom_assert (close (file_descriptor) == 0, file_close_error, (void) 0);

    RETURN ; // TODO why is there space
    //----^------
    //WhY???@?@?@??00
}

// TODO split to what? Split to two same buffers? Or to ten unique copies with separate memory? Add this info into function's name
size_t split_buffer (char *file_buffer, char **line_buffer){
    PushLog (3);

    custom_assert (file_buffer != NULL, pointer_is_null, 0);

    char *current_symbol = file_buffer;
    size_t new_line_index = 0;

    // TODO you can avoid duplication of stored information and copiing symbols to lines buffer
    // think how....
    // hint #1: you have already stored those lines in file buffer
    // hint #2: line ends with "\n" or "\0"
    //
    while (*current_symbol != '\0'){
        if (line_buffer != NULL){                             // TODO why do you have to check it in EVERY cycle iteration while you can just move this check into function's start?
            *(line_buffer + new_line_index) = current_symbol; // TODO use operator[], please. You should not use it only when you're doing some *magic* with pointers and arrays.
        }

        if ((current_symbol = strchr (current_symbol, '\n')) == NULL) // TODO do you really call strchr on every cycle's iteration? You want your function to be O(n^2) don't you?
            break;

        new_line_index++; // TODO I believe more appropriate name is "current_line_index" according to "current_symdol"
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

int open_file_w (const char *filename){ // TODO what are you gonna do with those 3 seconds you save writing "w" instead of "write"?)) Please, fix it.
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
