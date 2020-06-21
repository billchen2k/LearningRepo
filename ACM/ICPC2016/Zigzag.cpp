/**
 * @file Zigzag.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 同时进行两个动态规划
 * @version 0.1
 * @date 2020-06-20 12:42
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define long long long
using namespace std;

int arr[55];
int dup[55];
int ddown[55];

int main() {
	int n;
	cin >> n;
	fill(dup, dup + 55, 1);
	fill(ddown, ddown + 55, 1);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	int fup = 1, fdown = 1;
	for (int i = 1; i < n; i++) {
		dup[i] = dup[i - 1];
		ddown[i] = ddown[i - 1];
		for (int j = 0; j < i; j++) {
			if ((fup == 1 && arr[i] > arr[j]) || (-fup == 1 && arr[i] < arr[j])) {
				dup[i] = max(dup[i], dup[j] + 1);
			}
			if ((fdown == 1 && arr[i] < arr[j]) || (-fdown == 1 && arr[i] > arr[j])) {
				ddown[i] = max(ddown[i], ddown[j] + 1);
			}
		}
		if (dup[i] > dup[i - 1])
			fup = -fup;
		if (ddown[i] > ddown[i - 1])
			fdown = -fdown;
	}
	cout << max(dup[n - 1], ddown[n - 1]);
}