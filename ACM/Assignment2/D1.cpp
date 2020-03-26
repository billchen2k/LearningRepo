#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int compare(const void *a, const void *b) {
	return (*(int *)a - *(int *)b);
}

int main() {
	int a;
	while (cin >> a) {
		int n = a;
		int na[100000], nb[100000];
		for (int i = 0; i < n; i++) {
			int t;
			cin >> t;
			na[i] = t;
		}
		for (int i = 0; i < n; i++) {
			int t;
			cin >> t;
			nb[i] = t;
		}
		qsort(na, a, sizeof(int), compare);
		qsort(nb, a, sizeof(int), compare);
		vector<int> sum;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < a; j++) {
				if (i > 0) {
					int top = sum[a - 1];
					if (na[i] + nb[j] > top) {
						break;
					}
				}
				sum.push_back(na[i] + nb[j]);
				if (i > 0)
					sort(sum.begin(), sum.end());
			}
			int top = sum[a - 1];
			if (na[i] > top) {
				break;
			}
		}
		int i = 0;
		for (auto it = sum.begin(); i < a; it++) {
			cout << *it;
			if (i != a - 1) {
				cout << " ";
			}
			i++;
		}
	}
}
