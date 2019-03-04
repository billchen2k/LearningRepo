#include <stdio.h>

int main(){
     int line, i;
     scanf("%d", &line);
     getchar();
   //  setbuf(stdin, NULL); //清空缓存区
     for(i=0;i<line;i++){
          int c;
          int characters=0, numbers=0, others=0;
          while ( (c=getchar())!= '\n'){
               if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) characters++;
               elseif (c >= 48 && c <= 57) numbers++;
               else others++;
          }
          printf("character:%d\nnumber:%d\nothers:%d\n",characters,numbers,others);
     }
}note.pdf

