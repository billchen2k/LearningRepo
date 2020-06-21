#include <bits/stdc++.h>
#define MAXL 25
#define INF 0x1f1f1f1f
#define long unsigned long long
using namespace std;

long k, r;
double p[MAXL];

double C(int a, int b) {
	if (b > a / 2) {
		b = a - b;
	}
	double res = 1;
	for (int i = 0; i < b; i++) {
		res *= (a - i);
	}
	for (int i = 1; i <= b; i++) {
		res /= i;
	}
	return res;
}

int main() {
	cin >> k >> r;
	int t = C(8, 35);
	fill(p, p + MAXL, 1);
	int maxwin = log2((1 << k) - r + 1);
	for (int i = 1; i <= maxwin; i++) {
		long A = (1 << i) - 1;
		long B = (1 << k) - r;
		long C = (1 << k) - 1;
		long gap = C - B;
		for (int j = 0; j < gap;j++){
			p[i] *= double(C - A - j) / double(C - j);
		}
		// 	double up = C((1 << k) - r, (1 << i) - 1);
		// double down = C((1 << k) - 1, (1 << i) - 1);
		// p[i] = up / down;
	}
	double res = 0;
	double last = 0;
	for (int i = maxwin; i > 0; i--) {
		res += (p[i] - last) * i;
		last += p[i] - last;
	}
	printf("%.5f", res);
}