#include <bits/stdc++.h>
using namespace std;

int main() {
	while (!cin.eof()) {
		int m, n;
		cin >> m >> n;
		int count = 0;
		for (int i = m; i <= n; i++) {
			if (pow(i / 100, 3) + pow(i % 100 / 10, 3) + pow(i % 100 % 10, 3) == i) {
				printf("%d ", i);
				count++;
			}
		}
		if (count == 0) {
			cout << "no" << endl;
		}
	}
}