#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
	int a, b, c;
	while (!cin.eof()) {
		cin >> a >> b >> c;
		unordered_set<string> sa, sb, sc;
		string t;
		while (a--) {
			cin >> t;
			sa.insert(t);
		}
		while (b--) {
			cin >> t;
			sb.insert(t);
		}
		while (c--) {
			cin >> t;
			sc.insert(t);
		}
		unordered_set<string> out;
		for (string one : sb) {
			if (sa.count(one) != 0 && sc.count(one) == 0) {
				out.insert(one);
			}
		}
		if (out.size() == 0) {
			cout << "No enemy spy";
		} else {
			for (auto it = out.begin(); it != out.end(); it++) {
				if (it != out.begin())
					cout << " ";
				cout << it->data();
			}
		}
	}
}
