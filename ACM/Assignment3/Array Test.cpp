#include <iostream>

using namespace std;

int **A;

int MAP[3][3];

void test(int **a) {
	a[1][1] = 8;
}


// void realTest((int &)map[3][3]){
// 	map[2][2] = 8;
// 	cout << map[2][2];
// }

int main() {
	MAP[2][2] = 1;

	cout << MAP[2][2];
	// A = new int *[3];
	// for (int i = 0; i < 3;i ++){
	// 	A[i] = new int[3];
	// }
	// test((int **)A);
	// cout << A[1][1];
}