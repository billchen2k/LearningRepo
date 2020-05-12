#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>

#define MAXL 100005
using namespace std;

struct edge {
	int to;
	bool visited;
};

vector<edge> G[MAXL];
int N, M;
int num = 0;

void dfs(int s) {

	for (int i = 0; i < G[s].size(); i++) {
		if(!G[s][i].visited){
			G[s][i].visited = 1;
			dfs(G[s][i].to);
		}
	}
	printf("%d\n", s);
}
int main() {
	cin >> N >> M;
	while (M--) {
		int a, b;
		cin >> a >> b;
		edge e;
		e.to = b;
		e.visited = 0;
		G[a].push_back(e);
		e.to = a;
		G[b].push_back(e);
	}
	dfs(1);
}