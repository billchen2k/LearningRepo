#include <stdio.h>
int max(int * data) {
	int temp = data[0], i=0;
	while (data[i] != -1) {
		if (data[i] > temp) temp = data[i];
		i++;
	}
	return temp;
}
int min(int * data) {
	int temp = data[0], i = 0;
	while (data[i] != -1) {
		if (data[i] < temp) temp = data[i];
		i++;
	}
	return temp;
}
int average(int * data) {
	int count, sum = 0;
	for (count = 0; data[count] != -1; count++) sum += data[count];
	return sum / count;
}
int main() {
	int i, len;
	scanf("%d", &len);
	for (i = 0; i < len; i++) {
		int input[101];
		int j = 0;
		do {
			scanf("%d", input + j);
			j++;
		} while (input[j-1] != -1);
		printf("case #%d:\n", i);
		printf("%d\n%d\n%d\n", max(input), min(input), average(input));
	}
	system("pause");
}
