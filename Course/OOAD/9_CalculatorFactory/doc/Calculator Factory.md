# Calculator Factory

> 10185101210 陈俊潼

## Simple Calculator Factory

运行截图：

![image-20201218152004396](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-12-18-wfh8Vy.png)

类图：



![SimpleFactory!Main_0](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-12-18-Un2J02.png)

## Calculator Factory

运行截图：

![image-20201218152401761](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-12-18-L0pFmp.png)

类图

![Factory!Main_1](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-12-18-F5RToE.png)

## 对比

工厂模式相对简单和工厂模式而言，遵循了开闭原则，又保持了封装对象创建过程的优点。因为在简单工厂模式中，如果增加了新的运算符号，需要“打开”工厂类来进行修改，改变 `switch` 语句的行为，所以对修改就不封闭了。而在工厂模式中，可以通过新增一个新的工厂类来继承基工厂，从而避免了修改之前已有的代码，对修改封闭。而此时又能够在原有的系统上进行拓展，所以遵循了对拓展的开放性。

程序代码见附件。