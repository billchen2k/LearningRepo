#include <bits/stdc++.h>
using namespace std;

int main() {
	int a = random();
	int b = random();
	double da = (double)a;
	double db = (double)b;
	float fa = (float)da;
	float fb = (float)db;
	printf("%.32f, %d, %d", fa, a, fa == a);
}