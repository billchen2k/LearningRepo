#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

int board[8][8] = {0};
vector<pair<int, int>> as;
vector<pair<int, int>> bs;


int main(){
	int a;
	cin >> a;
	for (int i = 0; i < a; i++) {
		string t;
		cin >> t;
		board[t[0] - 'A'][t[1] - '1'] = 1;
		as.push_back(make_pair<int, int>(t[0] - 'A', t[1] - '1'));
	}
	int b;
	cin >> b;
	for (int i = 0; i < b; i++) {
		string t;
		cin >> t;
		board[t[0] - 'A'][t[1] - '1'] = 2;
		bs.push_back(make_pair<int, int>(t[0] - 'A', t[1] - '1'));
	}
	if(as.size() > bs.size()){
		cout << "Cuber QQ";
	}
	else{
		cout << "Quber CC";
	}
	return 0;
}