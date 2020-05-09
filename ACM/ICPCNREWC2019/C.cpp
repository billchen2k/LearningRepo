
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>

#define ll long long
using namespace std;

typedef struct canvas {
	ll start;
	ll end;
	int pegcount;
} canvas;

int main() {
	ll n, p, q, r;
	cin >> n;
	vector<canvas> c;
	vector<ll> pegs;
	vector<ll> ans;
	while (n--) {
		canvas newc;
		ll a, b;
		cin >> a >> b;
		newc.start = a;
		newc.end = b;
		newc.pegcount = 0;
		c.push_back(newc);
	}
	cin >> n;
	int pos = 0;
	while (n--) {
		ll a;
		cin >> a;
		pegs.push_back(a);
		for (int i = pos; i < c.size(); i++) {
			if (a >= c[i].start && a <= c[i].end) {
				c[i].pegcount++;
				if (c[i].pegcount > 2) {
					cout << "impossible" << endl;
					exit(0);
				}
			}
		}
	}
	for (auto it = c.begin(); it != c.end(); it++) {
		auto last = it - 1;
		auto next = it + 1;
		if (it->pegcount == 0) {
			pos = it->start;
			if (last->pegcount == 2) {
				pos = it->end;
				if (next != c.end() && next->start == it->end) {
					next->pegcount++;
				}
			}
			ans.push_back(pos);
			pegs.push_back(pos);
			it->pegcount++;
		}

		if (it->pegcount == 1) {
			if (next != c.end() && next->start == it->end) {
				if (next->pegcount == 2) {
					ans.push_back(it->end - 1);
					pegs.push_back(it->end - 1);
				} else {
					ll pos = it->end;
					if (find(pegs.begin(), pegs.end(), pos) != pegs.end()) {
						pos--;
					} else {
						next->pegcount++;
					}
					ans.push_back(pos);
					pegs.push_back(pos);
				}
			} else {
				ll pos = it->end;
				if (find(pegs.begin(), pegs.end(), pos) != pegs.end()) {
					pos--;
				}
				ans.push_back(pos);
				pegs.push_back(pos);
			}
			it->pegcount++;
		}
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++) {
		printf("%lld ", ans[i]);
	}
}