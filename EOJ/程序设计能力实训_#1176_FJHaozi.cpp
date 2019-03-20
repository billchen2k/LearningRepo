#include <iostream>
#include <string>
using namespace std;
int main(){
    string input;
    getline(cin, input);
    for (int i = 0; i < input.length();i++){
        input[i] = toupper(input[i]);
    }
    cout << input;
    return 0;
}