#include <iostream>
using namespace std;

void move(int n, char a, char b) {
	cout << n << " from " << a << "->" << b << endl;
}
void hanoi(int n, char a, char b, char c) { //把n个盘子从a柱子移动到c柱子
	if (n > 0) {
		hanoi(n - 1, a, c, b); // 将a上的n-1个盘子移到b，c做辅助
		move(n, a, c);	       // 把n从a移动到c
		hanoi(n - 1, b, a, c); // 把b上n-1个盘子移到c，a做辅助
	}
}

int main() {
	int n;
	while (cin >> n) {
		char a = 'a', b = 'b', c = 'c';
		hanoi(n, a, b, c); //把n个盘子从a柱子移动到c柱子 b做辅助
	}
	return 0;
}