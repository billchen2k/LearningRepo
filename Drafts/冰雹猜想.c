#include <stdio.h>

int main(){
    longint num;
    printf("This is a test for the Collatz Conjecture.\n");
    while (printf("Please enter an integer, -1 to exit:") && scanf("%ld", &num) && num != -1){
        int i=0;
        for (i=0;num!=1;i++){
            if (num%2==0) num/=2;
            elseif (num%2==1) num=num*3+1;
        }
        printf("success! We calculated %d times.\n" ,i);
    }
    return 0;
}

