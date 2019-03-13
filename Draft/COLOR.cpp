#include <iostream>
using namespace std;
int main(){
    cout << "\033[2J\033[0;0H";
    for (int i = 0; i < 129;i++){
        printf("\033[%dm\\033[%dm)\033[0m\n\033[?25lh", i, i);
    }
    int temp;
    cin >> temp;
}