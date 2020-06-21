#include <bits/stdc++.h>
#define MAXL 10
#define INF 0x1f1f1f1f
#define long unsigned long long
using namespace std;

int n, q;
long good[MAXL];
long d[MAXL * MAXL];

inline long read() {
	int sgn = 1;
	long cnt = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			sgn = -sgn;
		ch = getchar();
	}
	while ('0' <= ch && ch <= '9') {
		cnt = cnt * 10 + (ch - '0');
		ch = getchar();
	}
	return sgn * cnt;
}

void build(int s, int t, int p) {
	if (s == t) {
		d[p] = good[s];
		return;
	}
	int m = (s + t) / 2;
	build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
	d[p] = min(d[p * 2], d[(p * 2) + 1]);
}

int query(int l, int r, int s, int t, int p) {
	// [l,r] 为查询区间,[s,t] 为当前节点包含的区间,p 为当前节点的编号
	if (l <= s && t <= r)
		return d[p]; // 当前区间为询问区间的子集时直接返回当前区间的和
	int m = (s + t) / 2, value = 0;

	value = min(query(l, r, s, m, p * 2), query(l, r, m + 1, t, p * 2 + 1));
	// 如果左儿子代表的区间 [l,m] 与询问区间有交集,则递归查询左儿子

	// 如果右儿子代表的区间 [m+1,r] 与询问区间有交集,则递归查询右儿子
	return value;
}

int main() {
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		good[i] = read();
	}
	fill(d, d + MAXL * MAXL, INF);
	build(0, n - 1, 1);
	// cout << query(1, 3, 0, n - 1, 1);
	while (q--) {
		long v, b, c;
		v = read();
		b = read();
		c = read();
		long total = log(v);
		long rest = v;
		int buyed = 0;
		query(b, c, 0, n - 1, 1);
		for (long i = b - 1; i < c; i++) {
			if (rest >= good[i]) {
				rest = rest % good[i];
				buyed++;
				if (buyed > total)
					break;
			}
		}
		printf("%llu\n", rest);
	}
	return 0;
}