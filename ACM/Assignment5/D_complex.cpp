#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>

#define MAXL 100005
using namespace std;
struct edge;
struct vertex {
	int num;
	vector<edge> edge;
};

struct edge {
	vertex *to;
	int visited;
	edge(vertex *_to) {
		to = _to;
		visited = 0;
	}
};

vertex G[MAXL];
int N, M;
vector<int> ans;
int vt = 0, dM = 0;
void dfs(vertex *s, vector<int> ans) {
	if (vt == 2 * dM && s == &G[0]) {
		cout << 1 << endl;
		for (int i = 0; i < ans.size();i++) {
			cout << ans[i] << endl;
		}
		// cout << "------" << endl;
		exit(0);
	}
	vector<edge> connected;
	for (int i = 0; i < s->edge.size();i++) {
		edge e = s->edge[i];
		if (e.visited == 2) {
			return;
		} else {
			e.visited++;
			vt++;
			int i = 0;
			for (int i = 0;; i++) {
				if (e.to->edge[i].to == s) {
					e.to->edge[i].visited++;
					break;
				}
			}
			ans.push_back(e.to->num);

			dfs(e.to, ans);
			
			ans.pop_back();
			e.visited--;
			vt--;
			e.to->edge[i].visited--;
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= MAXL; i++) {
		G[i - 1].num = i;
	}
	while (M--) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		for (int i = 0; i < G[a].edge.size(); i++) {
			if (G[a].edge[i].to == &G[b]) {
				break;
			}
		}
		edge e(&G[b]);
		dM++;
		G[a].edge.push_back(e);
		e.to = &G[a];
		G[b].edge.push_back(e);
	}
	dfs(&G[0], ans);
}