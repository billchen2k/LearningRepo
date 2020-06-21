/**
 * @file Gravity.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 还是送分的
 * @version 0.1
 * @date 2020-06-20 01:13
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define MAXL 55
using namespace std;

char grid[MAXL][MAXL];

int m, n;

void down(int x, int y) {
	while (x < m && grid[x + 1][y] == '.') {
		grid[x][y] = '.';
		grid[x + 1][y] = 'o';
		x++;
	}
}

int main() {
	scanf("%d %d", &m, &n);
	for (int i = 0; i < m; i++) {
		getchar();
		for (int j = 0; j < n; j++) {
			char tmp;
			tmp = getchar();
			grid[i][j] = tmp;
		}
	}
	for (int i = m - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 'o') {
				down(i, j);
			}
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%c", grid[i][j]);
		}
		printf("\n");
	}
}