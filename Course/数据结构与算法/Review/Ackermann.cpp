#include <iostream>
using namespace std;
int fun(int m, int n) {
	printf("A(%d, %d)\n", m, n);
	if (m == 0 && n >= 0)
		return n + 1;
	if (m > 0 && n == 0) {
		return fun(m - 1, 1);
	}
	if (m > 0 && n > 0) {
		return fun(m - 1, fun(m, n - 1));
    }
}
int main() {
	cout << fun(2, 1) << endl;
}
