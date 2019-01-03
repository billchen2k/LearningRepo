#include <stdio.h>
#include <stdlib.h>
int main()
{
    int fl = 1;
    int num;
    while(printf("Please enter a number: ") && scanf("%d", &num) && num != -1)
          {
            printf("您输入的数为：%d阶乘为：%ld\n", num, calculate(num));
          }
  return 0;
}
int calculate(int n)
{
    /*
    int fl = 1;
    if(n == 0){
        fl = 1;
    }
    else if(n>0){
        while(n >0){
        fl = fl * n;
        n--;
        }
    }
return fl;
*/
if (n == 0) return 1;
else return n * calculate(n-1);
}
对于大数据：
#include <stdio.h>
#include <stdlib.h>
double calculate(unsigned int n)
{1
    if (n == 0) return 1;
    else return n * calculate(n-1);
}
int main()
{
    int fl = 1;
    int num;
    while(printf("Please enter a number: ") && scanf("%d", &num) && num != -1)
          {
            printf("您输入的数为：%d阶乘为：%lf\n", num, calculate(num));
          }
  return 0;
}

