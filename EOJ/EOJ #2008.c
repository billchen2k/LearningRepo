
#include <stdio.h>

int main(){
    int i, temp, storeNum, searchNum;
    scanf("%d", &storeNum);
    short library[501] = {0};
    for (i=0;i<storeNum;i++){
        scanf("%d", &temp);
        library[temp]=1;
    }scanf("%d", &searchNum);
    for (i=0; i<searchNum; i++){
        scanf("%d", &temp);
        if (library[temp]==1) puts("yes!");
        elseputs("no!");
    }
    return 0;
}C

