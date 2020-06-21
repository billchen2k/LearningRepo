/**
 * @file Barbells.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief DFS 枚举
 * @version 0.1
 * @date 2020-06-18 21:38
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define MAXL 16
using namespace std;

int n, m;
int temp;
vector<int> b;
vector<int> p;
vector<int> res;

void dfs(int root, int suma, int sumb) {
	if (suma == sumb) {
		res.push_back(suma);
	}
	if (root == m) {
		return;
	}
	dfs(root + 1, suma + p[root], sumb);
	dfs(root + 1, suma, sumb + p[root]);
	dfs(root + 1, suma, sumb);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		scanf("%d", &temp);
		b.push_back(temp);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &temp);
		p.push_back(temp);
	}
	dfs(0, 0, 0);
	vector<int> final;
	for (auto i : b) {
		for (auto j : res) {
			if (find(final.begin(), final.end(), i + 2 * j) == final.end()) {
				final.push_back(i + 2 * j);
			}
		}
	}
	sort(final.begin(), final.end());
	for (auto i : final) {
		cout << i << endl;
	}
}