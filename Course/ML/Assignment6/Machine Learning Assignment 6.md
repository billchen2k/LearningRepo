# Machine Learning Assignment 6

> 10185101210 陈俊潼

## 4.10

![image-20201124003452179](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-24-KgqUEW.png)

a. 如果不含偏置项，优化问题为：
$$
\min_{w,b}\gamma = \frac{2}{||\omega||} \\

s.t. y_i(w^t x_i) \ge 1
$$
b. 拉格朗日函数为：
$$
L(\omega, b, \lambda) = \frac{1}{2} || \omega || ^2 + \sum _{i=1} ^{m}\lambda_i (1-y_i(\omega^T x_i))
$$


令偏导数为 0，得到对偶问题：
$$
\max_{\mathbf{\alpha}}\sum_{i = 1} ^m \alpha_i - \frac{1}{2} \sum^m _{i = 1} \sum^{m} _{j = 1} \lambda_i\lambda_jy_iy_jx_i^Tx_j \\

s.t. \sum_{i = 1} ^m \lambda_iy_i = 0\\
\lambda_i \ge 0, i = 1,2,3,...m
$$
最优决策边界中：
$$
\omega^* = \sum_{i=1}^{m}\lambda_iy_ix_i^Tx
$$

## 4.11

![image-20201124005208450](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-24-X1pdF3.png)

**D**

## 4.12

![image-20201124005214171](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-24-aOBr7t.png)

**B**

![image-20201124112420599](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-24-HcLFaO.png)