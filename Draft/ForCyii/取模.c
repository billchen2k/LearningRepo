#include <stdio.h>
#define ULL unsigned long long

int main() {
	int input;
	scanf("%d", &input);
	if (input == 0) {
		printf("%d\n", 1);
	} else {
		ULL int sum = 1;
		for (ULL int i = 1; i <= input; i++) {
			sum = (sum % 20181111 * i % 20181111) % 20181111;
		}
		printf("%lld\n", sum);
	}
	return 0;
}
