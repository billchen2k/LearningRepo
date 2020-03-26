#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
	while (1) {
		int n = 0;
		map<string, int> points;
		cin >> n;
		if (n == 0)
			break;
		while (n--) {
			string a, b;
			cin >> a >> b;
			points[b] = points.count(b) == 0 ? 1 : points[b] + 1;
			points[a] = points.count(a) == 0 ? 0 : points[a];
		}
		int f = 0;
		for (auto it = points.begin(); it != points.end(); it++) {
			if(it->second == 0){
				f++;
			}
		}
		int result = f == 1 ? 1 : 0;
		cout << (result ? "Yes" : "No") << endl;
	}
}