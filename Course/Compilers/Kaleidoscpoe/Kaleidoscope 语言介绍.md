# Kaleidoscope 语言介绍

Kaleidoscope 是一种面向过程的语言，主要包括 def 和 extern 两个关键字，而且只含有浮点数一种数据类型。该语言同时并且支持定义函数、使用条件语句和数学表达式。其计算斐波那契数列的代码如下：

```
# Compute the x'th fibonacci number.
def fib(x)
  if x < 3 then
    1
  else
    fib(x-1)+fib(x-2)
# This expression will compute the 40th number.
fib(40)
```


Kaleidoscope 语言主要包含以下元素：

- **keywords** 只含 `def` 和 `extern`
- **identifier** 支持大小写的标示符，其正则表达式为 `[a-zA-Z][a-zA-Z0-9]*`
- **float number** 浮点数，其正则表达式为 `[0-9].[0-9]`
- **comments** 以 # 开头的一整行为注释
- **others** 除了
- **eof**