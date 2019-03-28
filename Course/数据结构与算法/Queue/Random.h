#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <iostream>
#include <time.h>
#include <limits.h>
#include <math.h>

using namespace std;

class Random
{

  public:
    Random(bool pseudo = true);
    double random_real();
    int random_integer(int low, int high);
    int poisson(double mean);

  private:
    int reseed();                 //  Re-randomize the seed.
    int seed, multiplier, add_on; //  constants for use in arithmetic operations
};
#include "Random.h"

Random::Random(bool pseudo)
/*Post: The values of seed, add_on, and multiplier are
        initialized.  The seed is initialized randomly only if pseudo == false.
*/
{
    if (pseudo)
        seed = 1;
    else
        seed = time(NULL) % INT_MAX;
    multiplier = 2743; // 斜率
    add_on = 5923;     // 位移
}

int Random::reseed()
//Post: The seed is replaced by a pseudorandom successor.
{
    seed = seed * multiplier + add_on;
    return seed;
}

double Random::random_real()
/*Post: A random real number between 0 and 1 is returned.*/
{
    double max = INT_MAX + 1.0; //INT_MAX = (2)31 -1
    double temp = reseed();
    if (temp < 0)
        temp = temp + max;
    return temp / max;
}

int Random::random_integer(int low, int high) // 这个函数在泊松分布中没有用到
{
    double max = INT_MAX + 1.0; //INT_MAX = (2)31 -1
    double temp = reseed();
    if (temp < 0)
        temp = temp + max;
    return (int)(temp / (max / (high - low + 1.0) + low)); // 返回整数，且有规定范围
}

int Random::poisson(double mean) // 泊松分布的实现
{
    double x = -1;
    double u;
    double log1, log2;
    log1 = 0;
    log2 = -mean;
    do
    {
        u = random_real();
        log1 += log(u);
        x++;
    } while (log1 >= log2);
    return x;
}
#endif // RANDOM_H_INCLUDED