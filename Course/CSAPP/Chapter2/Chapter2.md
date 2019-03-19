# 计算机系统第二章作业
> 陈俊潼 10185101210

### E2.62
```c
int int_shifts_are_arithmetic(){
    int source = -1;
    int des = source >> 1;
    if (des == -1)
        return 1;
    else
        return 0;
}
```
### E2.67
```c
int int_size_is_32(){
    int msb = 1;
    unsigned char *pointer1 = &msb;
    if (*pointer1 == 0x01){
        int moved_msb = msb >> 24;
        return msb && !(moved_msb);
    }
    else{
        int
        moved_msb = msb <<31;
        return msb && !(moved_msb);
    }
}
```
### E2.75
```c
unsigned unsigned_high_prod(unsigned x, unsigned y){
    int w = sizeof(int) << 3;
    return int_high_prod(x, y) + x * y>>(w-1) = y * x>>(w-1);
}
```
### E2.82
- A.不是。当x是最小的有符号整数的时候该式不成立。
- B.是。<<4相当于乘$2^4$倍。
- C.是。~x+1=-, ~y+1=-y, (x+y)=-(x+y)+1。
- D.是。(ux-uy)=(unsigned)(x-y), =>(ux-uy)=-(unsigned)(y-x)
- E.是。>>2可能会让x最右侧的两位变为0，所以可能小于原数。当x最右侧两位本来就是0的时候=x。

### E2.87
如表所示。
| Hex    | M         | E   | V               | D             |
| ------ | --------- | --- | --------------- | ------------- |
| 0x8000 | 0         | -14 | -0              | -0.0          |
| 0x4001 | 1025/1024 | 1   | 1025/512        | 2.00195312    |
| 0x6000 | 1         | 9   | 512             | 512.0         |
| 0x03FF | 1023/1024 | -14 | 2^-14*1023/1024 | 6.09755516e-5 |
| 0xFC00 | -         | -   | -∞              | -∞            |
| 0x3BB0 | 123/64    | -1  | 123/128         | 0.96          |

### E2.89
- A.是。dx都是从x转换过来的。
- B.不一定。当y是最小的有符号整数的时候
- C.是。浮点运算加法可以结合。
- D.不一定。乘法只保留后w位，可能会溢出。
- E.不一定。如果dx或dz等于0会出现错误。

### E2.90

依次填入空格的代码如下：
```
2-pow(2,7)-23
0
0
2-pow(2,7)
0
1<<unsigned(x-2-pow(2,7)-23)
pow(2,7)
pow(2,7)-1+x
0
0xFF
0
```
