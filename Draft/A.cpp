#include <iostream>
#include <string>
#include <time.h>

using namespace std;

int main(){
	time_t start = clock();
	string a = "a";
	for (int i = 0;i<50000;i++){
		a = a + to_string(i);
	}
	time_t end = clock();
	cout << (end - start) / (double)CLOCKS_PER_SEC << " s" << endl;
}