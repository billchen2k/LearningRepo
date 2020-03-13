#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int ifGood(string s) {
	string rs = s;
	reverse(rs.begin(), rs.end());
	return (s == rs);
}

string act(string s) {
	string rs = s;
	reverse(rs.begin(), rs.end());
	return to_string(stoull(s) + stoull(rs));
}

int main() {
	string n;
	while (cin >> n) {
		string origin = n;
		int cnt = 0;
		string proc[10000];
		do {
			if (ifGood(n))
				break;
			n = act(n);
			proc[cnt] = n;
			cnt++;
		} while (1);

		cout << cnt << endl;
		cout << origin;
		for (int i = 0; i < cnt; i++) {
			cout << "--->" << proc[i];
		}
		cout << endl;
	}
	return 0;
}