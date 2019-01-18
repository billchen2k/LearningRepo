#include <iostream>
#include <iomanip>
using namespace std;
int main(){
    int len;
    cin>>len;
    while(len--){
        double proA[6];
        int i;
        long long int sumA=0;
        for (i=0;i<6;i++){
            cin>>proA[i];
            sumA+=proA[i];
        }
        long long int rateA[6];
        for(i=0;i<6;i++){
            rateA[i]=(i+1)*proA[i];
        }
        long long int max=rateA[0];
        for(i=0;i<6;i++){
            if (rateA[i]>max) max=rateA[i];
        }
        double expec=(double)max/(double)sumA;
        cout<<fixed<<setprecision(12)<<expec<<endl;
    }
    return 0;
}
