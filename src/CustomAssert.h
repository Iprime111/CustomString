#ifndef CUSTOMASSERT
#define CUSTOMASSERT

#include <stdio.h>

#include "ColorConsole.h"

// TODO make a custom assert library as a git submodule

/*! @brief Custom assert implementation that provides information about file, function and line and do not stops the program*/
#define custom_assert(EXP, CODE, RET)                                                           \
            do{                                                                                 \
                if (!(EXP)){                                                                    \
                    assert_perror_custom (CODE, #EXP, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                    return RET;                                                                 \
                }                                                                               \
            }while(0)                                                                           \

/// @brief Code of detected error

//TODO you can use powers of two as error code to easily stack them
// for exaple if you reach 'eof found' and then 'too many arguments'
// 'too many arguments' will override first error
// so I suggest you to use powers of two like shown below:

enum ERROR_CODE{
    number_is_nan       = 0,  ///< Given number has NaN value
    number_is_inf       = 1 << 0,  ///< Given numver has inf value
    not_enough_pointers = 1 << 1,  ///< One or multiple pointers have one address
    eof_found           = 1 << 2,  ///< EOF symbol has been found in input buffer
    pointer_is_null     = 4,  ///< Given pointer has NULL value
    cannot_open_file    = 5,  ///< Error is occuried while opening file
    wrong_data_format   = 6,  ///< File data have wrong format
    too_many_arguments  = 7,  ///< Too many console line arguments have been passed
    file_close_error    = 8,  ///< Error is occuried while closing file
    length_too_big      = 9,  ///< String length is too big
    file_reading_error  = 10  ///< Error while reading file
};

/*!
    @brief Shows error in console
    @param[in] code Error code
    @param[in] expr Tested expression
    @return Nothing
    Shows detailed error description, it's file and line and tested expression
*/
void assert_perror_custom (enum ERROR_CODE code, char *expr, const char *file, const char *function, int line);

#endif


