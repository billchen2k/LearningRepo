//2019.2.24
#include <iostream>
#include <cstdlib>
using namespace std;
char order[27];
int cmp(const void * pta,const void * ptb){
    char * pa = (char*) pta;
    char * pb = (char*) ptb;
    int orderID_A = 0, orderID_B = 0, i;
    for(i=0; i<27; i++){
        if (toupper(*pa) == order[i]) orderID_A=i;
        if (*pa == '\0') orderID_A = -1;
        if (toupper(*pb) == order[i]) orderID_B=i;
        if (*pb == '\0') orderID_B = -1;
    }
    if (orderID_A == orderID_B){
        return cmp(pa + 1, pb + 1);
    }
    return orderID_A<orderID_B ? -1 : 1;
}
int main(){
    while(cin.getline(order, 27) || !cin.eof()) {
        char toSort[100][21] = {0};
        int i, j;
        for(i = 0; ;i++){
            cin>>toSort[i];
            if (cin.get() == '\n') break;
        }
        qsort(toSort, i + 1, sizeof(toSort[0]), cmp);
        for(j=0;j<=i;j++){
            if(j!=i) cout<<toSort[j]<<" ";
            else cout<<toSort[j]<<endl;
        }
    }
    return 0;
}

