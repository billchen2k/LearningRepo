#include <iostream>
#include <string.h>
using namespace std;
int main(){
    unsigned long long int data[75];
    data[0] = 0;
    data[1] = data[2] = 1;
    for (int i = 3;i < 75; i++){
        data[i] = data[i - 1] + data[i - 2] + data[i - 3];
    }
    int len;
    cin >> len;
    for(int i = 0; i < len;i++){
        int num;
        cin >> num;
        printf("case #%d:\n", i);
        cout << data[num] << endl;
    }
    return 0;
}