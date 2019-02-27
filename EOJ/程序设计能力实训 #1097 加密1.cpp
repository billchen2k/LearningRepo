//2019.2.24
//Notes: 无符号32位整数获取高16位：i & 0xffff0000
//1111 1111 1111 1111 0000 0000 0000 0000
#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
    unsigned int input;
    while (cin >> input && !cin.eof())
    {
        unsigned int H16, L16, output;
        H16 = (input & 0xffff0000) >> 16;
        L16 = (input << 16) & 0xffff0000;
        H16 = ~H16 & 0x0000ffff;
        L16 = ((H16 << 16) ^ L16) & 0xffff0000;
        output = H16 | L16;
        printf("%X\n", output);
    }
}