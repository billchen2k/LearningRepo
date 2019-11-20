#include <stdio.h>

double sum = 0.0;
int count = 0;

float RunningAvg(float value) {
	count++;
	sum += value;
	if (count == 0 || sum == 0.0)
		return 0;
	return sum / count;
}

int main() {
	float input = 0.0;
	while (scanf("%f", &input)) {
		if (input == -1)
			break;
		printf("%.2f\n", RunningAvg(input));
	}
	return 0;
}
