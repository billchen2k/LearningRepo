/**
 * @file Mismatched Socks.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 判断是否有浪费
 * @version 0.1
 * @date 2020-06-20 02:54
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define long long long
using namespace std;

long k;
long s[1005];

int cmp(const void *a, const void *b) {
	return -(*(long *)a - *(long *)b);
}

int main() {
	cin >> k;
	long sum = 0;
	for (int i = 0; i < k; i++) {
		cin >> s[i];
		sum += s[i];
	}
	qsort(s, k, sizeof(long), cmp);
	long most = s[0];
	long waste = 0;
	if (most > sum / 2) {
		waste = most - (sum - most);
	}
	cout << (sum - waste) / 2;
}