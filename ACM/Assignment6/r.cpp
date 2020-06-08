#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
typedef long long ll;
const ll maxn = 1010;
using namespace std;
#define inf 0x3f3f3f3f
#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b

ll T, S, D;

int map1[maxn][maxn], s[maxn], e[maxn];

int main() {
	int a, b, c;
	int m = -1;
	while (scanf("%lld %lld %lld", &T, &S, &D) != EOF) {
		memset(map1, inf, sizeof(map1));
		memset(s, 0, sizeof(s));
		memset(e, 0, sizeof(e));
		for (int i = 1; i < maxn; i++)
			map1[i][i] = 0;
		for (int i = 1; i <= T; i++) {
			scanf("%d%d%d", &a, &b, &c);
			map1[a][b] = min(map1[a][b], c);
			map1[b][a] = min(map1[b][a], c);
			a = max(a, b), m = max(a, m);
		}
		for (int k = 1; k <= m; k++)
			for (int i = 1; i <= m; i++)
				if (map1[i][k] != inf)
					for (int j = 1; j <= m; j++)
						map1[i][j] = min(map1[i][j], map1[i][k] + map1[k][j]);
		for (int i = 1; i <= S; i++)
			cin >> s[i];
		for (int i = 1; i <= D; i++)
			cin >> e[i];
		ll min = inf;
		for (int i = 1; i <= S; i++) {
			for (int j = 1; j <= D; j++)
				min = min(min, map1[s[i]][e[j]]);
		}
		printf("%lld\n", min);
		
	}
	return 0;
}