#include "ColorConsole.h"

void printf_color (enum CONSOLE_COLOR color, enum CONSOLE_BOLD bold, const char *format, ...){
    va_list args;
    va_start (args, bold);

    printf ("\033[%d;3%dm", bold, color);
    vfprintf (stdout, format, args); // TODO pass stdout as a default argument to be able to print to file
    printf ("\033[0;39m");

    va_end (args);
}

void set_color (enum CONSOLE_COLOR color, enum CONSOLE_BOLD bold){
    printf ("\033[%d;3%dm", bold, color);
}


