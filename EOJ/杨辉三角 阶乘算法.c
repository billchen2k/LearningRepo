#include <stdio.h>

int factorial(int num){
     int i, out = 1;
     for (i=num;i>=1;i--){
          out = out * i;
     }
     return out;
}

int combinatory(int down, int up){
     if (up==0 || down==0) return 1;
     elseif (up==down) return 1;
     else{
          if (up>=down/2) up=down-up;
          returnfactorial(down)/(factorial(up)*factorial(down-up));
     }
     return 0;
}

int main(){
    int length;
     while(scanf("%d", &length)!=EOF){
          if (length != 0){
               int i1, i2;
               for(i1=0;i1<length;i1++){
                    for(i2=0;
                        i2<=i1;i2++){
                         if (i2<i1) printf("%d ",combinatory(i1, i2));
                         elseif(i2==i1) printf("%d\n",combinatory(i1, i2));
                    }
               }
               printf("\n");
          }
     }
     return 0;
}


