# Machine Learning Final Review

<center>January 2021</center>

## Preface

机器学习：输入 -> 数据集

机器学习的三要素：模型，策略，算法。

- 模型：决策函数或者条件概率分布
- 策略：从假设空间中选取最优模型
- 算法：学习模型的具体算法, 选取最优模型

主要类型：监督学习，非监督学习，半监督学习，强化学习

按输出空间分类：二分类、多分类、回归

奥卡姆剃刀：多个假设与观察一致，选择最简单的那个

### 分类

关于监督问题：预测问题和分类问题都是监督问题，推荐系统、音乐学习等没有直接标志的问题为非监督学习，学习的过程是强化学习。**根据训练数据是否具有标记数据来分类**。

- 监督式学习（Supervised learning），是一个机器学习中的方法，可以由训练资料中学到或建立一个模式（ learning model），并依此模式推测新的实例。训练资料是由输入物件（通常是向量）和预期输出所组成。函数的输出可以是一个连续的值（称为回归分析），或是预测一个分类标签（称作分类）。
- 无监督式学习(Unsupervised Learning )是人工智能网络的一种算法(algorithm)，其目的是去对原始资料进行分类，以便了解资料内部结构。有别于监督式学习网络，无监督式学习网络在学习时并不知道其分类结果是否正确，亦即没有受到监督式增强(告诉它何种学习是正确的)。
- 半监督学习的基本思想是利用数据分布上的模型假设, 建立学习器对未标签样本进行标签。

Eg.

![image-20210110153735905](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-cgTmpS.png)

### 交叉验证

> https://zhuanlan.zhihu.com/p/35394638

K 折交叉验证：选择 K 次评测中平均测试误差最小的模型

![image-20210110121225776](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-gGFECG.png)

### 范数

范数：欧式空间向量长度的推广

![image-20210110114137023](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-R7e6UY.png)



Ps. 零范数：指的是向量中非 0 元素的个数

![image-20210110114227069](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-mBQdnL.png)

### 评估指标

通常使用均方误差 MSE 来决定
$$
MSE = \frac{1}{N}\sum_i(\hat{y_i} - y_i)^2
$$


混淆矩阵：TP FP FN TN

![image-20210110150254640](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-kkPwkA.png)

几个指标：

- Accuracy 准确率：**(TP+TN)/(TP+TN+FP+FN)**
  - 判断总体的正确率，无法处理样本不平衡的问题
- Precision 查准率 ：TP / (TP + FP)
  - 所有被预测为正的样本中实际为正的样本的概率

- Recall 查全率 召回率：TP / (TP + FN)
  - 实际为正的样本中被预测为正样本的概率

ROC 曲线：Receiver Operation Characteristic（AUC 值）

![image-20210110124839554](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-LPKz7a.png)

### 凸函数*

> KKT，带约束的最优化问题的理解：https://blog.csdn.net/NewThinker_wei/article/details/52857397

凸函数的定义一：
$$
\forall x, y \in \operatorname{dom} f, \forall 0 \leq \theta \leq 1, \text { 有 } f(\theta x+(1-\theta) y) \leq \theta f(x)+(1-\theta) f(y)
$$
定义二：
$$
\forall x \in \operatorname{dom} f, \forall v \in \mathbf{R}^{n}, g(t)=f(x+t v) \text { 在 } \\ \operatorname{dom} g=\{t \mid x+t v \in \operatorname{dom} f\} \text{ 上是凸的 }
$$
KKT 定理（KKT 条件）—— 最优解的必要条件

![image-20210110155514958](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-fsazOQ.png)

Lagrangian Function

## 线性模型

### 线性回归

> 线性回归、逻辑回归和感知机的区别：
>https://blog.csdn.net/weixin_38300566/article/details/80753905
> 
>https://cloud.tencent.com/developer/article/1526936

#### 基本假设

1. 线性可分，可加性
2. 误差项之间相互独立
3. 自变量 $x_1, x_2$ 之间相互独立
4. 误差项为常数
5. **误差项为同方差的正态分布**

