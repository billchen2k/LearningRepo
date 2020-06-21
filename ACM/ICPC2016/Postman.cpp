/**
 * @file Postman.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 优先考虑最远的 house
 * @version 0.1
 * @date 2020-06-20 16:23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <bits/stdc++.h>
#define long long long
#define MAXL 1005
using namespace std;

long n, k;
struct house {
	long x;
	long m;
};
house h1[MAXL];
house h2[MAXL];

int cmp(const void *a, const void *b) {
	house *pa = (house *)a;
	house *pb = (house *)b;
	return pa->m - pb->m;
}

long run(int *c, house *h) {
	long sum = 0;
	while (1) {
		long hand = k, thiscost = 0;
		int i = 0;
		for (i = 0; i < *c; i++) {
			if (h[i].x == 0)
				break;
		}
		i -= 1;
		if (i == -1)
			break;
		thiscost = h[i].m;
		while (hand > 0 && i >= 0) {
			if (h[i].x > hand && hand == k) {
				long trip = h[i].x / hand;
				h[i].x = h[i].x - trip * hand;
				hand = 0;
				thiscost += (trip - 1) * h[i].m;
			} else if (h[i].x > hand) {
				h[i].x -= hand;
				hand = 0;
			} else {
				hand -= h[i].x;
				h[i].x = 0;
				i--;
			}
		}
		sum += 2 * thiscost;
	}
	return sum;
}

int main() {
	cin >> n >> k;
	int c1 = 0, c2 = 0;
	for (int i = 0; i < n; i++) {
		long a, b;
		cin >> a >> b;
		if (a < 0) {
			house h;
			h.m = -a, h.x = b;
			h1[c1++] = h;
		} else {
			house h;
			h.m = a, h.x = b;
			h2[c2++] = h;
		}
	}
	qsort(h1, c1, sizeof(house), cmp);
	qsort(h2, c2, sizeof(house), cmp);
	cout << run(&c1, h1) + run(&c2, h2);
}