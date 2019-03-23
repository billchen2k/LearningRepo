#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len){
	int i;
	for (i = 0; i < len; i++)
		printf("%.2x ", start[i]);
}
void show_int(int x){
	show_bytes((byte_pointer)&x, sizeof(int));
}
void show_double(double x){
	show_bytes((byte_pointer)&x, sizeof(double));
}
int main(){
	char input[10000];
	while ((scanf("%s", input) != EOF)){
		if(strchr(input, '.')){
			show_double(atof(input));
			printf("\n");
		}
		else{
			show_int(atoi(input));
			printf("\n");
		}
	}
	return 0;
}