#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
	int n;
	cin >> n;
	while (n--) {
		map<string, map<string, int>> data;
		int m;
		cin >> m;
		while (m--) {
			string a, b;
			int c;
			cin >> b >> a >> c;
			if (data.count(a) == 0) {
				map<string, int> t;
				data[a] = t;
			}
			data[a][b] = data[a].count(b) == 0 ? c : c + data[a][b];
		}
		for (auto it = data.begin(); it != data.end(); it++) {
			cout << it->first << endl;
			for (auto its = it->second.begin(); its != it->second.end(); its++) {
				cout << "   |----" << its->first << "(" << its->second << ")" << endl;
			}
		}
		if (n) {
			cout << endl;
		}
	}
}