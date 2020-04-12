#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

bool cmp(string a, string b) {

	transform(a.begin(), a.end(), a.begin(), ::tolower);
	transform(b.begin(), b.end(), b.begin(), ::tolower);
	if (a.compare(b) <= 0 )
		return true;
	return false;
}
int main() {

	string a[200];
	string temp;
	int n, i;
	int num, j;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> num;
		getchar();
		for (j = 0; j < num; j++)
			getline(cin, a[j]);

		sort(a, a + num, cmp);
		cout << "case #" << i << ":" << endl;
		for (j = 0; j < num; j++)
			cout << a[j] << endl;
	}

	return 0;
}