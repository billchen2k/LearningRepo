#include <stdio.h>
#include <stdlib.h>

//void sort(void * ptr, int len){
//    int * pt = (int*)ptr;
//    int i, flag=1;
//    while (flag==1){
//        flag=0;
//        for (i=0;i<len-1;i++){
//            if (*(pt+i) > *(pt+i+1)){
//                flag=1;
//                int temp;
//                temp = *(pt+i);
//                *(pt+i) = *(pt+i+1);
//                *(pt+i+1) = temp;
//            }
//        }
//    }
//}

int compare(void * pt1, void * pt2){
    return *(int*)pt1>*(int*)pt2?1:0;
}
int main(){
    int i, n, k;
    scanf("%d", &n);
    int data[100000]={0};
    for (i=0;i<n;i++){
        scanf("%d", data+i);
    }
    //sort(data, n);  //冒泡排序
    qsort(data, n, sizeof(int), compare);
    scanf("%d", &k);
    while (k--){
        int j; //要查询的数组位置
        scanf("%d", &j);
        printf("%d\n", data[j-1]);
    }
}

