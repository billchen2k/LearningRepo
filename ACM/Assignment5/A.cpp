#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

struct vertex {
	vector<vertex *> edge;
	int visited = 0;
	int d = -1;
};

int main() {
	int len;
	cin >> len;
	while (len--) {
		int N, D;
		cin >> N >> D;
		vertex *G = new vertex[N];
		//vertex G[105];
		for (int i = 0; i < N - 1; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			//printf("'%d %d'", a, b);
			G[a].edge.push_back(&G[b]);
		}
		vector<vertex *> S;
		vector<vertex *> ans;
		S.push_back(&G[0]);
		for (int i = 0; !S.empty(); i++) {
			vector<vertex *> T = S;
			S.clear();
			for (auto n : T) {
				if (n->visited == 0) {
					n->visited = 1;
					n->d = i;
					if (i > D) {
						ans.push_back(n);
					}
				}
				for (auto e : n->edge) {
					S.push_back(e);
				}
			}
		}
		cout << ans.size() << endl;
	}

	return 0;
}