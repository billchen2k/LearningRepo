#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>

const double r = 0.57721566490153286060651209;
using namespace std;
typedef long long ll;

/**
 * @brief Calculate harmonic number. 1/1 + 1/2 + 1/3 + ... + 1/n
 * 
 * @param n 
 * @return double 
 */
double harm(ll n) {
	return log(n) + r + 1.0 / (2 * n);
}

double calc(double m, ll a, ll b) {
	double res = 0;
	if (b < 10e10) {
		for (double i = a; i <= b; i++) {
			res += ((double)m / (double)i);
		}
	}
	else {
		res = m * harm(b) - m * harm(a);
	}
	return res;
}

int main() {
	ll n, m, k;
	double P = 0;
	cin >> n >> m >> k;
	if (m > n)
		m = n; // Not necessary
	if (k > m) {
		P += calc(m, k, n);
	} else {
		double certain_count = m - k + 1;
		P += certain_count;
		P += calc(m, m + 1, n);
		// P = certain_count + (n - m) * (m / n);
	}
	printf("%.10f", P);

	return 0;
}