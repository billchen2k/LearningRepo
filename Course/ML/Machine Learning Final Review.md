# Machine Learning Final Review

<center>January 2021</center>

[toc]

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

假设空间相关的例题：

![image-20210112004947553](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-Hgixvb.png)

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

### 凸函数，KKT*

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

激活函数的结果作为 $P(y = 1)$
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
Eg. 求解分类为 $\pm1$ 时的对数似然函数：

![image-20210111115837913](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-RCjPjE.png)

### 多分类问题

单分类到多分类的几个方法：

- 一对一
  - 构造多个二分类问题
- 一对多
  - 将每一次的一个类作为正例，其余作为反例来计算多次获得分类结果

## 支持向量机 Support Vector Machine

定义间隔
$$
\operatorname{margin}(\mathbf{w}, b)=\min _{i} \frac{\left|\mathbf{w}^{T} \mathbf{x}_{i}+b\right|}{\|w\|}
$$

### 线性 SVM

![image-20210111104222940](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-N3mhqL.png)

**// bias 偏大时，应当考虑增加模型复杂度**

####  对偶与 KKT

关于 KKT，凸优化

![image-20210111115352399](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-PxoGui.png)

即得到凸优化问题
$$
\begin{array}{ll}
\min _{\mathbf{w}, b} & \frac{1}{2} \mathbf{w}^{T} \mathbf{w} \\
\text { s.t. } & y_{i}\left(\mathbf{w}^{T} \mathbf{x}_{i}+b\right) \geq 1 \quad(i=1,2, \ldots, N)
\end{array}
$$
原问题和对偶问题

![image-20210111121837925](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-GcXalx.png)

一个例题：

![image-20210111134536847](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-XrDGai.png)

### 核技巧

核函数：解决线性不可分的问题，将原始空间映射到更高维的特征空间

得到问题：
$$
\begin{array}{ll}
\min _{\mathbf{w}, b} & \frac{1}{2} \mathbf{w}^{T} \mathbf{w} \\
\text { s.t. } & y_{i}\left(\mathbf{w}^{T}\phi(\mathbf{x}_{i})+b\right) \geq 1 \quad(i=1,2, \ldots, N)
\end{array}
$$

核技巧旨在将特征映射和内积这两步运算压缩为一步。

常用的核：

![img](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-Op1ai8.jpg)

