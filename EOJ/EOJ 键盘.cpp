#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int nu, np, nup, nk, sum = 0, c = 0;
		vector<int> ku, kp;
		cin >> nu >> np >> nup;
		cin >> nk;
		while (nk--) {
			int p;
			string tmp;
			cin >> p >> tmp;
			if (tmp == "USB") {
				ku.push_back(p);
			} else {
				kp.push_back(p);
			}
		}
		sort(ku.begin(), ku.end());
		sort(kp.begin(), kp.end());
		for (; nu > 0 && ku.size() > 0; nu--) {
			sum += ku.front();
			c++;
			if (ku.size() != 0)
				ku.erase(ku.begin());
		}
		for (; np > 0 && kp.size() > 0; np--) {
			sum += kp.front();
			c++;
			if (kp.size() != 0)
				kp.erase(kp.begin());
		}
		for (; nup > 0 && (ku.size() > 0 || kp.size() > 0); nup--) {
			int a = ku.size() != 0 ? ku.front() : INT_MAX;
			int b = kp.size() != 0 ? kp.front() : INT_MAX;
			if (a < b) {
				sum += a;
				ku.erase(ku.begin());
			} else {
				sum += b;
				kp.erase(kp.begin());
			}
			c++;
		}
		cout << "case #" << i << ":" << endl;
		cout << c << " " << sum << endl;
	}
}