#### 最小二乘法

采用均方差作为损失函数：
$$
\mathrm{J}(\mathrm{w})=\frac{1}{2} \sum_{i=1}^{m}\left(f\left(x_{i}\right)-y_{i}\right)^{2}
$$


最小二乘法解析：
$$
\omega = (X^TX)^{-1}X^TY \\
\hat{Y} = X\omega
$$

#### 梯度下降法

1. BGD 批量梯度下降
   1. 不断重复更新参数使得误差函数减小，知道满足要求，学习率 $\eta$，阈值 $\varepsilon$。
2. 随机梯度下降
   1. 利用单个样本的损失函数对 $\theta$ 求偏导
3. 小批量梯度下降
   1. 利用部分样本的损失函数对 $\theta$ 求偏导得到对应的梯度

![image-20210110182453011](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-dEr1IR.png)



#### 正则化

L1 正则化有助于生成一个稀疏权值矩阵。
$$
\begin{array}{l}
l_{1}: \Omega(w)=\|w\|_{1}=\sum_{i} \mid w_{i} \mid \\
l_{2}: \Omega(w)=\|w\|_{2}^{2}=\sum_{i} w_{i}^{2}
\end{array}
$$
其他概念：

1. 损失函数：单个样本预测值和真实值之间误差的程度。
2. 期望风险：是损失函数的期望，理论上模型f(X)关于联合分布P(X,Y)的平均意义下的损失。
3. 经验风险：模型关于训练集的平均损失（每个样本的损失加起来，然后平均一下）。
4. 结构风险：在经验风险上加上一个正则化项，防止过拟合的策略。

### 感知机 Perceptron

错误驱动，硬分类，$y\in \{0, 1\}$

损失函数：
$$
L(\hat{w})=\max \left(0,-y_{i} \hat{y}_{i}\right)=-\sum_{i \in M} y_{i} \hat{w}^{T} x_{i}
$$
权值更新的步骤，其中 M 为错误分类的点。
$$
w_{t+1}=w_{t}+\eta \sum_{i \in M} y_{i} \mathbf{x}_{i}
$$


随机选着直线分类，直到找到一个分类错误的点，修正错误。例子：

![image-20210110185635265](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-8vADnn.png)

#### 收敛性

例题：

![image-20210110194016866](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-8Z7mzL.png)

![image-20210110195806448](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-FvxSuI.png)

解答：

![image-20210110194026239](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-eqlSPC.png)

### 逻辑回归 Logistic Regression

> 用人话讲明白逻辑回归：https://zhuanlan.zhihu.com/p/139122386

**本质是将线性回归的输出作为sigmoid函数的输入，最终的输出便是分类的结果。**
$$
\mathrm{h}_{\theta}(x)=g\left(\theta^{T} x\right)=\frac{1}{1+e^{-\theta^{T_{x}}}}
$$


逻辑回归：软分类。激活函数：sigmoid:
$$
\theta(s) = \frac{1}{1+e^{-s}}
$$

损失函数：利用对数似然损失函数。
$$
J(\beta)=-\log \mathcal{L}(\beta)=-\sum_{i=1}^{n}\left[y_{i} \log P\left(y_{i}\right)+\left(1-y_{i}\right) \log \left(1-P\left(y_{i}\right)\right)\right]
$$
拓展：输出为 -1，+1 的对数似然函数：
$$
-\sum_{i=1}^{N} \log \left(1+\exp \left(-y_{i}\left(w^{T} \mathbf{x}_{i}+b\right)\right)\right)
$$

### 多分类问题

单分类到多分类的几个方法：

- 一对一
  - 构造多个二分类问题
- 一对多
  - 将每一次的一个类作为正例，其余作为反例来计算多次获得分类结果

## 支持向量机 Support Vector Machine

间隔、对偶、核技巧

## 集成学习

## 决策树

## 聚类和降维

## 概率图模型

