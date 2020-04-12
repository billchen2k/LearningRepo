#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>
#define MAXL 1000
using namespace std;

typedef pair<int, int> P;

char map[MAXL][MAXL];
int m, n;

bool visit[MAXL][MAXL];
int d1[MAXL][MAXL];
int d2[MAXL][MAXL];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
vector<P> kfcs;
P sa;
P sb;

queue<P> q;

bool canGo(P p) {
	if (p.first < 0 || p.first == m || p.second < 0 || p.second == n) {
		return false;
	}
	if (map[p.first][p.second] == '#' || visit[p.first][p.second] == true) {
		return false;
	}
	// if (p == sa || p == sb) {
	// 	return false;
	// }
	return true;
}

void clear(int d[][MAXL]) {
	for (int j = 0; j < MAXL; j++) {
		for (int i = 0; i < MAXL; i++) {
			d[i][j] = 0;
			visit[i][j] = false;
		}
	}
}

void bfs(P s, int d[][MAXL]) {
	clear(d);
	d[s.first][s.second] = 0;
	q.push(s);
	while (q.size()) {
		s = q.front();
		q.pop();
		visit[s.first][s.second] = 1;
		for (int i = 0; i < 4; i++) {
			P newp = P(s.first + dx[i], s.second + dy[i]);
			if (canGo(newp)) {
				q.push(newp);
				d[newp.first][newp.second] = d[s.first][s.second] + 1;
			}
		}
	};
}

int main() {

	while (cin >> m >> n) {
		kfcs.clear();
		memset(map, 0, sizeof(map));
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				char tmp;
				cin >> tmp;
				map[i][j] = tmp;
				if (tmp == '@') {
					kfcs.push_back(P(i, j));
				}
				if (tmp == 'Y') {
					sa = P(i, j);
				}
				if (tmp == 'M') {
					sb = P(i, j);
				}
			}
		}
		bfs(sa, d1);
		bfs(sb, d2);
		int min = 99999999;
		for (auto it = kfcs.begin(); it != kfcs.end(); it++) {
			int tot1 = d1[(*it).first][(*it).second];
			int tot2 = d2[(*it).first][(*it).second];
			if (tot1 + tot2 < min && tot1 != 0 && tot2 != 0) {
				min = tot1 + tot2;
			}
		}
		cout << min * 11 << endl;
	}
}
