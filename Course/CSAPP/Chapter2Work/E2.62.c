//对于使用算术右移的机器将会输出1，否则将会输出0。

#include <stdio.h>

int int_shifts_are_arithmetic(){
    int source = -1;
    int des = source >> 1;
    if (des == -1)
        return 1;
    else
        return 0;
}

int main(){
    printf("%d", int_shifts_are_arithmetic());
    return 0;
}