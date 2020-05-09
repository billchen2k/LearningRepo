#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> pii;

pii p[1010];
int vis[1010];
int main() {
	int n, m;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].ff, &p[i].ss);
	scanf("%d", &m);
	set<int> s;
	for (int i = 1; i <= m; i++) {
		int x;
		scanf("%d", &x);
		s.insert(x);
		for (int j = 1; j <= n; j++)
			if (p[j].ff <= x && x <= p[j].ss)
				vis[j]++;
	}
	for (int i = 1; i <= n; i++)
		if (vis[i] > 2) {
			printf("impossible");
			return 0;
		}
	vector<int> ans;
	for (int i = 1; i < n; i++)
		if (p[i].ss == p[i + 1].ff) {
			if (vis[i] < 2 && vis[i + 1] < 2 && s.find(p[i].ss) == s.end())
				ans.push_back(p[i].ss), vis[i]++, vis[i + 1]++, s.insert(p[i].ss);
		}
	for (int i = 1; i <= n; i++) {
		for (int j = vis[i]; j < 2; j++) {
			int l = p[i].ff + 1;
			while (s.find(l) != s.end())
				l++;
			s.insert(l), ans.push_back(l), vis[i]++;
		}
	}
	printf("%d\n", ans.size());
	for (auto i : ans)
		printf("%d ", i);
}
