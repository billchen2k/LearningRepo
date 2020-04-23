#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int dp[10000];
int a[10000];
int pos[10000];
int k;
int main() {
	while (cin >> k && k) {
		memset(dp, 0, sizeof(dp));
		memset(a, 0, sizeof(a));
		for (int i = 0; i < k; i++) {
			cin >> a[i];
		}
		dp[0] = a[0];
		pos[0] = 0;
		int maxend = 0;
		for (int i = 1; i < k; ++i) {
			dp[i] = max(dp[i - 1] + a[i], a[i]);
			pos[i] = dp[i - 1] + a[i] < a[i] ? i : pos[i - 1];
			if(dp[i] > dp[maxend]){
				maxend = i;
			}
		}
		if(dp[maxend] < 0){
			printf("%d %d %d\n", 0, a[0], a[k - 1]);
		}else{
			printf("%d %d %d\n", dp[maxend], a[pos[maxend]], a[maxend]);
		}
	}
}

int main(){
	mems
}
