#include <stdio.h>
int main(){
     int n;
     while (scanf("%d", &n)!=EOF){
          int book[30],booknew[30];
          int i, max, i2, maxposition;
          for (i=0;i<n;i++) scanf("%d", &book[i]);
          for(i2=0;i2<n;i2++){
               max=book[0]; maxposition=0;
               for(i=0;i<n;i++){
                    if (book[i]>max){
                         max = book[i]; maxposition = i;
                    }
               }
               booknew[n-1-i2]=max;
               book[maxposition]=0;
               
          }
          for (i=0;i<n;i++) printf("%d\n", booknew[i]);
     }
     return 0;
}

          
//          for (i2=0;i2<n;i2++){
//               max=book[0];
//               for (i=0;i<(n-i2);i++){
//                    if (book[i]>=max) {
//                         max=book[i];
//                         maxposition=i;
//                    }
//               }
//               book[i]=0;
//               booknew[n-i2]=max;
//          }

