#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#define MAX_L 1005
#define INF 0xffffff
#define LL long long
using namespace std;

int G[MAX_L][MAX_L];
int dis[MAX_L][MAX_L];
LL t, s, d, n = 0;
int start[MAX_L];
int dest[MAX_L];

void init() {
	// 未清 0
	// start.clear();
	// dest.clear();
	fill(G[0], G[0] + MAX_L * MAX_L, INF);
	fill(dis[0], dis[0] + MAX_L * MAX_L, INF);
	for (int i = 0; i < MAX_L; i++) {
		G[i][i] = 0;
		dis[i][i] = 0;
	}
}

void floyd() {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			if (G[k][i] == INF) {
				continue;
			}
			for (int j = 0; j < n; j++) {
				dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
			}
		}
	}
}

int main() {
	while (~scanf("%lld %lld %lld", &t, &s, &d)) {
		init();
		for (int i = 0; i < t; i++) {
			LL a, b, c;
			cin >> a >> b >> c;
			a--;
			b--;
			if (c < G[a][b]) {
				G[a][b] = G[b][a] = dis[a][b] = dis[b][a] = c;
			}
			n = max(n, max(a, b));
		}
		LL temp;
		for (int i = 0; i < s;i++){
			cin >> temp;
			start[i] = temp - 1;
		}
		for (int i = 0; i < d; i++) {
			cin >> temp;
			dest[i] = temp - 1;
		}
		// 	while (s--) {
		// 		cin >> temp;
		// 		start.push_back(temp - 1);
		// 	}
		// while (d--) {
		// 	cin >> temp;
		// 	dest.push_back(temp - 1);
		// }
		floyd();
		int mint = INF;
		for (int i = 0; i < s;i++){
			for (int j = 0; j < d;j++){
				mint = min(mint, dis[start[i]][dest[j]]);
			}
		}
			// for (auto i : start) {
			// 	for (auto j : dest) {
			// 		mint = min(mint, dis[i][j]);
			// 	}
			// }
		cout << mint << endl;
	}
	return 0;
}