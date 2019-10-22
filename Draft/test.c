#include <stdio.h>
int main(void) {
	double tax, salary;
	int x, y;
	while(scanf("%d %d", &x, &y) != EOF){
		...
	}
		scanf("%f", &salary);
	if (salary <= 850) {
		tax = 0;
		printf("%.2f\n", tax);

	} else if (salary <= 1350 && salary > 850) {
		tax = (salary - 850) * 0.05;
		printf("%.2f\n", tax);
	} else if (salary <= 2850 && salary > 1350) {
		tax = (salary - 1350) * 0.1 + 1350 * 0.05;
		printf("%.2f\n", tax);
	} else if (salary > 2850 && salary <= 5850) {
		tax = (salary - 2850) * 0.15 + 500 * 0.1 + 500 * 0.05;
		printf("%.2f\n", tax);
	} else {
		tax = (salary - 5850) * 0.2 + 500 * 0.15 + 500 * 0.1 + 500 * 0.05;
	}
	return 0;
}