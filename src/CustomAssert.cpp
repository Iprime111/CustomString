#include "CustomAssert.h"


void assert_perror_custom (enum ERROR_CODE code, char *expr, const char *file, const char* function, int line){

    const char* msg = "??? Unknown code ???";

    #define MSG_(err_code, descr)       \
        case err_code:                  \
            msg = #err_code ": " descr; \
            break;

    switch (code) {
        MSG_ (number_is_nan,        "Requested number is NaN!")
        MSG_ (number_is_inf,        "Requested number is inf!")
        MSG_ (not_enough_pointers,  "One or multiple pointers are similar!")
        MSG_ (eof_found,            "EOF symbol has been found in input buffer!")
        MSG_ (pointer_is_null,      "Requested pointer is NULL!")
        MSG_ (cannot_open_file,     "Can not open file for reading!")
        MSG_ (wrong_data_format,    "Incorrect file data format!")
        MSG_ (too_many_arguments,   "Too many command line arguments!")
        MSG_ (file_close_error,     "Can not close file!")
        MSG_ (length_too_big,       "String length is too big!")
        MSG_ (file_reading_error,   "Error occuried while trying to read file")

        default:
            msg = "Unknown error!";
            break;
    }

    printf_color (Console_red, Console_normal, "%s  ", msg);


    #ifdef _DEBUG
        printf_color (Console_red, Console_normal, "(%s in file: %s:%d function: %s)\n",\
                     expr, file, line, function);
    #endif

    #undef MSG_
}
