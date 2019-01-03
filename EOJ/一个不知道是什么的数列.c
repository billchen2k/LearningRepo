//
//  main.c
//  Playground_C
//
//  Created by Bill Chen on 2018/10/17.
//  Copyright © 2018 Bill Chen. All rights reserved.
//
#include <stdio.h>
void draw(int length){
   int i;
   if ((length%2)==0){
       for (i=1; i<=length/2 ; i++) printf("%d ", i);
       for (i=length/2; i>0; i--) {
           if (i>1) printf("%d ",i);
           elseprintf("%d \n",i);
       }
   }
   elseif((length%2)==1){
       for (i=1; i<(length+1)/2; i++)  printf("%d ", i);
       for (i = (length+1)/2; i>0; i--){
           if (i>1) printf("%d ", i);
           else  printf("%d\n", i);
       }
   }
}

int main(){
   int length, a;
   while(scanf("%d", &length) != EOF){
       if (length != 0){
           for (a=1; a<=length; a++)
               draw(a);
           printf("\n");
           }
   }
   return0;
}

