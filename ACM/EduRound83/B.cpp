#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int ifGood(vector<int> a){

	for (int i = 0; i < a.size(); i++) {
		a[i] = a[i] - i;
	}
	int oldSize = a.size();
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	return oldSize == a.size();
}

int findDup(vector<int> a){

}

void print(vector<int> a){
	for (int i = 0; i < a.size();i++){
		cout << a[i] << " ";
	}
	cout << endl;
}

int main(){
	int p;
	cin >> p;
    while(p--){
	    vector<int> a;
	    int len;
	    cin >> len;
		while(len--) {
			
			int temp;
			cin >> temp;
			a.push_back(temp);
		}

		while (!ifGood(a)) {
			vector<int> dup = a;
			for (int i = 0; i < dup.size(); i++) {
				dup[i] = dup[i] - i;
			}
			for (int i = 0; i < dup.size(); i++) {
				for (int j = i; j < dup.size(); j++) {
					if (dup[i] == dup[j]) {
						swap(a[i], a[j]);
					}
				}
			}
			//swap(a[rand() % (a.size() - 1)], a[rand() % (a.size() - 1)]);
		}
		print(a);
    }
    return 0;
}