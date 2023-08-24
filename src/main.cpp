#include <string.h>

#include "CustomStrings.h"

#define dummy_test(func, exp)                       \
            do{                                     \
                if(func exp == func##_custom exp){  \
                    printf("ok\n");                   \
                }else{                              \
                    printf("dolbaeb\n");              \
                }                                   \
            }while(0)


int main(){

    char *a = "hjvagdsiufhiweghiu";
    char b[50];
    strcpy(b, a);
    printf("%s %s", a, b);
    return 0;
}
