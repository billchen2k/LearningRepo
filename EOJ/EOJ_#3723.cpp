#include <iostream>
using namespace std;

int main(){
	int n;
	cin >> n;
	bool *data = new bool[n];
	for (int i = 0; i < n; i++){
		int temp;
		cin >> temp;
		data[temp] = 1;
	}
	int f = 0;
	int out = 0;
	while (f = 1) {
		f = 0;
		for (int i = 0; i < n; i++) {
			if (data[i] == 1) {
				f = 1;
				out++;
				for (int j = 0; j < n;j+=i){
					data[j] = 0;
				}
			}
		}
    }
    cout << out;
}