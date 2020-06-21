/**
 * @file Contest Score.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 送分的
 * @version 0.1
 * @date 2020-06-20 00:38
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define MAXL 10000005
#define long long long
using namespace std;

long d[MAXL];
bool f[MAXL];
priority_queue<long, vector<long>, greater_equal<long>> solve;
long last = 0;
long penalty = 0;

int main() {
	int n, k;
	fill(f, f + MAXL, 0);
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		int tmp;
		scanf("%d", &tmp);
		d[i] = tmp;
	}
	int i = 0;
	for (i = 0; i < k; i++) {
		solve.push(d[i]);
	}
	while(!solve.empty()){
		int num = solve.top();
		solve.pop();
		penalty += last + num;
		last = last + num;
		if(i < n){
			solve.push(d[i]);
			i++;
		}
	}
	cout << penalty << endl;
}