# 形式语言与自动机 Outline

# 概念与文法

核心问题：哪些问题可以通过计算解决（可计算型理论）

自动机理论：研究抽象机器所能解决问题的理论（图灵机：核心理论模型；以及有限状态机、文法、下推自动机等）

## 谓词逻辑与集合关系

- n元关系是定义在某域上的一组n元组的集合

- 集合A和B的二元关系R是A×B的子集；二元关系可写作 xRy

- dom(R)和ran(R)分别表示关系R的定义域和值域

![image-20200902103702649](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-02-azYbAL.png)

- 对于 $R \subseteq S\times S$ 几种特殊的关系：
  - 偏序关系：自反，反对称，传递 Eg. 自然数集合N和小于等于关系≤构成的偏序集
  - 等价关系：自反，对称，传递 -> 等价类：由等价关系确定的一组集合，每个集合中的任意元素都相互等价
    - 等价关系的秩：等价类的个数



## 字母表、图与语言

- 字母表是语言中出现的原子符号，通常用Σ表示
- 字符串是字母表中元素的序列，长度必须为有限的，长度、连接等操作在定义上都为递归
  - 长度：递归定义 $|w| = 0, w = \epsilon; |x| + 1, w = xa$
- 字符串运算：联结运算 abc.def、重复运算 (abc)*
  - 和集合有关的运算：$A \cdot B = {w | w = x \cdot y, x\in A, y \in B}$
    - 若 $\Sigma$ 为字母表，则 $\Sigma^n$  为长度为 n 的字符串集合
  - 正闭包、克林闭包
- 语言：一系列特殊字符串的集合：L⊆Σ^∗
- 图：系统描述方式
  - 标签集合D，标签函数 L:S∪T→D
  - 带标签的图可以表示为一个4元组 (S,T,D,L)
  - 树是一种特殊的有向无环图
- 迁移系统：$TS = (s, \Sigma,\rightarrow,S_0)$
- **给定字符串是否属于某个具体语言 L？** 任何问题都可以转换成语言问题 $w \in L?$
  - （可判定问题与不可判定问题）



## 逻辑语言与演绎推理

- 证明：演绎法、归纳法与反证法

- 命题逻辑
  - 一种可以判定真或假的命题描述语言
  - 由原子命题和连接算子构成
- 谓词逻辑：比命题逻辑描述能力更强的逻辑语言，增加了变量取值
  - 组成：Variable, Functions & (Predicate symbols, equality, logical connectives, quantifiers)
  - 公式 $\phi$ 在一个给定的结构 M 和赋值 $\phi$ 下成立，记为$M, \sigma \vDash \phi$ 或 $\vDash^M_\sigma\phi$
  - 在给定结构M下每个赋值成立，记为$M\vDash\phi$或$\vDash^M = \phi$
  - 任意赋值成立：$\vDash\phi$
- 演绎推理
  - 从一个集合的前提条件推导出一个结论的过程
  - 运用 Modus penens，矛盾，传递
  - 一些证明规则：
  - ![image-20200902110734521](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-02-LMMXmR.png)
  - 证明过程：对于$\frac{A}{C}$，若要证明 C 只需证明 A，A 与 C 是相继式（$H\vdash G$，H 前件，G 后件）
  - 一个证明的例子：
  - ![image-20200902113914551](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-02-u6KShf.png)



## 文法

- 包含： V(ariables) T(erminal symbols) P(roductions / rules) S(tart symbols)
  - V: 非终止符号，满足 $V \cap T = \emptyset$
  - S: 起始符号，满足 $S \in V$

- 文法的推导：$Let G=(V,T,P,S)$$，$. 有$ α→β∈P, γ,δ∈(V∪T)^∗$, 则称 $𝛾𝛼𝛿⇒_𝐺 𝛾𝛽𝛿$
  - 上述过程 = $𝛾𝛼𝛿$规约成$𝛾𝛽𝛿$
  - 最左 & 最右，依据替换次序的不同，一个语句可以有多种推导
- 文法的语言： $L(G) = {w | w\in T^*, S \Rightarrow^*_G w}$
- 符号上的描述： + 和 * 作为幂时表示长度为 1 以上 或 0 以上的表达式，如$T^*, T^+$ 等
- **定义：等价文法：如果$L(G_1) = L(G_2)$ ，则等价**

### 文法分类的乔姆斯基体系

$3 RG  \subset 2 CFG \subset 1 CSG\subset 0 PSG$

#### 0 型文法

由文法结构定义的文法，又称为递归可枚举文法、短语结构语言、递归可枚举集等

Phrase structure grammer, aka PSG

#### 1 型文法

满足：$\forall \alpha \rightarrow \beta \in P, |\beta| \ge |\alpha|$ 

又称上下文有关文法 Context sensitive grammar aka CSG

#### 2 型文法

满足：$\forall \alpha \rightarrow \beta \in P, |\beta| \ge |\alpha|$ 且 $\alpha \in V$ 

又称上下文无关文法 Context free grammar, aka CFG

例如：T = {a, b}, $S \rightarrow ASB | \epsilon, A \rightarrow aa, B \rightarrow b$  

#### 3 型文法

满足：$\forall \alpha \rightarrow \beta \in P$ 具备形式：

$A \rightarrow w$ 或 $A \rightarrow wB$，其中 $A,B\in V, w\in T^+$

又称正则文法 / 正规文法 Regular grammar, aka RG

定义上讲，空语句 $\epsilon$ 在 1 - 3 型文法中都是不允许的，但因为其不影响语言的有穷描述的存在，所以允许 $\epsilon$ 存在，但其除了用于产生空语句以外不可用于其他任何句子的推导之中。

# 自动机

## 有穷自动机 D

动机：语言的识别：

- 如果



