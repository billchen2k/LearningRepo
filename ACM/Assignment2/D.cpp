#include <algorithm>
#include <iostream>
#include <math.h>
#include <set>
#include <string>

using namespace std;

int main() {
	int a;
	while (cin >> a) {
		multiset<int> sa, sb;
		int n = a;
		while (n--) {
			int t;
			cin >> t;
			sa.insert(t);
		}
		n = a;
		while (n--) {
			int t;
			cin >> t;
			sb.insert(t);
		}
		multiset<int> sum;
		int i = 0, j = 0;
		for (auto it = sa.begin(); it != sa.end(); it++, i++) {
			for (auto its = sb.begin(); its != sb.end(); its++, j++) {
				sum.insert(*it + *its);
				if (sum.size() > a) {
					auto m = max_element(sum.begin(), sum.end());
					sum.erase(m);
				}
			}
		}
		for (auto it = sum.begin(); it != sum.end(); it++) {
			cout << *it;
			if (i != a - 1) {
				cout << " ";
			}
		}
		cout << endl;
	}
}