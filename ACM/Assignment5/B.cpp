#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

struct vertex {
	int num;
	vector<vertex *> edge;
	int visited = 0;
};

int sol = 0;
int s = 1;
vertex G[20];

void dfs(vertex *r, vector<vertex *> ans) {
	if (r->visited == 1 && r != &G[s]) {
		return;
	}
	if (r->visited == 1 && r == &G[s] && ans.size() != 21){
		return;
	}
	r->visited = 1;
	if (r == &G[s] && ans.size() == 21) {
		sol++;
		cout << sol << ": ";
		for (auto n : ans) {
			printf(" %d", n->num);

		}
		cout << endl;
		return;
	}
	for (auto n : r->edge) {
		ans.push_back(n);
		dfs(n, ans);
		ans.pop_back();
	}
	r->visited = 0;
}

int main() {

	for (int i = 0; i < 20; i++) {
		G[i].num = i + 1;
		for (int j = 0; j < 3; j++) {
			int t;
			cin >> t;
			G[i].edge.push_back(&G[t - 1]);
		}
	}
	while (~scanf("%d", &s) && s != 0) {
		s--;
		for (int i = 0; i < 20; i++) {
			G[i].visited = 0;
		}
		sol = 0;
		vector<vertex *> ans;
		ans.push_back(&G[s]);
		dfs(&G[s], ans);
	}
}