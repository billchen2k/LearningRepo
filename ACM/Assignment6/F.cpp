/**
 * @file F.cpp 并查集 + 暴力
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-12 21:27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
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

struct edge {
	int from;
	int to;
	int speed;
};

vector<edge> map;

int v, e;
int q;

int par[MAXL];

void init() {
	for (int i = 0; i < MAXL; i++) {
		par[i] = i;
	}
}

int find(int x) {
	if (par[x] == x) {
		return x;
	} else {
		return find(par[x]);
	}
}

void merge(int x, int y) {
	if (x == y) {
		return;
	} else {
		par[find(x)] = find(y);
	}
}

int cmp(edge a, edge b) {
	return (a.speed < b.speed);
}

int main() {
	while (~scanf("%d %d", &v, &e)) {
		map.clear();
		for (int i = 0; i < e; i++) {
			int start, end, speed;
			scanf("%d %d %d", &start, &end, &speed);
			edge e;
			e.from = start;
			e.to = end;
			e.speed = speed;
			map.push_back(e);
		}
		sort(map.begin(), map.end(), cmp);

		int q;
		scanf("%d", &q);
		while (q--) {
			int a, b;
			int m = INF;
			scanf("%d %d", &a, &b);
			for (int i = 0; i < e - 1; i++) {
				init();
				for (int j = i; j < e; j++) {
					if (find(a) != find(b)) {
						merge(map[j].from, map[j].to);
					} else {
						m = min(m, map[j - 1].speed - map[i].speed);
					}
				}
			}
			if(m == INF){
				printf("-1\n");
			}
			else{
				printf("%d\n", m);
			}
		}
	}
}