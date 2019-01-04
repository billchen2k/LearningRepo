#include <stdio.h>
#include <string.h>
//减少count中对应数字英文的所有字母
void cuter(int * count, char toCut[]){
    int i,j=(int)strlen(toCut);
    for(i=0;i<j;i++){
        char ch=toCut[i];
        count[ch-'A']--;
    }
}
int main(){
    int len, i;
    scanf("%d", &len);
    getchar();
    for (i=0;i<len;i++){
        char ch;
        //count用来存储输入数据，save用来存储h将要输出的数字；
        int count[26]={0}, save[10]={0};
        while ((ch=getchar())!='\n'){
            count[ch-'A']++;
        }
        while(count['Z'-'A']>0){save[0]++; cuter(count, "ZERO");}
        while(count['X'-'A']>0) {save[6]++; cuter(count, "SIX");}
        while(count['S'-'A']>0) {save[7]++; cuter(count, "SEVEN");}
        while(count['V'-'A']>0) {save[5]++; cuter(count, "FIVE");}
        while(count['F'-'A']>0) {save[4]++; cuter(count, "FOUR");}
        while(count['R'-'A']>0) {save[3]++; cuter(count, "THREE");}
        while(count['W'-'A']>0) {save[2]++; cuter(count, "TWO");}
        while(count['G'-'A']>0) {save[8]++; cuter(count, "EIGHT");}
        while(count['I'-'A']>0) {save[9]++; cuter(count, "NINE");}
        while(count['O'-'A']>0) {save[1]++; cuter(count, "ONE");}
        int j, k;
        //打印
        printf("case #%d:\n", i);
        for(j=0;j<=9;j++){
            for(k=save[j];k>0;k--) printf("%d", j);
        }
        printf("\n");
    }
    return 0;
}
