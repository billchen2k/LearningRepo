#include <stdio.h>

int main(){
    puts("Please input an English phrase with space:");
    int count=0; char c;
    c=getchar();
    while (c!='\n'){
        if(count==0) {printf("Word No.1: "); count++;}
        if (c==' '){
            count++;
            printf("\nWord No.%d: ", count);
        }
        else{
            putchar(c);
        }
        c=getchar();
    }
    printf("\nThere are %d words in total.", count);
    return 0;
}

