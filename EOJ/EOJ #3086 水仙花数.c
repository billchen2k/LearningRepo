#include <stdio.h>
#include <math.h>
int main(){
    int num;
     int a,b,c,d;
     for (num=1000;num<=9999;num++){
          a=num/1000;
          b=(num-(a*1000))/100;
          c=(num-(a*1000)-(b*100))/10;
          d=num-(a*1000)-(b*100)-(c*10);
          if (pow(a,4)+pow(b,4)+pow(c,4)+pow(d,4) == num) printf("%d\n", num);
          else continue;
     }
     getchar();
     return 0;
}

