//2019.3.7
//DP
#include <iostream>
using namespace std;
int main(){
    unsigned long long int mem[1000000];
    mem[0] = 1;
    mem[1] = 2;
    for (int i = 2; i < 1000000; i++){
        if (i % 2 == 0){
            mem[i] = mem[i - 1];
        }
        else{
            mem[i] = (mem[i - 1] + mem[(i - 1) / 2]) % 1000000000;
        }
    }
    int len;
    cin >> len;
    for (int k = 0; k < len; k++){
        int num;
        cin >> num;
        cout << "case #" << k << ":" << endl;
        cout << mem[num - 1] << endl;
    }
    return 0;
}