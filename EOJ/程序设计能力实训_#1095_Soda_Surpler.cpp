//2019.3.7
#include <iostream>
#include <stdio.h>
using namespace std;
int main(){
    input:
    int e, c, f;
    while (cin >> e >> c >> f && !cin.eof()){
        int sum = 0;
        e += c;
        if (f <= 1){
            cout << "Unvalid input." << endl;
            goto input;
        }
        while (e / f >= 1){
            int temp = e / f;
            e %= f;
            e += temp;
            sum += temp;
        }
        cout << sum << endl;
    }
    return 0;
}