# Algorithm Final Review

<center>January 2021</center>

## Preface. 基础

### 一些概念

- Loop invariant 循环不变式：问题的某一部分的不变的性质，如 A[1..j-1] 已经排好了序。
-  :star: 多重对数函数：$lg *n$ 表示多重对数（区别于 $f^{(i)}(n)$，其表示多重函数）

![image-20201117182123136](https://billc.oss-cn-shanghai.aliyuncs.com/file/2020-11-17-image-20201117182123136.png)

### 算法的一般特性

- **有穷性：** 一个算法必须保证执行**有限步**之后结束；
- **确切性：** 算法的每一步骤必须有**确切的定义**；
- **输 入：**一个算法有0个或多个输入，以刻画运算对象的初始情况，所谓0个输入是指算法本身限定了初始条件；
- **输 出**：一个算法有一个或多个输出，以反映对输入数据加工后的结果。没有输出的算法是毫无意义的；
- **可行性：** 算法原则上能够**精确地运行**，而且人们用笔和纸做**有限次运算**后即可完成。

如何衡量效率（efficiency）：

- 精度和可操作性之间的权衡（trade-off between precision and operability）

### 函数增长

几个渐进函数：

- $\Theta$ ：渐进准确界
- $O$： 准确上界 => $o$ 不准确上界
- $\Omega$： 准确下界 => $\omega$ 不准确下界

![image-20201117181200488](https://billc.oss-cn-shanghai.aliyuncs.com/file/2020-11-17-image-20201117181200488.png)

形式化定义：

> O(g(n)) ={ f(n) ：存在正常量 c、$n_0$，使 $\forall n \ge n_0,, 0 \le f(n) \le cg(n)$ }
>
> o(g(n)) ={ f(n) ：存在正常量 c、$n_0$，使 $\forall n \ge n_0,, 0 \le f(n) \lt cg(n)$ }

（非紧张确界的差别：趋近于无穷是时是否相等）

Eg.

![image-20201117185132048](../../../../Library/Application%20Support/typora-user-images/image-20201117185132048.png)

Eg2. 注意 $n^{lgc}$ 和 $c^{lgn}$ 的等价性

![image-20201117185511332](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-17-ksFdRO.png)

## Divide & Conquer

### 求解方法

- 代入法
- ![image-20201117191152469](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-17-zX077y.png)
  - 对于所有 c >= 1，最后一个步骤都成立
  - 类似于数学归纳法的思路
- 递归树法
  - ![image-20201117191326515](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-17-lxEFdU.png)
- :star: 主方法

![image-20201117190153085](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-17-KJ7Pjy.png)

也可以使用原始的方法，直接代入进行计算。

![image-20201117194658364](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-17-VWouY7.png)

## Sorting

| 排序算法 | 最佳时间复杂度 | 平均时间复杂度 | 最坏时间复杂度  | 稳定性 |
| -------- | -------------- | -------------- | --------------- | ------ |
| 选择排序 | O(N^2)         | O(N^2)         | O(N^2)          | 不稳定 |
| 插入排序 | O(N)           | O(N^2)         | O(N^2)          | 稳定   |
| 冒泡排序 | O(N)           | O(N^2)         | O(N^2)          | 稳定   |
| 希尔排序 | O(N)           | O(NlogN)       | O(N^S)（1<S<2） | 不稳定 |
| 快速排序 | O(NlogN)       | O(NlogN)       | O(N^2)          | 不稳定 |
| 堆排序   | O(NlogN)       | O(NlogN)       | O(NlogN)        | 不稳定 |
| 归并排序 | O(NlogN)       | O(NlogN)       | O(NlogN)        | 稳定   |

### Heap Sort

分为 `Build Heap` 和 `Max Heapify` 两个步骤。

节点的高度：该节点到叶节点最长简单路径上边的数目

堆的高度：根节点的高度

- 每个孩子的子树的大小至多为 2n/3。

### Quicksort

运行过程：

![image-20201118002705194](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-18-UQoSi4.png)

只要划分是常数比例的，算法的运行时间总是 O(nlgn)。

### Counting Sort

使用三个数组，B 存放输出、A 原数组、C 存放临时

![image-20201118004955871](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-18-fy2Hp7.png)

### Bucket Sort & Radix Sort

简单的排序。对于桶排序，可以在内部使用 merge sort 来将最差复杂度减少一些。对于桶排序，可以使用更加复杂的方式来决定。

#### 排序方法的下界

决策树模型决定了排序算法的下界。

![image-20210113201308950](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-13-4o5bUO.png)

核心：
$$
n! \le l \le 2^h
$$


## 动态规划

核心步骤：

1. 刻画一个最优解的结构特征
2. 递归地定义最优解的值
3. 计算最优解的值，采用自底向上的方法
4. 利用计算出的信息构造最优解

### Cut-Rod

自顶向下法既递归。

![image-20210113195144320](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-13-6WRshq.png)

Concepts: 子问题图：

![image-20210113195239876](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-13-tFFxlx.png)

### 矩阵链乘法

递归式：
$$
m[i, j]=\left\{\begin{array}{ll}
0 & \text { if } i=j \\
\min _{i \leq k<j}\left\{m[i, k]+m[k+1, j]+p_{i-1} p_{k} p_{j}\right\} & \text { if } i<j
\end{array}\right.
$$
m[ij] 为 i 到 j 之间的最优解， s 存放最优分隔的地点。

Eg.



![image-20201118152456084](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-18-dlAz4d.png)

## 贪心

### 活动选择问题

注意问题的最优子结构：

最优子结构的意思是局部最优解能决定全局最优解（对有些问题这个要求并不能完全满足，故有时需要引入一定的近似）。简单地说，问题能够分解成子问题来解决。（Wikipedia）

### 霍夫曼编码

期中考过了。

## 图算法

### 查找

#### BFS 广度优先搜索

维护一个队列，使用三种颜色查找。

广度优先树：由源节点可以到达的节点组成

伪代码：

```pseudocode
BFS(G, s)
for each vertex u in G.V-{s}
	u.color = WHITE
	u.d = inf
	u.pi = NIL
s.color = gray
s.d = 0
s.pi = NUL
Q = empty
ENQUEUE (Q, s)
while Q != empty:
	u = DEQUEUE(Q)
	for each vertex v in G.Adj[u]
		if u.color == WHITE:
            v.color = GRAY
            u.d = u.d + 1
            v.pi = u
            ENQUEUE (Q, v)
	u.color = BLACK
```



#### DFS 深度优先搜索

概念：每个节点有发现时间 $u.d$ 和完成时间 $u.f$。

伪代码：

```pseudocode
DFS(G)
for each vertex u in G.V
	u.color = WHITE
	u.pi = NIL
time = 0
for each vertex u in G.V
	if u.color == WHITE
		DFS_VISIT(u)
		
DFS_VISIT(G, u)
time = time + 1
u.d = time
u.color = GRAY
for each v in G:Adj[u]
	if v.color == WHITE:
		v.pi = u
		DFS_VISIT(G, v)
u.color = BLACK
time = time + 1
u.f = time
```



DFS 的执行过程：

![image-20210111230722660](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-5ZR1H5.png)

几个边的概念（针对 DFS 的概念）：

![img](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-uB6m0J.png)

定义：

![image-20210111230442500](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-NDpF1j.png)

横向边：其他所有的边。



### Topological Sorty 拓补排序

对原图进行 DFS 即可，每结束一个节点就将该节点输出到最终结果的链表的最前方。

### 最小生成树

轻量级边：横跨两个分隔的权重最小的边。

#### Kruskal

从小到大遍历所有边，如果这一条边左右已经属于同一棵树则跳过。

![image-20210112225305579](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-u5rj3F.png)

复杂度 $O(VlgV)$

使用不想交的数据结构来维护不相交的元素集合。

#### Prim

算法的每一步从连接 A 和 A 之外的所有轻量级边中选择一个加入到 A 中。

![image-20210112225314295](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-ckp2vr.png)

复杂度：$O(E\lg V)$

## 最短路

### 单源最短路

#### Belman-Ford

可以处理负权重的问题。

运行的总时间为 O(VE)，

![image-20210113002802457](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-13-t6uhHR.png)

#### Dijikstra

不能处理负权重的问题。

复杂度为 O(ElogV)。

![image-20210113002811788](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-13-8ogj9Y.png)

### 多源最短路

#### SLOW_SHORTEST_PATH

使用类似于矩阵乘法的思想进行计算。

复杂度 $O(V^4)$ 或 $O(V^3logV)$

![image-20210113162716826](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-13-g5Y7aH.png)

#### Floyd-Warshall 算法

动态规划，三重循环。
$$
d_{i j}^{(k)}=\left\{\begin{array}{ll}
w_{i j} & \text { 若 } k=0 \\
\min \left(d_{i j}^{(k-1)}, d_{i k}^{(k-1)}+d_{k j}^{(k-1)}\right) & \text { 若 } k \geqslant 1
\end{array}\right.
$$


复杂度：$O(V^3)$

## 最大流

**容量守恒**：对于所有节点 $u, v\in V， 要求 0 \le f(u,v) \le c(u,v)$，其中 f 是流，c 是容量

**流量守恒**：对于 $u\in V - \{s, t\}, \sum_{v\in  V} f(v,u) = \sum_{v \ in V} f(u,v)$。

### Ford-Fulkerson

利用残存网络来计算。

概念：递增、抵消 Cancellation

增广路经：残存网络中一条 s 到 t 的简单路径

残存容量：在增广路径 p 上能够为每条边增加的流量的最大值为路径 p 的残存容量.

**切割**

![image-20210113184609095](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-13-XFhzxn.png)

最大流最小切割定理：最大流最小割定理是网络流理论的重要定理。是指在一个网络流中，能够从源点到达汇点的最大流量等于如果从网络中移除就能够导致网络流中断的边的集合的最小容量和。即在任何网络中，最大流的值等于最小割的容量。

**最小切割**：一个网络的最小切割是网络中容量最小的切割。

![image-20210113184714595](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-13-uySszv.png)

Ford-Fulkerson：利用 p 来对流进行修改。

## NP 完全性

### Definition

Reference: https://zhuanlan.zhihu.com/p/73953567

- P 问题：多项式时间内能解决的问题
- NP 问题：多项式时间内能证明的问题
- NPC 问题 (NP-Complete)：NP 完备问题，对多项式时间规约这个工具而言是完备的（所有其他问题都可以规约到 NPC 问题上）。定义：
  - 如果一个问题Q，它满足以下两条性质：
    (1). Q是NP问题
    (2). 任一NP问题都可在多项式时间内归约到问题Q
    那么我们说问题Q是NPC问题。
- NP-Hard 问题：最难的问题，如果所有[NP](https://zh.wikipedia.org/wiki/NP_(複雜度))问题都可以[多项式时间归约](https://zh.wikipedia.org/wiki/多项式时间归约)到某个问题，则称该问题为NP困难。（Definitio of Wikipedia）
  - 一个问题仅满足性质(2)，而不满足性质(1)时，我们说该问题时NPH问题（NP-hard，NP-难问题）。

一个 NPC 问题首先要是一个 NP问题，然后是 NP-Hard 问题。

### Examples

- 欧拉回路：经过所有 edge 一次（P 问题） $O(V+E)$
  哈密尔顿回路：**经过所有点一次**（NPC 问题）

其他一些经典的 NPC 问题：布尔可满足性问题 SAT、顶点覆盖问题、分团覆盖问题

Vertex Cover, Clique Cover.

- 顶点覆盖问题：对于图 G，顶点覆盖是一个子集 $V’ \subseteq V$，如果有 $(u,v) \in E$，则 $u \in V’$ 或 $v \in V’$ 或同时成立。
- 分团问题：无向图 G 的团 $V’\subseteq V$ 其中每一对定点之间都由 E 中的一条边连接。（一个团是 G 的一个完全子图）。团问题是要寻找图中规模最大的团的问题。

P、NP、NP-Hard 之间的关系

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-06-C6FFqc.png" alt="image-20210106201438454" style="zoom:33%;" />

---

## 期末考试相关

题目分布：

- [ ] 排序算法
- [x] 堆排序
- [ ] 主方法
- [x] 图遍历算法
- [ ] 生成树算法
- [x] 路径问题
- [x] 多源点对最短路径
- [ ] 动态规划法
- [x] 贪心法
- [x] 网络流
- [x] 复杂性



考试形式和期中考试类似，选择和简答题相对简单

- [ ] 五个渐进符号相关的内容
- [ ] 贪心算法、动态规划算法、分治算法

大题不会要求每一个题都写出伪代码。

**动态规划需要写出动态规划的循环过程**

### 图论相关

- 图的DSF似乎不会出大题
- 所有点的最短路径和最短路径合在一起出题
- 最小生成树：贪心算法，算法比较简单
  - Kruskal 算法，Prim 算法（对比堆排序）
- 书上算法的包装
- 网络流：最大流 -> 对偶问题：最小割，问题的规约：
  —— 将另一个问题规约到网络流问题进行求解
- NP 复杂性：不会考规约，了解 P 类，NP 类，NP-C 类的概念
  - 规约的时间