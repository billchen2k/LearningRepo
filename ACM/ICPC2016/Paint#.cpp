/**
 * @file Paint.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 动态规划
 * @version 0.1
 * @date 2020-06-20 21:33
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define MAXL 200005
#define long long long
using namespace std;

struct fence {
	long left;
	long right;
};

fence f[MAXL];
map<long, long> d;
long n, k;

int cmp(const void * a, const void * b){
	fence *pa = (fence *)a;
	fence *pb = (fence *)b;
	return pa->left > pb->left ? 1 : -1;
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		long a, b;
		cin >> a >> b;
		if(a < b)
			swap(a, b);
		fence ff;
		ff.left = ++a, ff.right = b;
		f[i] = ff;
	}
	qsort(f, k, sizeof(f[0]), cmp);
	for (int i = 0; i < k; i++) {
		long dis = f[i].left - f[i].right;
		auto it = d.upper_bound(f[i].right);
		if(it != d.begin()){
			it--;
			dis += it->second;
		}
		if(d.size() == 0 || dis > d.rbegin()->second){
			d[f[i].left] = dis;
		}
	}
	cout << n - d.rbegin()->second << endl;
}