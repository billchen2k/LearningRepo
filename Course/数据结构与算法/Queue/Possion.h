//用于生成泊松分布的函数
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <cmath>
double U_Random()
{
    double f;
    f = (float)(rand() % 100);
    return f / 100;
}
int possion(double Lambda)
{
    int k = 0;
    long double p = 1.0;
    long double l = exp(-Lambda);
    srand((unsigned)time(NULL));
    while (p >= l)
    {
        double u = U_Random();
        p *= u;
        k++;
    }
    return k - 1;
}
