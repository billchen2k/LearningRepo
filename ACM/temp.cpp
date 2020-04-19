#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// int a[] = {1, 2, 3, 4};

// bool cmp(int a[], vector<int> va) {
// 	for (int i = 0; i < va.size(); i++) {
// 		if (a[i] != va[i]) {
// 			return false;
// 		}
// 	}
// 	return true;
// }

// void dfs(int depth, vector<int> va, int count) {
// 	if (va.size() == 4) {
// 		cout << count << ":";
// 		for (int i = 0; i < 4;i++){
// 			cout << va[i] << " ";
// 		}
// 		cout << endl;
// 		return;
// 	}
// 	int i = 0;
// 	for (i = 0; i < 4; i++) {
// 		if(find(va.begin(), va.end(), a[i]) == va.end()){
// 			break;
// 		}
// 	}
// 	va.push_back(a[i]);
// 	dfs(depth + 1, va, count + 1);
// 	va.pop_back();
// 	int j = 0;
// 	for (j = 0; j < 4; j++) {
// 		if (find(va.begin(), va.end(), a[i]) == va.end() && j!=i) {
// 			break;
// 		}
// 	}
// 	va.push_back(a[j]);
// 	dfs(depth + 1, va, count + 1);
// 	va.pop_back();
// }

// int main(){
// 	vector<int> va;
// 	dfs(0, va, 0);
// }

void swap(char *a, char *b) {
	int m;
	m = *a;
	*a = *b;
	*b = m;
}
int c = 0;
void perm(char a[], int k, int m) {
	int i;
	if (k > m) {
		cout << c << ":";
		for (i = 0; i <= m; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
		c++;
	} else {
		for (i = k; i <= m; i++) {
			swap(&a[k], &a[i]);
			perm(a, k + 1, m);
			swap(&a[k], &a[i]);
		}
	}
}

int main() {
	int n;
	char a[12];
	cin >> n;
	for (int i = 0; i < n; i++)
		a[i] = '0' + i + 1;
	perm(a, 0, n - 1);

	return 0;
}