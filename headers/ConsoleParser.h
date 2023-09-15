#ifndef CONSOLE_PARSER_H_
#define CONSOLE_PARSER_H_

const size_t MAX_FLAG_NAME_LENGTH = 20;
const size_t MAX_FLAG_COUNT = 40;

typedef void flag_function_t (char **arguments);

struct CONSOLE_FLAG{
    char short_name [MAX_FLAG_NAME_LENGTH];
    char long_name  [MAX_FLAG_NAME_LENGTH];

    flag_function_t *flag_function;
    size_t arguments_count;
};


void parse_arguments (int argc, char **argv);
void register_flag (char short_name[], char long_name[], flag_function_t *flag_function);
int init_flags ();
void close_flags ();

#endif
