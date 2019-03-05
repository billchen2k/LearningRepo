#include <stdio.h>
#include "bytepointer.h"
float sum_elements(float a[], int len){
    int i = 0;
    float sum = 0;
    for (i = 0; i < len;i++){
        sum += a[i];
    }
    return sum;
}

int main(){
    float a[4] = {0.0, 0.0, 0.0, 0.0};
    printf("%f\n\n\n\n", sum_elements(a, 0));
    int i = -1;
    show_int(i);
    show_int(-3);
    show_int(i >> 31);
    printf("%d\n\n\n\n\n", i >> 1);
}