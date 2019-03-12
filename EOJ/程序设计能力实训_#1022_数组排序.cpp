#include <iostream>
#include <string.h>
using namespace std;
typedef struct{
    int num = 0;
    int count = 0;
}number;
int cmp(const void *pa, const void *pb){
    number *pta = (number *)pa;
    number *ptb = (number *)pb;
    if (ptb->count != pta->count)
        return ptb->count - pta->count;
    if (ptb->count == pta->count)
        return pta->num - ptb->num;
}
int cmp2(const void *pa, const void *pb){
    number *pta = (number *)pa;
    number *ptb = (number *)pb;
    if (ptb->count == pta->count)
        return pta->num - ptb->num;
    else
        return 0;
}
int main()
{
    int len;
    cin >> len;
    for (int i = 0; i < len;i++){
        number data[501];
        int k;
        cin >> k;
        for (int r = 0; r < k;r++){
            int temp;
            cin >> temp;
            data[temp].num = temp;
            data[temp].count++;
        }
        qsort(data, 501, sizeof(data[0]), cmp);
        printf("case #%d:\n", i);
        for (int j = 0; j < 501;j++){
            if(data[j].count!=0){
                while(data[j].count--)
                    cout << data[j].num << " ";
            }
        }
        cout << endl;
    }
    return 0;
}