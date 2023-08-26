#include <string.h>
#include <time.h>

#include "CustomStrings.h"

#define dummy_test(func, exp)                           \
            do{                                         \
                if(func exp == func##_custom_2 exp){    \
                    printf("ok\n");                     \
                }else{                                  \
                    printf("ne ok\n");                  \
                }                                       \
            }while(0)


#define print_function_test_results(function, time_f, result)                               \
            do{                                                                             \
                 printf (#function " avg time: %ld clocks\tresult: %p\n", time_f, result);  \
            }while(0)

int main(){
    char *a = NULL;
    size_t sz = 0;

    FILE *fp = fopen ("testfile.txt", "r");

    getline (&a, &sz, fp);
    char *b = "abcdefg";

    clock_t init_time = 0, strstr_time = 0, strstr_custom_naive_time = 0, strstr_custom_time = 0;
    clock_t strstr_time_sum = 0, strstr_custom_naive_time_sum = 0, strstr_custom_time_sum = 0;
    char *default_res = NULL, *custom_naive_res = NULL, *custom_res = NULL;

    const int LAUNCH_COUNT = 10000;

    for (int i = 0; i < LAUNCH_COUNT; i++){
        init_time = clock ();

        default_res = strstr (a, b);

        strstr_time = clock ();

        custom_naive_res = strstr_custom_naive (a, b);

        strstr_custom_naive_time = clock ();

        custom_res = strstr_custom (a, b);

        strstr_custom_time = clock ();

        strstr_time_sum += strstr_time - init_time;
        strstr_custom_naive_time_sum += strstr_custom_naive_time - strstr_time;
        strstr_custom_time_sum += strstr_custom_time - strstr_custom_naive_time;
    }

    print_function_test_results (strstr(), strstr_time_sum / LAUNCH_COUNT, default_res);
    print_function_test_results (strstr_custom_naive(), strstr_custom_naive_time_sum / LAUNCH_COUNT, custom_naive_res);
    print_function_test_results (strstr_custom(), strstr_custom_time_sum / LAUNCH_COUNT, custom_res);

    fclose (fp);
    free (a);

    return 0;
}
