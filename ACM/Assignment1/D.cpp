#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int j, num[100000] = {0};
		cin >> j;

		for (int q = 0; q < j; q++){
			cin >> num[q];
		}
		int start = 0, end = 0, max = 0, sum = 0;
		for (int k = 1; k <= j; ++k){
			for (int r = 0; r <= j - k;r++){
				int tsum = 0;
				for (int p = 0; p < k; p++) {
					tsum += num[r + p];
				}
				if(tsum >= sum){
					sum = tsum;
					start = r + 1;
					end = r + k;
				}
			}
		}

		cout << "Case " << i + 1 << ":" << endl;
		cout << sum << " " << start << " " << end;

		///
		if (i != n - 1) {
			cout << endl;
		}
	}

	return 0;
}