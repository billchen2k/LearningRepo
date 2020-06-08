#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>
#define MAX_L 105
#define INF 0xfffffff
using namespace std;

struct edge {
	int to, cost;
};

// vector<edge> G[MAX_L];

int G[MAX_L][MAX_L];
int dis[MAX_L][MAX_L];
int v, e;

int floyd() {
	int minc = INF;
	for (int k = 0; k < v; k++) {
		for (int i = 0; i < k; i++) {
			for (int j = i + 1; j < k; j++) {
				minc = min(minc, dis[i][j] + G[i][k] + G[k][j]);
			}
		}
		for (int i = 0; i < v; i++) {
			for (int j = 0; j < v; j++) {
                dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
			}
		}
	}
	return minc;
}

void init() {
	fill(G[0], G[0] + MAX_L * MAX_L, INF);
	fill(dis[0], dis[0] + MAX_L * MAX_L, INF);
	for (int i = 0; i < MAX_L; i++) {
		G[i][i] = 0;
		dis[i][i] = 0;
	}
}
int main() {
	while (~scanf("%d %d", &v, &e)) {
		init();
		for (int i = 0; i < e; i++) {
			int a, b, c;
            
			cin >> a >> b >> c;
			a--;
			b--;
			if (c < G[a][b]) {
				G[a][b] = G[b][a] = dis[a][b] = dis[b][a] = c;
			}
		}
		int minc = floyd();
		if (minc >= INF) {
			cout << "It's impossible." << endl;
		} else {
			cout << minc << endl;
		}
	}
	return 0;
}