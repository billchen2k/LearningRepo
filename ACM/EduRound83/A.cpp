#include <iostream>

using namespace std;

int main(){
	int p;
	cin >> p;
    while(p--){
	    unsigned long m, n;
	    cin >> m >> n;
	    cout << (m % n == 0 ? "YES" : "NO") << endl;
    }

}