#include <iostream>
#include <string.h>
using namespace std;
int main(){
    int len;
    cin >> len;
    cin.get();
    while (len--){
        char ch;
        while ((ch=cin.get())!='\n'){
            printf("%02d", (int)(ch - 'a' + 1));
        }
        cout << endl;
    }
    return 0;
}