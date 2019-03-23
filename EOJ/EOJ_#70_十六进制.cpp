#include <iostream>
#include <cstring>
using namespace std;
int main(){
    string input;
    input.append("0x");
    cin.get();
    cin.get();
    char ch;
    while (ch = cin.get() && ((ch >= '0' && ch <= '9' )|| (ch >= 'a' && ch <= 'f'))) {
        input.append(&ch);
    }
    
}