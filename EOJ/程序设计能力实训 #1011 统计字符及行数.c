#include <stdio.h>
int main(){
    unsigned long int charnum = 0, lines = 0, charnum_L = 0, charnum_LMAX;
    char c;
    while((c=getchar())!=EOF){
        if ((c!='\n')){
            charnum++;
            charnum_L++;
        }
        if ((c=='\n')){
            lines++;
            if (charnum_L > charnum_LMAX) 
                charnum_LMAX = charnum_L;
            charnum_L = 0;
        }
    }
    printf("%ld,%ld,%ld", charnum, lines, charnum_LMAX);
}