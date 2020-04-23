#include <algorithm>
#include <iostream>


using namespace std;

int number[101];
int level[101];
int main() {
	int n, t;
	cin >> n;
	while(n--){
		cin >> t;
		for (int i = 0; i < t; i++){
			int ta, tb;
			cin >> ta >> tb;
			number[i] = ta;
			level[i] = tb;
		}
	}
	
}