#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long int LL;
int isEcho(vector<LL> &data) {
	int flag = true;
	for (int i = 0, j = data.size() - 1; i <= j; i++, j--) {
		if (data[i] != data[j]) {
			flag = false;
			break;
		}
	}
	return flag;
}
int main() {
	int len;
	cin >> len;
	vector<LL> array(len);
	for (int i = 0; i < len; i++) {
		LL temp;
		cin >> temp;
		array.push_back(temp);
	}
	int count = 0;
	int pa = 0, pb = array.size() - 1;
	while (!isEcho(array)) {
		if (array[pa] == array[pb]){
			pa++;
			pb--;
			continue;
	    }
		int tempa = array[pa] + array[pa + 1];
		int tempb = array[pb] + array[pb - 1];
		if (tempa <= tempb) {
			array.erase(begin(array), begin(array) + 1);
			array.insert(begin(array), tempa);
		} else {
			array.erase(end(array) - 1, end(array));
			array.insert(end(array), tempa);
		}
		count++;
	}
	cout << count;
}