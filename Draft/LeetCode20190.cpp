#include <iostream>
#include <string>
using namespace std;
string source, target;
int result = -1;
int solve(int pt, int len) {
	if (pt + len <= target.length()) {
		if (source.find(target.substr(pt, len)) != string::npos) {
			len++;
			solve(pt, len);
		} else {
			result++;
			pt = pt + len - 1;
			len = 1;
			solve(pt, len);
		}
	} else {
		result++;
		return 0;
	}
}
int main() {
	cin >> source >> target;
	for (int i = 0; i < source.length(); i++) {
		if (target.find(source[i]) == string::npos) {
			goto ending;
		}
	}
	result = 0;
	solve(0, 1);
ending:
	cout << result;
	return 0;
}