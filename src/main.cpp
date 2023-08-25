#include <string.h>

#include "CustomStrings.h"

#define dummy_test(func, exp)                       \
            do{                                     \
                if(func exp == func##_custom exp){  \
                    printf("ok\n");                 \
                }else{                              \
                    printf("ne ok\n");              \
                }                                   \
            }while(0)


int main(){
    char *a = "aaaaabc";
    char *b = "abc";

    dummy_test(strstr, (a, b));

    return 0;
}