核方法是一类把低维空间的非线性可分问题，转化为高维空间的线性可分问题的方法。核函数输入两个向量，它返回的值跟两个向量分别作 ![[公式]](https://www.zhihu.com/equation?tex=%5Cphi) 映射然后点积的结果相同。核技巧是一种利用核函数直接计算 ![[公式]](https://www.zhihu.com/equation?tex=%5Clangle+%5Cphi%28x%29%2C%5Cphi%28z%29+%5Crangle) ，以避开分别计算 ![[公式]](https://www.zhihu.com/equation?tex=%5Cphi%28x%29) 和 ![[公式]](https://www.zhihu.com/equation?tex=%5Cphi%28z%29) ，从而加速核方法计算的技巧。核方法不仅仅适用于SVM，还适用于其他数据为非线性可分的问题和算法。SVM的表现形式包含了映射的点积，所以可以用核技巧加速核方法的计算。

### 软间隔

相对硬间隔，允许误分类，允许少量样本分类错误。

![image-20210111145710212](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-ENGOJK.png)

![image-20210111145154470](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-0UKNb6.png)

## 集成学习与决策树

### 集成学习 Ensemble

- 强可学习：在概率近似正确（ Probably approximately correct, PAC ）学习的框架汇总， 一个概念， 如果存在一个多项式的学习算法能够学习它， 并且正确率很高， 那么就称这个概念是强可学习的
- 弱可学习：一个概念， 如果存在一个多项式的学习算法能够学习 它， 学习的正确率**仅比随机猜测略好**， 那么这个概念是弱可学习的

集成学习通常针对弱学习器。

#### 偏差方差分解

- 偏差 `Bias` 期望预测与真实标记的误差称为偏差(bias)，为了方便起见，我们直接取偏差的平方。
- 方差 `Variance`

分解：将泛化误差分解为三个部分，方差、偏差和噪声

![bias-variance](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-YEbp96.png)

- 偏差：度量了模型的期望预测和真实结果的偏离程度，刻画了**模型本身的拟合能力**。

- 方差：度量了同样大小的训练集的变动所导致的学习性能的变化，即**刻画了数据扰动所造成的影响**。

- 噪声：表达了当前任务上任何模型所能达到的期望泛化误差的下界，**刻画了学习问题本身的难度**。

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-A3PqvV.png" alt="image-20210111151041701" style="zoom:50%;" />



#### Boosting

Boosting 算法的工作机制是首先从训练集用初始权重训练出一个弱学习器1，根据弱学习的学习误差率表现来更新训练样本的权重，使得之前弱学习器1学习误差率高的训练样本点的权重变高，使得这些误差率高的点在后面的弱学习器2中得到更多的重视。然后基于调整权重后的训练集来训练弱学习器2.，如此重复进行，直到弱学习器数达到事先指定的数目T，最终将这T个弱学习器通过集合策略进行整合，得到最终的强学习器。

**AdaBoosting**: 具体的一种著名的 Boosting 算法，**Ada**ptive Boosting.

- 对异常样本敏感，异常样本在迭代中可能会获得较高的权重，影响最终的强学习器的预测准确性。
- 核心参数 $\alpha$ 的取值为 $\frac{1}{2} \ln \left(\frac{1-e}{e}\right)$

**GradientBoosting**: AdaBoosting 使用的是指数损失函数，GradientBoosting 使用梯度下降来更新权重

#### Bagging (Bootstrap Aggregatting)

Bootstrapping: 一种有放回的抽样方法：

1. 采用重抽样技术从原始样本中抽取一定数量（自己给定）的样本，此过程允许重复抽样。
2. 根据抽出的样本计算统计量T。
3. 重复上述N次（一般大于1000），得到统计量T。
4. 计算上述N个统计量T的样本方差，得到统计量的方差。

- 将弱学习器提升为强学习器的算法，先从初始训练集中训练出一个基学习器，再根据基学习器的表现对训练样本分布进行调整
- 学习错的训练样本将在后续收到更多的关注，重复进行直到基学习器达到事先的设定值，然后进行加权结合

Bagging： 采用相对多数投票

**Random Forest**

随机森林使用 Bagging 的方式把众多的 Decision Tree 进行 uniform 结合起来。

**Bagging 和 Boosting 的区别：**

1. 样本选择上：
   1. Bagging：训练集是在原始集中有放回选取的，从原始集中选出的各轮训练集之间是独立的。
   2. Boosting：每一轮的训练集不变，只是训练集中每个样例在分类器中的权重发生变化。而权值是根据上一轮的分类结果进行调整。
2. 样例权重：
   1. Bagging：使用均匀取样，每个样例的权重相等
   2. Boosting：根据错误率不断调整样例的权值，错误率越大则权重越大。
3. 预测函数：
   1. Bagging：所有预测函数的权重相等。
   2. Boosting：每个弱分类器都有相应的权重，对于分类误差小的分类器会有更大的权重。
4. 并行计算：
   1. Bagging：各个预测函数可以并行生成
   2. Boosting：各个预测函数只能顺序生成，因为后一个模型参数需要前一轮模型的结果。

在大多数数据集中，boosting的准确性要比bagging高。有一些数据集总，boosting会退化-overfit。**boosting思想的一种改进型adaboost方法在邮件过滤，文本分类中有很好的性能。**

// bagging 是减少 variance，而 boosting 是减少 bias。

### 决策树



#### 信息熵

表示随机系统的总体信息量，用概率表示。

第 k 类样本所占的比例为 $p_k$，则信息熵为：
$$
\operatorname{ENT}(D) = - \sum_{k=1}^{\mathcal{Y}}p_klog_2p_k
$$


信息熵的值越小，节点的纯度就越高。

交叉熵 Cross Entropy：关于随机变量 X 的两个概率分布，表示分布 p(x) 的困难程度：

划分选择：信息增益，增益率，基尼系数

#### 信息增益

$$
\operatorname{GAIN}(D,a) = \operatorname{Ent}(D) - \sum_{v=1}^{V}\frac{|D^v|}{|D|}\operatorname{Ent}(D^v)
$$





父节点和子节点的信息熵关系：无法确定。

例题：计算信息增益：

![image-20210111182758066](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-yY5zMu.png)

Sol.

![image-20210111182812150](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-ikOW0r.png)

## 聚类和降维

*无监督学习*

### 聚类

聚类：对大量未知标注的数据集，按数据的内在相似性将数据集划分为多个类别，使类别内的数据相似度较大而类别间的数据相似度

#### K-Means

![image-20210111183007057](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-GhpLU4.png)![image-20210111182958336](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-ecwYNo.png)

#### K 临近法 KNN

K-Nearest Neighbors

**新的样本出现后**找到数据集中与实例最近邻的 k 个实例，对新邻居采用投票法 / 平均法来预测新的类别。

懒惰算法的代表：Lazy learning：与急切学习（eager learning）相对应的，因为KNN没有显式的学习过程！也就是说没有训练阶段，从上面的例子就可以看出，数据集事先已有了分类和特征值，待收到新样本后直接进行处理。

计算复杂度高：新样本需要与数据集中每个数据进行距离计算，计算复杂度和数据集中的数据数目n成正比，也就是说，KNN的时间复杂度为O(n)，因此KNN一般适用于样本数较少的数据集。

### 降维

维数灾难：在高维情形下出现的数据样本稀疏、距离计算困难的问题

#### PCA 主成分分解

> PCA 的目的、作用即分析：https://blog.csdn.net/NeverLate_gogogo/article/details/88683904

在PCA中，数据从原来的坐标系转换到新的坐标系，新坐标系的选择是由数据本身决定的。

第一个坐标轴的选择是原始数据中方差最大的方向，从数据角度上来讲，这其实就是最重要的方向，即下图总直线B的方向。第二个坐标轴则是第一个的垂直或者说**正交（orthogonal）**方向，即下图中直线C的方向。该过程一直重复，重复的次数为原始数据中特征的数目。而这些方向所表示出的数据特征就被称为“主成分”。

![img](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-OGUtSf.jpg)

使用 **协方差矩阵** 及 **特征值分析**，得到对应的维数。

例题：主成分分析：$x=\{[2,3,3,4,5,7],[2,4,5,5,6,8]\}, d=2$



![image-20210111184036387](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-8XAADM.png)

应用：特征人脸 eigenface...

## 概率图模型

有向图：朴素贝叶斯、贝叶斯网络、隐马尔可夫模型（贝叶斯模型）

**无向图：马尔科夫随机场、条件随机场**

> https://www.jiqizhixin.com/articles/2017-11-29-3

### 贝叶斯网络

联合概率分布：

![image-20210111192403361](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-URi5zW.png)

三种结构：发散、汇总、顺序结构

#### D-Seperation D 划分

> https://zhuanlan.zhihu.com/p/274314301

![image-20210111202110917](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-SJKxim.png)

![image-20210111202140945](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-0QLG5Y.png)

![image-20210111202201795](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-UsP0Fs.png)

具体的例题：

![image-20210111195449086](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-GWClad.png)

阻隔了所有路径 = A 与 B 条件独立。

// 受限玻耳兹曼机是该旅途模型。

**随机场**：相对于贝叶斯模型，为无向图网络，又称马尔科夫随机场。无向边表示变量间的依赖关系。

### EM 算法

EM 算法的流程：

![image-20210111215134545](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-0N8TJU.png)

**Points**: EM 算法是一种迭代算法，用于计算后验分布，可以计算极大似然估计。

算法简单且稳定，迭代速度收到数据规模的影响，能找到极值点但不一定是最优解。**算法的收敛速度依赖于初始值**。

kmeans 也是一种 EM 算法。

### 隐马尔科夫模型 HMM

可用于标注问题， 在语音识别、 NLP 、生物信 息、模式识别等领域被证明是有效的算法。

在任意时刻t，给定$z_t$， 观测变量$x_t$的取值与其他隐变量无关。 同时，对于任意时刻的隐变量$z_t$ ， 如果给定其前一时刻的隐变量$z_{t-1}$， 则与更早时刻的隐变量没有关系。 对应的联合概率分布为：

HMM 的三大问题：

- **评估问题 / 概率计算问题**
- **预测问题 / 解码问题**
- 学习问题

用维特比算法进行编码的复杂度：$O(NK^2)$

- Baum-Welch算法：使用前向后向算法计算用于寻找隐马尔可夫模型(HMM)未知参数的一种 EM 算法。