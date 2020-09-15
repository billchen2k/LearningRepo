# Digital Image Final Review

## Preface

### 基本概念

#### 采样与量化

- 采样：空间坐标轴的数字化
- 量化：图像像素灰度值的数字化

#### 图像表示

图像的表示方法：二维离散亮度函数 $f(x,y)$；二维矩阵 $A[m,n]$

图像文件包含：图像描述信息、图像顺序

彩色模型主要有：

- RGB
- HIS Hue Saturation Intensity
- CYM 系统 Cyan Yellow Magenta
- CYMK CYM + Black

#### 像素间关系

4 邻域、8 邻域、4 连通、8 连通

### 图像增强

采用一系列技术改善图像的视觉效果，或将图像转换成一种更适合于人或机器进行分析处理的形式。 图像增强并不以图像保真为准则，而是有选择地突出某些对人或机器分析有意义的信息，抑制无用信息，提高图像的使用价值。	

#### 直方图均衡化 Equalize Histogram

核心计算：
$$
s=T(r) = (L-1)\int_0^rp_r(w)dw
$$

其中 $p_r$ 为累计概率函数。

#### 伪彩色与假彩色

- 伪彩色(pseudocolor)处理：
    - 根据一定准则给灰度值赋予彩色值的处理
- 将黑白图像（灰度图像）转化为彩色图像
- 将单色图像变换成给定彩色分布的图像
- 假彩色(false color)处理：
    - 把真实的自然彩色图像、遥感多光谱图像、医学图像等处理成假彩色图像。

可以理解为伪彩色是还原本来存在的颜色（主要是灰白照片还原），假彩色则是染上本来就不存在的颜色，比如数据可视化、CT 图像等。


## 图像分割

图像分割是按照某些特性(如灰度级,频谱,纹理等)将图像划分成一些区域，在这些区域内其特性是相同的或者说是均匀的，两个相邻区域彼此特性则是不同的，其间存在着边缘或边界。

门限化（灰度级门限化）

### 边缘检测

几种用于边缘检测差分算子：

- Laplacian 拉普拉斯算子：![image-20200906001833657](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-I36SJH.png)

- Prewitt:

  ![image-20200906001252635](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-apn56m.png)

- Sobel:

  ![image-20200906001319652](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-WrvnTc.png)

更高级的方法：Snake 算法、Canny 算法：

- Snack: 活动控制模型 Active Control
- Canny：
  - 高斯滤波：平滑图像，减少噪声
  - 计算梯度值和方向
  - 非极大值抑制：将当前像素的梯度强度与沿正负梯度方向上的两个像素进行比较。如果当前像素的梯度强度与另外两个像素相比最大，则该像素点保留为边缘点，否则该像素点将被抑制。
  - 使用上下阈值的双阈值来检测边缘

### 边缘连接

- 局部处理方法
  - 判断两个点是否应该连接：对于点 $(x,y)$ ，判断其是否与邻域内的 $(x,y)$ 相似。（同时判断梯度向量的方向角）
  - 如果方向角和梯度值都是相似的，则可以将两点连接
- 霍夫变换方法 Hough
  - ![image-20200907210203880](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-YtD6tx.png)

### 序贯分割

- 并行法：对图像上每一点所作的处理不依赖于其他点上经过处理已经得到的结果。

- 序贯法：需用前面已经处理的结果，跟踪计算不需要在每一点上进行，只需在已检测的点到正在跟踪的延伸点上作计算。

  区域生长：从满足检测条件的点开始向各个方向生出区域

### 模板匹配

- 点模板
<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-22P67b.png" alt="image-20200906004227782" style="zoom:67%;" />

- 线模板

![image-20200906004324370](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-65J2ht.png)





关于更多概念（感觉只用了解）

