#include <string.h>
#include <time.h>

#include "CustomAssert.h"
#include "CustomStrings.h"
#include "Onegin.h"
#include "string.h"
#include "FileIO.h"

#define dummy_test(func, exp)                           \
            do{                                         \
                if(func exp == func##_custom exp){      \
                    printf("ok\n");                     \
                }else{                                  \
                    printf("ne ok\n");                  \
                }                                       \
            }while(0)


#define print_function_test_results(function, time_f, result)                               \
            do{                                                                             \
                 printf (#function " avg time: %ld clocks\tresult: %p\n", time_f, result);  \
            }while(0)


void test_strstr ();

int main(){
    PushLog (1);

    char *filename = "texts/hamlet.txt";

    int out_file_descriptor = -1;
    custom_assert ((out_file_descriptor = open_file_w ("texts/hamlet_out.txt")) != -1, cannot_open_file, 0);

    ssize_t file_size  = get_file_size (filename);
    custom_assert (file_size > 0, invalid_value, 0);

    char *file_buffer = (char *) calloc ((size_t) file_size + 1, sizeof (char));

    read_file (filename, file_buffer, file_size);

    size_t new_line_count = split_buffer (file_buffer, NULL);
    char **text_lines     = (char **) calloc (new_line_count, sizeof (char *));

    split_buffer (file_buffer, text_lines);

    qsort_custom (text_lines, new_line_count, compare_strings, sizeof (char *));

    write_lines (out_file_descriptor, text_lines, new_line_count);

    qsort_custom (text_lines, new_line_count, compare_strings_reverse, sizeof (char *));

    write_line   (out_file_descriptor, "------------------------------------------------------------------");
    write_lines  (out_file_descriptor, text_lines, new_line_count);
    write_line   (out_file_descriptor, "------------------------------------------------------------------");
    write_buffer (out_file_descriptor, file_buffer, file_size);

    close_file (out_file_descriptor);

    free (file_buffer);
    free (text_lines);

    RETURN 0;
}


void test_strstr (){
    char  *input_string = NULL;
    size_t input_size   = 0;

    char *substring = "abcdefg";

    FILE *file_pointer = fopen ("testfile.txt", "r");

    getline (&input_string, &input_size, file_pointer);

    clock_t init_time                = 0,
            strstr_time              = 0,
            strstr_custom_naive_time = 0,
            strstr_custom_time       = 0;

    clock_t strstr_time_sum              = 0,
            strstr_custom_naive_time_sum = 0,
            strstr_custom_time_sum       = 0;

    char *default_res      = NULL,
         *custom_naive_res = NULL,
         *custom_res       = NULL;

    const int LAUNCH_COUNT = 1;

    for (int i = 0; i < LAUNCH_COUNT; i++){
        init_time                = clock ();

        default_res              = strstr (input_string, substring);
        strstr_time              = clock ();

        custom_naive_res         = strstr_custom_naive (input_string, substring);
        strstr_custom_naive_time = clock ();

        custom_res               = strstr_custom (input_string, substring);
        strstr_custom_time       = clock ();

        strstr_time_sum              += strstr_time              - init_time;
        strstr_custom_naive_time_sum += strstr_custom_naive_time - strstr_time;
        strstr_custom_time_sum       += strstr_custom_time       - strstr_custom_naive_time;
    }

    print_function_test_results (strstr(),              strstr_time_sum / LAUNCH_COUNT,              default_res);
    print_function_test_results (strstr_custom_naive(), strstr_custom_naive_time_sum / LAUNCH_COUNT, custom_naive_res);
    print_function_test_results (strstr_custom(),       strstr_custom_time_sum / LAUNCH_COUNT,       custom_res);

    fclose (file_pointer);
    free   (input_string);

}
