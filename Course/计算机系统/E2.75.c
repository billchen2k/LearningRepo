#include <stdio.h>
#include "bytepointer.h"

int main(){
    int x, y;
    while(scanf("%d %d", &x, &y)!=EOF){
        unsigned ux = (unsigned)x;
        unsigned uy = (unsigned)y;
         //     printf("%d\n", ((x + y) << 4) + y - x == 17 * y + 15 * x);
        printf("%d\n", ((x>>2)<<2 <= x));
    }
}