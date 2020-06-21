/**
 * @file Six Sides.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 枚举
 * @version 0.1
 * @date 2020-06-20 04:05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
#define long long long
using namespace std;

int a[6];
int b[6];

int main(){
	for (int i = 0; i < 6;i++){
		cin >> a[i];
	}
	for (int i = 0; i < 6; i++) {
		cin >> b[i];
	}
	int win = 0;
	int same = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6;j++){
			if(b[j] < a[i])
				win++;
			if(a[i] == b[j]){
				same++;
			}
		}
	}
	printf("%.5f", double(win) / (36 - same));
}