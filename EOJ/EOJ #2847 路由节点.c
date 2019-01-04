#include <stdio.h>
int main(){
    long long int n;
        while(scanf("%lld", &n)!=EOF){
        long long int points=1;
        int i;
        for(i=0;i<4;i++) {
            points*=n;
            n--;
        }
        printf("%lld\n", points/24); //Cn4
    }
}
