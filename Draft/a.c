#include <stdio.h>
int main(){
    int input, i, j;
    scanf("%d", &input);
    int storage[10];
    for (i = 0; input != 0; i++){
        storage[i] = input % 10;
        input /= 10;
    }
    for (j =0; j < i; j++){
        if (j != i-1)
        printf("%d ", storage[j]);
        else
            printf("%d\n", storage[j]);
    }
    for (j = 0; j < i; j++){
        printf("%d", storage[j]);
    }
    printf("\n%d", i);
    return 0;
}