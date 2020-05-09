#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

struct st {
	int num;
	long score;
};

int n, w;

long *score;
long *ranking;

int cmp(const void *a, const void *b) {
	st sa = *(st *)a;
	st sb = *(st *)b;
	return sb.score > sa.score;
}

void newrank() {
	st *s = new st[n];
	for (int i = 0; i < n; i++) {
		s[i].num = i;
		s[i].score = score[i];
	}
	qsort(s, n, sizeof(st), cmp);
	int rank = 1;
	long last = 0;
	for (int i = 0; i < n; i++) {
		if (last != s[i].score) {
			last = s[i].score;
			rank = i + 1;
		}
		ranking[s[i].num] += rank;
	}
}

int main() {
	cin >> n >> w;
	score = new long[n];
	ranking = new long[n];
	memset(score, 0, n * sizeof(long));
	memset(ranking, 0, n * sizeof(long));
	for (int i = 0; i < w; i++) {
		int len;
		cin >> len;
		while (len--) {
			int t;
			cin >> t;
			score[t - 1] += 1;
		}
		newrank();
	}
	for (int i = 0; i < n; i++) {
		printf("%f\n", (double)ranking[i] / w);
	}
}
