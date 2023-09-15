#include <stdio.h>
#include <stdarg.h>

#include "ConsoleParser.h"
#include "CustomAssert.h"

static struct CONSOLE_FLAG *registered_flags = NULL;
static size_t flags_count = 0;

int _init_flags_array_ = init_flags ();

int parse_arguments (int argc, char **argv){
    PushLog (2);

    if (argc < 2){
        RETURN -1;
    }

    custom_assert (argv != NULL, pointer_is_null, -1);

    struct CONSOLE_FLAG *current_flag = NULL;
    bool is_searching_flag = false;
    size_t arguments_readed = 0;
    char ** current_arguments_begin = NULL;


    for (size_t argument_index = 0; argument_index < argc - 1; argument_index++){

        if (is_searching_flag){
            arguments_readed++;
            if (arguments_readed == current_flag->arguments_count){
                is_searching_flag = false;
                arguments_readed = 0;
            }
            continue;
        }

        if ((current_flag = search_flag (*(argv + argument_index))) != NULL){
            if (is_searching_flag){
                RETURN -1;
            }

            is_searching_flag = true;
            current_arguments_begin = argv + argument_index;
        }
    }

    RETURN 0;
}

CONSOLE_FLAG *search_flag (char *flag){
    PushLog (3);

    for (size_t flag_index = 0; flag_index < flags_count; flag_index++){
        if (strcmp (registered_flags [flag_index].long_name, flag)  == 0 ||
            strcmp (registered_flags [flag_index].short_name, flag)  == 0){

            RETURN registered_flags + flag_index;
        }
    }

    RETURN NULL;
}

void register_flag (char short_name[], char long_name[], flag_function_t *flag_function){
    PushLog (2);

    custom_assert (flag_function != NULL, pointer_is_null, (void)0);
    custom_assert (short_name != NULL, pointer_is_null, (void)0);
    custom_assert (long_name != NULL, pointer_is_null, (void)0);
    custom_assert (long_name != short_name, not_enough_pointers, (void)0);

    strncpy (short_name, registered_flags [flag_index].short_name, MAX_FLAG_NAME_LENGTH);
    strncpy (long_name,  registered_flags [flag_index].long_name,  MAX_FLAG_NAME_LENGTH);

    registered_flags [flags_count].flag_function = flag_function;
    registered_flags [flags_count].arguments_count = 0;

    flags_count++;

    RETURN;
}

int init_flags (){
    PushLog (3);

    registered_flags = (struct CONSOLE_FLAG *) calloc (MAX_FLAG_COUNT, sizeof (CONSOLE_FLAG));
    atexit (close_flags);

    RETURN 1;
}

void close_flags (){
    PushLog (3);

    free (registered_flags);

    RETURN;
}
