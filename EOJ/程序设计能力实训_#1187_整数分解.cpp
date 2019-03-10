//2019.3.9
#include <iostream>
using namespace std;
int main(){
    int num;
    while(cin >> num && !cin.eof()){
        if(num%2==0){
            printf("%d %d\n", 2, num / 2);
        }
        else{
            int temp = 2;
            while (!(num%temp==0))
                temp++;
            printf("%d %d", temp, num / temp);
        }
    }
    return 0;
}