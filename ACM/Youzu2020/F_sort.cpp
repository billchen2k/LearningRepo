#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	vector<string> s;
	int num = 0;
	string t;
	int len;
	cin >> len;
	while (len--) {
		cin >> t;
		s.push_back(t);
	}
	sort(s.begin(), s.end());
	for (int i = 0; i < s.size() - 1; i++) {
		if (s[i + 1].find(s[i]) == string::npos) {
			if (s[i].size() > 3) {
				if (s[i].substr(s[i].size() - 4) == ".eoj") {
					num++;
				}
			}
		}
	}
	string tmp = s[s.size() - 1];
	if (tmp.size() > 3) {
		if (tmp.substr(tmp.size() - 4) == ".eoj") {
			num++;
		}
	}
		cout << num;
}