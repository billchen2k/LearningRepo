#include <stdio.h>
typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len){
    int i;
    for (i = 0; i < len; i++)
        printf("%.2x ", start[i]);
}
void show_int(int x){
    show_bytes((byte_pointer)&x, sizeof(int));
}
void show_float(float x){
    show_bytes((byte_pointer)&x, sizeof(float));
}
void show_double(float x){
    show_bytes((byte_pointer)&x, sizeof(double));
}