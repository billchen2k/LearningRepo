# 第十一讲 链接 课后作业

> 陈俊潼 10185101210

 ## 7.6

 | 符号  | swap.o.symtab条目 | 符号类型 | 定义符号的模块 | 节    |
 | ----- | ----------------- | -------- | -------------- | ----- |
 | buf   | Yes               | 外部     | m.o            | .data |
 | bufp0 | Yes               | 全局     | swap.o         | .data |
 | bufp1 | Yes               | 局部     | swap.o         | .bss  |
 | swap  | Yes               | 全局     | swap.o         | .text |
 | temp  | No                | -        | -              | -     |
 | incr  | Yes               | 局部     | swap.o         | .text |
 | count | Yes               | 局部     | swap.o         | .bss  |

 ## 7.10

 **A.** `gcc p.o libx.a p.o`

 **B.** `gcc p.o liby.a libx.a`

 **C.** `gcc p.o libx.a liby.a libx.a libz.a`

## 7.12

**A.** 由题可知 ADDR(s) = ADDR(.text) = 0x4004e0, ADDR(r.symbol) = ADDR(swap) = 0x4004f8. 先计算出引用的运行时地址：

`refaddr = ADDR(s) + r.offset = 0x4004ea`

再修改此引用：

`*refptr = (unsigned)(ADDR(r.symbol) + r.addend - refaddr) = 0x4004f8 - 0x4 - 0x4004ea = 0xa`

所以在可执行目标文件中对 swap 的 PC 相对引用的值为 0x10:

`400e9:  e8 0a 00 00 00  callq  4004f8 <swap>`

**B.** 由题可知 ADDR(s) = ADDR(.text) = 0x4004d0, ADDR(r.symbol) = ADDR(swap) = 0x400500. 先计算出引用的运行时地址：

`refaddr = ADDR(s) + r.offset = 0x4004da`

再修改此引用：

`*refptr = (unsigned)(ADDR(r.symbol) + r.addend - refaddr) = 0x400500 - 0x4 - 0x4004da = 0x22`

所以在可执行目标文件中对 swap 的 PC 相对引用的值为 0x10:

`400d9:  e8 22 00 00 00  callq  4004f8 <swap>`