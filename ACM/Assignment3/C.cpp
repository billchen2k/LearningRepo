#include <algorithm>
#include <iostream>
#include <set>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

#define MAXL 100
using namespace std;

int board[MAXL + 2][MAXL + 2];
int sx[MAXL + 2];
int sy[MAXL + 2];
int sxy[2 * MAXL + 5];
int syx[2 * MAXL + 5];
int n;
unsigned long sol;

void rec(int k) {
	if (k == n) {
		sol++;
		// Output result
		cout << "Solution #" << sol << ":" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (board[j][i] == 1) {
					cout << "♟ ";
				} else {
					cout << "- ";
				}
			}
			cout << endl;
		}
		return;
	} else {
		for (int i = 0; i < n; i++) {
			if (sx[i] == 0 && sy[k] == 0 && sxy[i + k] == 0 && syx[n - i - 1 + k] == 0) {
				sx[i] = sy[k] = sxy[i + k] = syx[n - i - 1 + k] = board[i][k] = 1;
				rec(k + 1);
				sx[i] = sy[k] = sxy[i + k] = syx[n - i - 1 + k] = board[i][k] = 0;
			}
		}
		return;
	}
}

int main() {
	int result[MAXL] = {0};
	while (cin >> n && n != 0) {
		sol = 0;
		memset(board, 0, sizeof(board));
		memset(sx, 0, sizeof(sx));
		memset(sy, 0, sizeof(sy));
		memset(sxy, 0, sizeof(sxy));
		memset(syx, 0, sizeof(syx));
		time_t start = clock();
		if (result[n] == 0) {
			rec(0);
			result[n] = sol;
		} else {
			sol = result[n];
		}
		time_t end = clock();
		cout << sol << endl;
		cout << "Time usage: " << (end - start)<< " clocks" << endl;
	}
}