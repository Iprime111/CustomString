#ifndef COLOR_CONSOLE
#define COLOR_CONSOLE

#include <stdio.h>
#include <stdarg.h>

/// @brief Enum for picking text color in console
enum CONSOLE_COLOR{
    Console_black   = 0, ///< Black color
    Console_red     = 1, ///< Red color
    Console_green   = 2, ///< Green color
    Console_yellow  = 3, ///< Yellow color
    Console_blue    = 4, ///< Blue color
    Console_purple  = 5, ///< Purple color
    Console_cyan    = 6, ///< Cyan color
    Console_white   = 7, ///< White color
    Console_default = 9  ///< Default color
};

/// @brief Enum for picking bold or normal text
enum CONSOLE_BOLD{
    Console_normal  = 0, ///< Normal text
    Console_bold    = 1  ///< Bold text
};

/*!
    @brief Printf's given text with given color, bold and arguments
    @param[in] color  Text color
    @param[in] bold   Text bold
    @param[in] format Printf format string
*/
void printf_color (enum CONSOLE_COLOR color, enum CONSOLE_BOLD bold, const char *format, ...);

/*!
    @brief Changes console color to given
    @param[in] color Text color
    @param[in] bold  Text bold
*/
void set_color (enum CONSOLE_COLOR color, enum CONSOLE_BOLD bold);

#endif
