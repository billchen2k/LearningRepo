#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

#define INF 1e9
#define MAX_V 10000
struct edge {
	int to;
	int cost;
};

// first: 最短距离，second: 该顶点编号
typedef pair<int, int> P;

int V = 0;

int V = 0;

vector<edge> G[MAX_V];
int d[MAX_V];

void dijkstra(int s) {
	priority_queue<P, vector<P>, greater<P>> que;
	fill(d, d + V, INF);
	d[s] = 0;
	while (!que.empty()) {
		P p = que.top();
		que.pop();
		int v = p.second;
		if (d[v] < p.first)
			continue;
		for (int i = 0; i < G[v].size(); i++) {
			edge e = G[v][i];
			if (d[v] + e.cost < d[e.to]) {
				d[e.to] = d[v] + e.cost;
				que.push(P(d[e.to], e.to));
			}
		}
	}
}


int main() {
	dijkstra(0);
	return 0;
}