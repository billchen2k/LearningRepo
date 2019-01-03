//
//  main.c
//  斐波那契数列
//
//  Created by Bill Chen on 2018/10/15.
//  Copyright © 2018 Bill Chen. All rights reserved.
//
#include <stdio.h>
int main(){
    int num;
    while(printf("Please enter a number here(enter -1 to exit):")
          && scanf("%d", &num) && num !=-1){
        for (int i=0; i<=num; i++){
            printf("%d\n", fib(i));
        }

    }
    return 0;
}
int fib(int N){
    int N0 = 0 , N1 = 1, result,i;
    result = 0;
    if(N == 0 || N == -1){
        return N;
    }
    else{
        for(i=0; i<N; i++){
            result = N0 + N1;
            N0 = N1;
            N1 = result;
        }
        return result;
    }
}
