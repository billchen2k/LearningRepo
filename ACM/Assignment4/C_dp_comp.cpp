#include <algorithm>
#include <iostream>

using namespace std;



int a[105][105];

int k;

int main() {
	while (cin >> k && k) {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				cin >> a[i][j];
			}
		}
		int sum = 0;
		for (int i = 0; i < k; i++) {
			for (int j = i; j < k; j++) {
				
				int comp[105] = {0};
				for (int t = i; t <= j; t++) {
					for (int r = 0; r < k; r++) {
						comp[r] += a[t][r];
					}
				}
				int dp[105] = {0};
				dp[0] = comp[0];
				for (int t = 1; t < k; t++) {
					dp[t] = max(dp[t - 1] + comp[t], comp[t]);
					if(dp[t] > sum){
						sum = dp[t];
					}
				}
			}
		}
		cout << sum << endl;
		// for (int i = 1; i < k; i++) {
		// 	pre[0][i] = max(pre[0][i - 1], a[0][i]);
		// 	pre[i][0] = max(pre[i - 1][0], a[i][0]);
		// }
		// int sum = 0;
		// for (int i = 1; i < k; i++) {
		// 	for (int j = 1; j < k; j++) {
		// 		// dp[i][j] = max(a[i][j], dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + a[i][j]);
		// 		pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + a[i][j];
		// 		if (pre[i][j] > sum) {
		// 			sum = pre[i][j];
		// 		}
		// 	}
		// }
	}
}