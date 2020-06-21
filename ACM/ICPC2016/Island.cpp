/**
 * @file Island.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief Flood fill
 * @version 0.1
 * @date 2020-06-20 01:35
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define MAXL 55
using namespace std;

char grid[MAXL][MAXL];
int visited[MAXL][MAXL];
int m, n;

void flood(int x, int y){
	if(x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 'W' || visited[x][y]){
		return;
	}
	grid[x][y] = 'L';
	visited[x][y] = 1;
	flood(x - 1, y);
	flood(x, y - 1);
	flood(x + 1, y);
	flood(x, y + 1);
}

int main() {
	fill(visited[0], visited[0] + MAXL * MAXL, 0);
	scanf("%d %d", &m, &n);
	for (int i = 0; i < m; i++) {
		getchar();
		for (int j = 0; j < n; j++) {
			char tmp = getchar();
			grid[i][j] = tmp;
		}
	}
	int count = 0;
	for (int i = 0; i < m;i++){
		for (int j = 0; j < n;j++){
			if(!visited[i][j] && grid[i][j] == 'L'){
				count++;
				flood(i, j);
			}
		}
	}
	cout << count;
}