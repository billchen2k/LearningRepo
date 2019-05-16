# 第九讲 存储器层次结构 课后作业

> 陈俊潼 10185101210

## 6.22

每条磁道的位数：x * r * K，其中 K 为常数

总的磁道数：(1 - x) * r * N，其中 N 为常数。

容量 = x(1-x)r^2 * K * N

易得当 x = 1/2 时该二次函数取最大值，有最大容量。

## 6.23

T<sub>avg seek</sub> = 4 ms

T<sub>avg rotation</sub> = 1/2 * 1 / 15000 * 60 * 1000 = 2 ms

T<sub> avg transfer</sub> = 1 / 15000 * 60 * 1000 / 800 = 0.005 ms

∴ T<sub>total</sub> 
= T<sub>avg seek</sub> + T<sub>avg rotation</sub> + T<sub> avg transfer</sub>
= 6.005 ms

## 6.24

2 MB / 512b = 4000, 所以一共需要读取4000个逻辑快。

#### A.最好情况

逻辑快连续： 

T<sub>avg seek</sub> + T<sub>avg rotation</sub>
= 5 ms +  1 / 2 * (1 / 15000 * 60 * 1000) ms = 4 ms + 2 ms = 6 ms

由于平均扇区数为 1000，所以需要旋转 4 圈进行读取。

∴ T<sub>total</sub> = T<sub>avg seek</sub> + T<sub>avg rotation</sub> + 4 * 1 / 15000 * 60 * 1000 ms = 22 ms.

#### B. 随机情况

如果是随机的，则每一次都需要定位到一个逻辑快。

∴ T<sub>total</sub> = 4000 * (T<sub>avg seek</sub> + T<sub>avg rotation</sub>) = 24000 ms = 24 s.