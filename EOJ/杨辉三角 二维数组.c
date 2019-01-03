#include <stdio.h>

int main(){
     int length;
     while(scanf("%d", &length)!=EOF){
          if (length!=0){
               int i1,i2,i3;
               int matrix[30][30]={0};
               for (i1=0;i1<length;i1++) matrix[i1][i1]=1;
               for (i1=0;i1<length;i1++) matrix[i1][0]=1;
               for (i2=1;i2<length;i2++) {
                    for (i3=1;i3<length;i3++){
                         matrix[i2][i3] = matrix[i2-1][i3-1] + matrix[i2-1][i3];
                    }
               }
               for (i2=0; i2<length; i2++){
                    for (i3=0; i3<=i2; i3++){
                         if (i3<i2) printf("%d ",matrix[i2][i3]);
                         elseif(i3==i2) printf("%d\n", matrix[i2][i3]);
                    }
               }
               printf("\n");
          }
     }
     return 0;
}

