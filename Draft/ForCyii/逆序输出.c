#include <stdio.h>

void recursion() {
	int temp;
	scanf("%d", &temp);
	if (temp == 0) {
		return;
	}
	recursion();
	printf("%d ", temp);
}

int main() {
	recursion();
}
