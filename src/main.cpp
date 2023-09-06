#include <string.h>
#include <time.h>

#include "CustomStrings.h"
#include "CustomAssert.h"
#include "Onegin.h"

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


    char test_string[] = "qwertzzyuiop";

    qsort_char (test_string, strlen (test_string));

    printf ("%s\n", test_string);

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
