#include <stdio.h>
/* Read a string from stdin into buf */
long evil_read_string() {
	long buf[2];
	scanf("%s", buf);
	return buf[0];
}
int main() {
	printf("0x%c\n", evil_read_string());
}
