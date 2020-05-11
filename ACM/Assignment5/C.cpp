#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>
#define INF 1e9
using namespace std;

int dis[105][105];
vector<int> G[105];

int main() {
	int N, M;

	while (~scanf("%d %d", &N, &M)) {

		for (int i = 0; i < 105; i++) {
			G[i].clear();
			fill(dis[0], dis[0] + 105 * 105, -1);
		}

		while (M--) {
			int a, b;
			if (b > a) {
				swap(a, b);
			}
			scanf("%d %d", &a, &b);
			G[a].push_back(b);
		}

		for (int i = 0; i < N; i++) {
			vector<int> S;
			S.push_back(i);
			for (int j = 0; !S.empty(); j++) {
				vector<int> T = S;
				S.clear();
				for (auto t : T) {
					for (auto r : G[t]) {
						if (dis[i][r] == -1) {
							dis[i][r] = dis[r][i] = j;

							S.push_back(r);
						}
					}
				}
			}
		}

		int ans = 1, num = 0;
		for (int i = 1; i < N; i++) {
			if (dis[0][i] != -1) {
				num++;
			}
		}
		for (int i = 0; i < 105; i++) {
			for (int j = 0; j < 105; j++) {
				if (dis[i][j] > 6 && i != j) {
					ans = 0;
				}
			}
		}
		printf("%s\n", (ans == 1 && num == N - 1 ? "Yes" : "No"));
	}
}