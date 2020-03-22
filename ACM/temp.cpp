#include <cstdio>
#include <iostream>
using namespace std;
int main() {
	int a, b;
	int mon[30];
	for (int k = 0; k < 30; k++) {
		mon[k] = 1;
	}
	scanf("%d", &a);
	for (int i = 0; i < a; i++) {
		while (1)
		{
			scanf("%d", &b);
			if (b == -1) {
				break;
			}
			mon[b - 1] = 0;
		}
	}
	for (int l = 0; l < 30; l++) {
		if (mon[l] == 1) {
			printf("no");
			return 0;
		}
	}
	printf("yes");
}