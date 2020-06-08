#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#define MAXL 300
#define INF 0x1f1f1f1f
using namespace std;

int v, e;
int G[MAXL][MAXL];

void init() {
	fill(G[0], G[0] + MAXL * MAXL, INF);
}

int main() {
	while (~scanf("%d %d", &v, &e)) {
		init();
		int start, end, speed;
		scanf("%d %d %d", &start, &end, &speed);
		G[start][end] = G[end][start] = speed;
		int q;
		scanf("%d", &q);
		while (q--) {
			int a, b;
			scanf("%d %d", &a, &b);
		}
	}
}