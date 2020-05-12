#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>

#define MAXL 10005

using namespace std;

struct node {
	bool on = 0;
	short visited = 0;
};

int tv = 0, dM = 0;
node G[MAXL][MAXL];
vector<int> ans;
int N, M;
void dfs(int s, vector<int> ans) {
	if (tv == dM * 2 && s == 0) {
		cout << 1 << endl;
		for (auto i : ans) {
			cout << i + 1 << endl;
		}

	}
	for (int i = 0; i < N; i++) {
		if (G[s][i].on || G[i][s].on) {
			if (G[s][i].visited == 2) {
				return;
			}
			ans.push_back(i);
			tv++;
			G[s][i].visited++;
			G[i][s].visited++;
			dfs(i, ans);
			G[s][i].visited--;
			G[i][s].visited--;
			tv--;
			ans.pop_back();
		}
	}
}

int main() {
	cin >> N >> M;
	while (M--) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		if (G[a][b].on == 0) {
			dM++;
		}
		G[a][b].on = 1;
		G[b][a].on = 1;
	}
	dfs(0, ans);
}