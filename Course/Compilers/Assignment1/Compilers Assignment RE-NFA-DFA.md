# Compilers Assignment: RE-NFA-DFA

> 10185101210 陈俊潼

## 一、使用Thompson构造法为下列正规式构造NFA，写出每个NFA处理符号串“ababbab”过程中的状态转换序列。

a) (a | b)\*

![image-20201008195409797](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-08-rlJ9GG.png)

0-1-2-3-6-1-4-5-6-1-2-3-6-1-4-5-6-1-4-5-6-1-2-3-6-1-4-5-6-7​

b) (a\* | b\*)\*

![image-20201008200716498](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-08-egp0d8.png)

0-1-2-3-4-5-10-1-6-7-8-9-10-1-2-3-4-5-10-1-6-7-8-9-10-1-6-7-8-9-10-1-2-3-4-5-10-1-6-7-8-9-10-11​

c) ((e | a)b\*)\*

![image-20201008200746759](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-08-UkB2VN.png)

  0-1-2-5-6-7-8-9-10-1-2-5-6-7-8-9-8-9-10-1-2-5-6-7-8-9-10-11

d) (a | b)\*abb(a | b)\*

![image-20201008200755674](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-08-QPYsRR.png)

1-2-3-4-7-2-5-6-7-8-9-10-11-12-13-14-15-18-13-16-17-18-19

## 二、利用子集构造法将第一题得到的 NFA 转换为 DFA，同样写出分析符号串 ababbab 过程中的状态转换。

![image-20201008201138450](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-08-QR4c7k.png)

A-C-B-C-C-B-C

![image-20201008201210026](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-08-lZfS4i.png)

A-C-B-C-C-B-C

![image-20201008202611714](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-08-GtvWvX.png)

A-B-D-B-D-D-B-D

![image-20201008202625261](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-08-vYWQLp.png)

A-B-B-D-E-G-F-G