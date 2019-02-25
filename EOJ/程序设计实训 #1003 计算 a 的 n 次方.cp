//2019.2.24
#include <iostream>
#define ULL unsigned long long
using namespace std;
int main(){
    int len, i;
    cin >> len;
    for (i=0; i<len; i++){
        ULL input, output = 1;
        int pow, j;
        cin>>input>>pow;
        for (j=0;j<pow;j++){
            output *= input;
        }
        cout<<"case #"<<i<<":\n"<<output<<endl;
    }
    return 0;
}
