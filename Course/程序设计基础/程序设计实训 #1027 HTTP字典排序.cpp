#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
int compare(const void * pa, const void *pb){
    char *cpa=(char *)pa;
    char *cpb=(char *)pb;
    return strcmp(cpa, cpb);
}
int main(){
    char links[100][1000]={0};
    int len, i=0, j=0;
    cin>>len;
    while(i<len) {
        cin>>links[j];
        char http[6];
        strncpy(http, links[j], 5);
        if (strcmp(http, "http:")==0) j++;
        else memset(links[j], 0, sizeof(links[j]));
        i++;
    }
    qsort(links[0], j, sizeof(links[j]), compare);
    for(i=0;i<j;i++) cout<<links[i]<<endl;
    return 0;
}