#include <iostream>
#include <string>
using namespace std;

int main(){
    int T;
    scanf("%d\n",&T);
    
    for (int i = 0; i < T; i++) {
        string s,t;
        getline(cin,s);
        getline(cin,t);
        int count = 0,len = t.length(),f = 0;
        
        while((f = s.find(t,f)) != -1){
            f += len;
            count++;
        }
        printf("case #%d:\n%d\n",i,count);
    }
    return 0;
}