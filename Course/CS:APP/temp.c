#include <stdio.h>

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
    printf("%f", sum_elements(a, 0));
}