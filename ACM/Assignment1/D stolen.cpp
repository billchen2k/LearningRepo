#include <stdio.h>
#include <string.h>

int main() {
	int T, N;
	int t, i;
	int a[100001];
	scanf("%d", &T);
	for (t = 0; t < T; t++) {
		scanf("%d", &N);
		for (i = 0; i < N; i++)
			scanf("%d", &a[i]);
		int maxSum = a[0];
		int sum = 0, l = 0, r = 0;
		int tmpL = 0;
		for (i = 0; i < N; i++) {
			sum += a[i];
			if (sum > maxSum) {
				maxSum = sum;
				l = tmpL;
				r = i;
			}
			if (sum < 0) {
				sum = 0;
				tmpL = i + 1;
			}
		}
		printf("Case %d:\n", t + 1);
		printf("%d %d %d\n", maxSum, l + 1, r + 1);
		if (t < T - 1)
			printf("\n");
	}
}