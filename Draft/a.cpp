#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
int main()
{
    unsigned long long int input;
    cin >> input;
    unsigned long long int output = sqrt(input);
    if(pow(output,2)<input)
        output++;
    cout << output;
    return 0;
}