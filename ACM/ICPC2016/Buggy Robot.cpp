#include <bits/stdc++.h>
#define MAXL 16
using namespace std;

char maze[55][55];
int m, n;

struct p {
	int x;
	int y;
};

p start, exitp;
string path;
int main() {
	fill(maze[0], maze[0] + 55 * 55, '#');
	cin >> m >> n;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			char tmp;
			cin >> tmp;
			maze[i][j] = tmp;
		}
	}
	cin >> path;
}