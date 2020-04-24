#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

int dp[1005];
int number[1005];
int cost[1005];
int sum[1005];
int main() {
	int n, t;
	cin >> n;
	while (n--) {
		cin >> t;
		memset(dp, 0, sizeof(0));
		memset(sum, 0, sizeof(0));
		for (int i = 1; i <= t; i++) {
			cin >> number[i] >> cost[i];
			sum[i] = sum[i - 1] + number[i];
		}
		dp[0] = 0;
		for (int i = 1; i <= t; i++) {
			dp[i] = dp[i - 1] + cost[i] * (number[i] + 10);
			for (int j = 0; j < i;j++){
				dp[i] = min(dp[i], dp[j] + (sum[i] - sum[j] + 10) * cost[i]);
			}
		}
		cout << dp[t] << endl;
	}
	return 0;
}