#include <stdio.h>

int main(){
     int line, i;
     scanf("%d", &line);
     for(i=0;i<line;i++){
          longunsignedint a,b;
          scanf("%lu %lu", &a, &b);
          longunsigned GCD, LCM, temp;
          GCD=LCM=temp=1;
          for(temp=1;temp<=a && temp <= b;temp++){
               if (a%temp == 0 && b%temp == 0) GCD = temp;
          }
          for(temp=a*b;temp>=1;temp--){
               if (temp%a ==0 && temp%b == 0) LCM = temp;
          }
          printf ("%d %d\n",GCD ,LCM);
     }
     return 0;
}

