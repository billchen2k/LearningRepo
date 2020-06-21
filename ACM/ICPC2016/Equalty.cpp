
/**
 * @file Equalty.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 送分的
 * @version 0.1
 * @date 2020-06-20 00:55
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <bits/stdc++.h>
using namespace std;

int main(){
	char eq[10];
	cin.getline(eq, 10);
	if (eq[0] + eq[4] - '0' == eq[8]) {
		cout << "YES";
	} else {
		cout << "NO";
	}
}