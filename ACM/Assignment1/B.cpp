#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char ch;
		vector<int> a, b;
		string sa, sb;
		cin >> sa >> sb;
		for (int i = 0; i < sa.length(); i++) {
			a.push_back(sa[i] - '0');
		}
		for (int i = 0; i < sb.length(); i++) {
			b.push_back(sb[i] - '0');
		}
		int r = max(a.size(), b.size()), add = 0;
		vector<int> c(r + 1);
		if (a.size() < b.size()) {
			a.swap(b);
		}
		int gap = a.size() - b.size();
		while (gap--) {
			b.insert(b.begin(), 0);
		}
		while (r) {

			c[r] = (a[r - 1] + b[r - 1] + add) % 10;
			add = (a[r - 1] + b[r - 1] + add) / 10;
			r--;
		}
		c[r] += add;
		if (c[0] == 0)
			c.erase(c.begin());

		cout << "Case " << i + 1 << ":" << endl;
		cout << sa << " + " << sb + " = ";
		for (int i = 0; i < c.size(); i++) {
			cout << c[i];
		}
		cout << endl;
		if (i != n - 1) {
			cout << endl;
		}
	}

	return 0;
}