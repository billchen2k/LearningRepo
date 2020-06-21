/**
 * @file Three Square.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 枚举
 * @version 0.1
 * @date 2020-06-20 03:54
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define long long long
using namespace std;

struct panel {
	int x;
	int y;
};

panel p[3];

int cmp(const void * a, const void *b){
	panel *pa = (panel *)a;
	panel *pb = (panel *)b;
	return pa->y - pb->y;
}

int main() {
	for (int i = 0; i < 3; i++) {
		int x, y;
		cin >> x >> y;
		if(x > y)
			swap(x, y);
		panel pp;
		pp.x = x, pp.y = y;
		p[i] = pp;
	}
	qsort(p, 3, sizeof(panel), cmp);
	string res = "NO";
	if (p[0].y == p[1].y && p[1].y == p[2].y && p[0].x + p[1].x + p[2].x == p[0].y) {
		res = "YES";
	} else {
		int len = p[2].y;
		int w = p[2].x;
		if (p[1].x == p[0].x && p[1].y + p[0].y == len && p[1].x + w == len ||
		    p[1].y == p[0].y && p[1].x + p[0].x == len && p[1].y + w == len ||
		    p[1].x == p[0].y && p[1].y + p[0].x == len && p[1].x + w == len) {
			res = "YES";
		}
	}
	cout << res;
}