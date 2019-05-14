#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
	string input;
	cin >> input;
	int flags[256] = {0}, lenmax = 0, left = 0;
	for (int i = 0; i < input.size(); ++i) {
		int index = int(input[i]);
		if (flags[index] == 0 || flags[index] < left) {
			lenmax = max(lenmax, i - left + 1);
		} else {
			left = flags[index];
		}
		flags[index] = i + 1;
	}
	cout << lenmax;
}