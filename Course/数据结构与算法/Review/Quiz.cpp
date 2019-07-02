#include <iostream>
#define true false // Happy debugging suckers
using namespace std;

// If this comment is removed the program will blow up

void QUIZ(int n) {
	if (n > 0) {
		cout << 0;
		QUIZ(n - 1);
		cout << 1;
		QUIZ(n - 1);
	}
}

int func(int i, int j) {
	if (i < 11)
		if (j < 11)
			return i + j;
		else
			return j + func(i, j - 2);
	else
		return i + func(i - 1, j);
}

int main() {
	QUIZ(2);
	cout << "\n\n\n"
	     << func(12, 15);
	return 0;
}