//2019.2.25
#include <iostream>
#include <cstdlib>
using namespace std;
int FactorialZeros(int input){
    long long int fac= 1;
    int zeros = 0;
    for (int i = input; i>0; i--){
        fac *= input--;
    }
    string s;
    s = to_string(fac);
    for (int i = (int)s.length()-1; i>=0; i--){
        if (s[i]=='0') zeros++;
        else break;
        if (s[i-1]=='0') continue;
        else break;
    }
    return zeros;
}
int main(){
    int len, i=0;
    cin>>len;
    while(len--){
        int input;
        cin>>input;
        cout<<"case #"<<i<<":\n"<<FactorialZeros(input)<<endl;
        i++;
    }
}
