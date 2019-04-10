#include <stdio.h>
int int_high_prod(int x, int y){
    return 0;
}
unsigned unsigned_high_prod(unsigned x, unsigned y){
    int w = sizeof(int) << 3;
    return int_high_prod(x, y);
}