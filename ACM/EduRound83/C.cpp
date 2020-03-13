#include <iostream>
#include <vector>
#include <algorithm>

#define ULL unsigned long long
using namespace std;

int ifAllO(vector<ULL> a){
	for (int i = 0; i < a.size(); i++){
		if(a[i] > 0){
			return 0;
		}
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int v, k;
		cin >> v >> k;
		vector<ULL> a;
		
		while (v--) {
			ULL temp;
			cin >> temp;
			a.push_back(temp);
		}
		vector<bool> flag(100);
		int fail = 0;
		int frac = 0;
		while(!ifAllO(a)){
			frac++;
			for (int i = 0; i < a.size(); i++) {
				
				if (a[i] < 9 && a[i] > 1) {
					fail = 1;
					goto print;
				}
				if(a[i] == 0){
					continue;
				}
				if (a[i] % 9 == 0) {
					a[i] = a[i] / 9;
					if (flag[frac] == true){
						fail = 1;
						goto print;
					}
					flag[frac] = true;
				}
				else{
					a[i]--;
				}
			}
		}
	print:
		cout << (fail == 1 ? "NO" : "YES") << endl;
	}
	return 0;
}