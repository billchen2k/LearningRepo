//Answer A:左移的时候超出了该类型的宽度。
//Answer B:
#include <stdio.h>
#include "bytepointer.h"
int int_size_is_32(){
    int msb = 1;
    unsigned char *pointer1 = &msb;
    if (*pointer1 == 0x01){
        int moved_msb = msb >> 24;
        return msb && !(moved_msb);
    }
    else{
        int
        moved_msb = msb <<31;
        return msb && !(moved_msb);
    }
}
int main(){
    printf("%d", int_size_is_32());
}