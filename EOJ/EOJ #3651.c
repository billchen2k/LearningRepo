#include <stdio.h>

int main(){
    unsignedlongint N, A, B;
    scanf("%ld %ld %ld", &N, &A, &B);
    unsignedlongint max, min;
    max=B*(N-1)+A;
    min=A*(N-1)+B;
    printf("%ld",max-min+1);
    return 0;
}

