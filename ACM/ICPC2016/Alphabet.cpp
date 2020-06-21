/**
 * @file Alphabet.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 最长上升子串，动态规划
 * @version 0.1
 * @date 2020-06-18 21:39
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define MAXL 55
using namespace std;

int dp[MAXL];

int main() {
	int res = 0;
	fill(dp, dp + MAXL, 0);
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (s[j] < s[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		res = max(res, dp[i]);
	}
	cout << 26 - res;
}