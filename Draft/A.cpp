#include <bits/stdc++.h>
using namespace std;

int main() {
	unsigned int x = 0XDEADBEEF;
	unsigned short y = 0xFFFF;
	cout << (x > (signed short) y ) << endl;
	cout << x << endl;
	cout << (signed short)y << endl;
}