#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <string.h>
#include <vector>
#define MAXL 100000
using namespace std;

int arr[MAXL];
int s = 0;
int n;
int sum;
set<vector<int>> ans;
bool used[MAXL];

void dfs(int i, int j, int cnt) {
	// printf("dfs(%d, %d)\n", i, j);
	if (i > n || j > sum) {
		return;
	}
	if (sum == j) {
		// Output result
		vector<int> res;
		int r = 0;
		for (int r = 0; r < n; r++) {
			if (used[r] == true) {
				res.push_back(arr[r]);
			}
		}
		if (ans.find(res) == ans.end()) {
			ans.insert(res);
			for (int k = 0; k < res.size(); k++) {
				if (k == 0) {
					cout << res[k];
				} else {
					cout << "+" << res[k];
				}
			}
			cout << endl;
		}
		return;
	}
	used[i] = true;
	dfs(i + 1, j + arr[i], cnt + 1);
	used[i] = false;
	dfs(i + 1, j, cnt);
	return;
}

int main() {
	cin >> sum >> n;
	while (sum != 0) {
		ans.clear();
		s = 0;
		memset(used, 0, MAXL * sizeof(bool));
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		cout << "Sums of " << sum << ":" << endl;
		dfs(0, 0, 0);
		if (ans.size() == 0) {
			cout << "NONE" << endl;
		}
		cin >> sum >> n;
	}
}
