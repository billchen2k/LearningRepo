#include <iostream>
using namespace std;

int div16(int x) {
	int t = x >> 31;
	int bias = (x >> 31) & 0xF;
	// bias = 0;
	return (x + bias) >> 4;
}

int main(){
	cout << div16(-18);
}