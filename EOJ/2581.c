#include <stdio.h>
int main(void) {
	int n, x, N, d;
	int l = 0, m = 0;
	scanf("%d", &N);
	for (n = 1; n <= N; n++) {
		scanf("%d", &x);
		do {
			d = x % 2;
			if (d == 1)
				l++;
			x = x / 2;
			if (d == 0)
				m++;
		} while (x != 0);
		printf("%d %d\n", m, l);
	}
	return 0;
}