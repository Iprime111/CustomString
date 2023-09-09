#ifndef FILEIO_H_
#define FILEIO_H_

ssize_t get_file_size (char *filename);
void read_file (char *filename, char *buffer, ssize_t file_size);

size_t split_buffer (char *file_buffer, char **line_buffer);

int open_file_w (char *filename);
void close_file (int file_descriptor);

void write_line(int file_descriptor, const char *str);
void write_lines (int file_descriptor, char **lines, size_t line_count);
void write_buffer (int file_descriptor, const char *buffer, ssize_t buffer_size);

#endif