1. The top-down approach uses object representation learned from examples to detect an object in a given input image and provide an approximation to its figure-ground segmentation.通过先验知识建立物体模型，以模型驱动图像分割，完成物体识别和分割同步协调的渐进处理流程。 
2. The bottom-up approach uses image-based criteria to define coherent groups of pixels that are likely to belong together to either the figure or the background part. 强调基于区域的特性，例如颜色的均匀性，灰度或纹理，边界轮廓的平滑度和连续性等。 基于图像的特性的方法（image-based，例如根据颜色的均匀性，灰度级或纹理均匀的图像区域，边界轮廓的平滑度和连续性等来分割图像）
3. 基于区域的方法（ region-based，根据一些具体的标准，例如阈值化、区域的生长及分裂合并等方法） 区域分治的方法（“Divide & Conquer”，将区域通递归分割成子区域） 基于轮廓的方法（Contour-based，根据区域的边界属性，如边缘的连续性、平滑度、长度、曲率以及形状）

## :star: 傅里叶变换 Fourier Transform

//todo

原理看不懂。

空间域 -> 傅里叶变换 -> 频率域

离散傅里叶变换 DFT ：
$$
F(u) = \sum_{x=0}^{M-1} f(x) e^{-j2\pi ux/ M} \\

f(x) = \frac{1}{M} \sum_{u=0} ^ {M-1} F(u) e ^ {j2\pi ux / M}
$$


一维离散傅里叶变换对：

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-08-AHVzUT.png" alt="image-20200908011506945" style="zoom:50%;" />

一个例子：

![image-20200908013118384](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-08-Of4j2N.png)

### 傅里叶变换的性质

- 加法定理：时域或空域内的相加对应于频域内的相加。
- 函数位移不改变傅立叶变换的幅值。
- 对*f*(*x*,*y*)的平移不影响其傅立叶变换的幅值。

$$
\mathfrak{I}(F(u))
$$



## 图像平滑

### 频率域方法

低通滤波（滤除高频成分，在频域中实现平滑处理），用于图像平滑
$$
G(u,v) = H(u,v)F(u,v)
$$

术语：$F$ 原始图像频谱； $G$ 平滑图像频谱；$H$ 转移函数。具有频率响应曲线

主要用于平滑的滤波器：

- 高斯低通滤波器
- 理想滤波器

- 巴特沃斯低通滤波器：

  - $$
  H(u,v) = \frac{1}{1+\Big[D(u,v) /D_0\Big]^{2n}}
  $$

### 空间域方法

平滑：中值滤波、自适应滤波、简单均值滤波

==中值滤波：用局部中值代替局部平均值== （消除噪声）

自适应中值滤波也工作在Sxy（窗口）内，只是会根据某些条件改变(增大)窗口的尺寸

## 图像锐化

### 频率域方法

主要用于锐化的滤波器：

- 高频加强滤波器
- 指数高通滤波器
- 提醒高通滤波器
- 巴特沃斯高通滤波器

### 微分法 - 即空间域处理

- 背景保留：即门限值、阈值，采用门限函数
- 使用算子进行卷积：Prewitt、Sobel 等

**反锐化掩膜法**：

![image-20200906010231299](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-XgAo9I.png)

即用原始图像加上原始图像减去被模糊的图像，后半部分为掩膜

其中 C 为常数。

## 形态学处理

击中与不命中：两幅图像 $A\cap B \ne \emptyset$ 则为击中 Hit，否则 Miss

结构元：就是一个形状和大小已知的像素点集，通常还要为结构元定义一个中心。

### 腐蚀与膨胀

腐蚀与膨胀：腐蚀使图像向内收缩，膨胀使图像向外扩张。

**腐蚀和膨胀是对白色部分（高亮部分）而言的，不是黑色部分。膨胀就是图像中的高亮部分进行膨胀，“领域扩张”，效果图拥有比原图更大的高亮区域。腐蚀就是原图中的高亮部分被腐蚀，“领域被蚕食”，效果图拥有比原图更小的高亮区域。**

膨胀：

![image-20200907191608194](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-ZPRjc3.png)



腐蚀：

![image-20200907191652072](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-nL1uJF.png)

### :star: 开操作与闭操作

**开操作：先腐蚀后膨胀：$A \circ B = (A\ominus B) \oplus B$  其中 B 为结构元**

