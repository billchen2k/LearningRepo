#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
	unsigned long long int input;
	cin >> input;
	int data[100000] = {0};
	int len = 0;
	while (input > 0) {
		input--;
		data[len] = input % 26;
		input /= 26;
		len++;
	}
	for (int i = len - 1; i >= 0; i--) {
		cout << char('A' + data[i]);
	}
	cout << endl;
}
