/**
 * @file Camera.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 贪心
 * @version 0.1
 * @date 2020-06-19 21:38
 * 
 * @copyright Copyright (c) 2020
 * 
 */
// #include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#define MAXL 100001
// using namespace std;

int road[MAXL];

inline int read() {
	int sgn = 1;
	int cnt = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			sgn = -sgn;
		ch = getchar();
	}
	while ('0' <= ch && ch <= '9') {
		cnt = cnt * 10 + (ch - '0');
		ch = getchar();
	}
	return sgn * cnt;
}

inline int judge(int root, int r) {
	int count = 0;
	for (int i = 0; i < r; i++) {
		if (road[root + i] == 1) {
			count++;
			if (count >= 2) {
				return 2;
			}
		}
	}
	return count;
}

int main() {
	memset(road, 0, sizeof(int) * MAXL);
	// fill(road, road + MAXL, 0);
	int a, b, r;
	a = read();
	b = read();
	r = read();
	//scanf("%d %d %d", &a, &b, &r);
	// cin >> a >> b >> r;
	while (b--) {
		// int tmp;
		// tmp = read();
		// cin >> tmp;
		road[read()] = 1;
	}
	int count = 0;
	int current = 0;
	for (int i = 0; i < r; i++) {
		if (road[i] == 1) {
			current++;
		}
	}
	if (current == 1) {
		int i = r - 1;
		while(road[i] == 1)
			i--;
		road[i] = 1;
		current++, count++;
	}
	else if (current == 0) {
		road[r - 1] = 1;
		road[r - 2] = 1;
		current += 2, count += 2;
	}
	for (int i = 1; i < a - r + 1; i++) {
		current = road[i - 1] == 1 ? current - 1 : current;
		current = road[i + r - 1] == 1 ? current + 1 : current;
		if(current == 1){
			road[i + r - 1] = 1;
			current++, count++;
		}
		else if(current == 0){
			road[i + r - 1] = 1;
			road[i + r - 2] = 1;
			current+=2, count+=2;
		}
		// int t = judge(i, r);
		// if (t == 1) {
		// 	road[i + r - 1] = 1;
		// 	count++;
		// } else if (t == 0) {
		// 	road[i + r - 1] = 1;
		// 	road[i + r - 2] = 1;
		// 	count += 2;
		// 	i++;
		// }
	}
	printf("%d", count);
}