#include <stdio.h>
#include <math.h>
int main(){
    int len, i;
    scanf("%d", &len);
    while(len--){
        char input[33];
        scanf("%s", input);
        int j,k,sum;
        for (j=0;j<4;j++){
            sum=0;
            for (k=0;k<8;k++){
                if (input[8*j+k]=='1') sum+= (int)(pow(2,8-k-1)+0.5);
            }
            if (j!=3) printf("%d.", sum);
            elseprintf("%d\n", sum);
        }
    }
    return 0;
}

//#include <stdio.h>
//#include <string.h>
//#include <math.h>
//int Convert (char * input){
//    int length = strlen(input);
//    int output=0, i, j;
//    for (i=length-1, j=0; i>=0; i--,j++){
//        if (input[i]=='1') output+=(int)(pow(2,j)+0.5);
//    }
//    return output;
//}
//int main(){
//    int len, i;
//    scanf("%d", &len);
//    for (i=0;i<len;i++){
//        char input[33];
//        setbuf(stdin, NULL);
//        scanf("%s", input);
//        char a[9], b[9], c[9], d[9];
//        strncpy(a, input, 8);
//        strncpy(b, input+8, 8);
//        strncpy(c, input+16, 8);
//        strncpy(d, input+24, 8);
//        a[8]='\0';b[8]='\0';c[8]='\0';d[8]='\0';
//        printf("%d.%d.%d.%d\n", Convert(a),Convert(b),Convert(c),Convert(d));
//    }
//    return 0;
//}

