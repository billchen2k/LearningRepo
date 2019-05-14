#include <algorithm>
#include <iostream>
using namespace std;
int main() {
	unsigned long long int input;
	cin >> input;
	int positions[100000] = {0};
	int t = 0;
	for (int i = 0; input > 0; i++) {
		if (input & 1 == 1) {
			positions[t++] = i;
		}
		input >>= 1;
	}
	int ans = 0, maxl = 0;
	for (int i = 0; i < t - 1; i++) {
		maxl = max(positions[i + 1] - positions[i], maxl);
	}
	cout << maxl << endl;
}