**闭操作：先膨胀后腐蚀：$A \cdot B = (A\oplus B) \ominus B$**

开操作与闭操作直观的几何解释：

![image-20200906011725642](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-7yT4W9.png)

![image-20200906011737102](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-gaistS.png)

### 基本形态学的应用

边缘提取（Boundary extraction）

孔洞填充（Hole filling）

骨架提取（Skeletons）

提取连通成分（Extraction of connected components）

## 图像恢复

 ### 图像退化



成像系统、记录设备、传输介质和处理方法的不完善，从而导致的图像质量下降。

![image-20200906015730020](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-uOJthS.png)

可建立噪声的退化模型：考虑加性噪声 or not

退化模型的向量空间表示：

![image-20200907153229850](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-hPighK.png)

恢复方式：

- 图像观察恢复法：构造一个估计图像，其观察的子图像有相同大小和特性（使用子图像）
  - $g_s(x,y)$ 为观察子图像，$\hat{f}_s(x,y)$ 表示构造的估计子图像，傅里叶变换分别为 G, F, 则
  - $H_s(u,v) = \frac{G_s(u,v)}{\hat{F}_s(u,v)}$
- 实验估计法
- 模型估计法：建立退化模型，模型要把引起环境退化的因素考虑在内
  - 大气湍流退化模型：$H(u,v) = e^{-k(u^2+v^2)^{5/6}}$

### 一些噪声模型

- 高斯噪声
  $$
  p(z) = \frac{1}{\sqrt{2\pi}\sigma}e^{\frac{-(z-u)^2}{2\sigma^2}}
  $$
  
- 瑞利噪声

$$
p(z) = \begin{cases} \frac{2}{b}(z-a)e^{-(z-a)^2/b} & z \ge a \\ 0 & z \lt a \end{cases}
$$



### 频率域处理

使用滤波器在傅里叶变换后的图像上进行处理。

- 带阻滤波器

![image-20200907162629096](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-fqAp21.png)



- 逆滤波：利用滤波器恢复
  -  若在频谱平面对图像信号有决定影响的点或区域上，H(u,v)的值为零，那么G(u,v)的值也为零，故不能确定这些频率处的F(u,v)值，也就难以恢复原始图像f(x,y)。
- 维纳滤波：最小二乘方滤波

![image-20200907165614241](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-QZIgP1.png)

![image-20200907165205570](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-lKY1Yw.png)

### 空间域处理

空间滤波：适用于图像中唯一存在的退化是噪声时。

算数均值滤波器（$\sum$）、几何均值滤波器（$\prod$）

- 谐波均值滤波器：对盐噪声效果好，但不适用于椒噪声
- 擅长处理高斯噪声
- 中值滤波器 & 自适应中值滤波器
  

## *小波变换

小波变换是对一个函数在空间和时间上进行局部化的一种数学变换。

通过平移母小波获得信号的时间信息；通过缩放母小波的宽度获得信号的**频率特性**。

一些常用的小波 $\psi$：

![image-20200908015923669](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-08-qyrmVF.png)



- Wavelet: 在有限时间范围内变化且平均值为零的数学函数
- 具有优先的持续时间和突变的频率和振幅
- 在有限的时间平均值等于 0

### Haar 小波 哈尔

计算步骤：

1. 求均值（[9 7 3 5] -> [8 4]）
2. 求差值：**像素对的第一像素值减去像素对的平均值** （[8 4] -> [8 4 1 -1]）
3. 重复 1 & 2，进一步分解图像成分辨率更低的图像和细节系数

- 基函数是一组线性无关的函数，可以用来构造任意给定的信号，如用基函数的加权和表示

![image-20200907170305325](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-aggmwL.png)

非标准分解：用一维小波交替地对每一行和每一列像素值进行变换。

产生结果：

![image-20200907171051664](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-yBxrbG.png)

主要应用：图像降噪、图像压缩等。

## 智能图像处理（深度学习部分）

好像不用了解太多

反向传播、梯度下降、代价函数……

**Back Propagation**

![image-20200907174104688](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-uRR4Xh.png)

