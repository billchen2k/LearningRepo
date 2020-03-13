#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
	long n, r;
	int isFirst = 1;
	while (!cin.eof()) {
		if (isFirst) {
			isFirst = 0;
		} else {
			printf("\n");
		}
		cin >> n >> r;
		string out;
		int minus = 0;
		if (n < 0) {
			minus = 1;
			cout << "-";
			n = -n;
		}
		while (n != 0) {
			out += ('0' + n % r + (n % r > 9 ? 7 : 0));
			n /= r;
		}
		for (int i = out.length() - 1; i >= 0; i--)
			cout << out[i];
	}
	return 0;
}