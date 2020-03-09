#include <iostream>

using namespace std;

int main(){
    unsigned long long m, n, k;
	cin >> m >> n >> k;
	cout << (m / k + 1 * !!(m % k)) * (n / k + 1 * !!(n % k));
}