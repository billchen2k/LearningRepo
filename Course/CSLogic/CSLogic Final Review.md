# CSLogic Final Review

<center>January 2021</center>

Background:

First-order Logic in CS: formalising the argument in propositional logic 一阶逻辑（区别于高级的量化逻辑）

Mathematics is not automatable.

## Propositional Logic

Declarative sentences: (we can consider whether they’re true or not)

Eg. The sum of the number 3 and 5 equals 8.

![image-20210110205505479](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-StBNE3.png)

Definitions:

![image-20210110205549711](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-VMBHN3.png)

### :star: Natural Deduction $\vdash$

![image-20210110205132816](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-VAD4gg.png)
$$
premise \vdash conclusion \\ sequent
$$


Implication Introduction Example

![image-20210110211603288](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-m48iAD.png)

Negation examples:

![image-20210110220850741](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-lfBysM.png)

==**NATURAL DEDUCTION RULES**==

![image-20210110205742484](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-RDs6RD.png)



Provable Equivalence:

![image-20210110212239079](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-fZBOeU.png)

### Formal Language

**BNF FORM**: Inductive definitions, like the one of well-formed propositional logic formulas above, are so frequent that they are often given by a defining grammar in Backus Naur form (BNF).

**Well-formed formula**: (Convention) If we are a rigorous computer and we call formulas well-formed iff they can be deduced to be so using the definition above.

### Semantics of Propositional Logic

- Using a truth table

![image-20210110223022836](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-nH5vQ8.png)

- *Mathematical Induction:

![image-20210110223227063](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-vnxx5j.png)

数学归纳法

### :star: Soundness and Completeness

![image-20210110223432903](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-iz3Sbk.png)



可靠性（正确性）：推导出来的都是正确的

完备性：正确的都可以推导出来

**Semantic Entailment:**

![image-20210110223615777](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-WLHkFx.png)

**Semantically equivalent:**

![image-20210110232800074](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-10-image-20210110232800074.png)

Some equivalent examples:

![image-20210110233623924](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-10-image-20210110233623924.png)



### Normal Forms

#### :star: CNF — Validity

CNF Def:

![image-20210110232828870](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-10-image-20210110232828870.png)

Calculating Process:

方法一：使用真值表。例子：

![image-20210110234000158](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-10-image-20210110234000158.png)

方法二：$\texttt{CNF(NNF(IMPL_FREE}(\Phi\texttt{)))}$

NNF: negation normal form

Impl_free -> get rid of $\to$

![image-20210111011132734](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-11-image-20210111011132734.png)

**Def: Satisfiability** —— 真值表中有一个为真

![image-20210111012152022](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-11-image-20210111012152022.png)

**Def: Validity** —— 真值表所有都为真

![image-20210111012140822](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-11-image-20210111012140822.png)

用 CNF 检查 Validity。检查每个 disjunction 中是否都有 $p \or \neg p$。

#### Horn Clauses — Satisfiability

Example of Horn Clauses:

![image-20210111011256224](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-11-image-20210111011256224.png)

Example of checking satisfiability:

![image-20210111011701050](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-11-image-20210111011701050.png)

Example:

![image-20210111013435861](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-11-image-20210111013435861.png)

## Predicate Logic

*The need for a richer language.*

### Formal Language

Def:

![image-20210111014814732](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-11-image-20210111014814732.png)

- Function symbols $\mathcal{F}$
- Predicate symbols $\mathcal{P}$
- Constants $\mathcal{C}$

Note that one can always do without function symbols, by using a predicate symbol instead. However, it is usually neater to use function symbols. **To generate a neater symbol.**

- **Free variable**: $\phi$ is a leaf node such that there’s no path upwards from node $x$ to $\forall x$ or $\exists x$.
- Bound variable: Vice versa.

Example:

![image-20210111014859230](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-11-image-20210111014859230.png)

**Subtitution**:

:exclamation: Only free variable can substitute!

![image-20210111014953066](https://billc.oss-cn-shanghai.aliyuncs.com/file/2021-01-11-image-20210111014953066.png)

### Natural Deduction $\vdash$



## Verification by Model Checking

- Some useful equivalences:

![image-20201221203100461](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-uv3ZIR.png)

![image-20201221203557578](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-SK8ptN.png)

### Labeling algorithm

- May cause the problem of state explosion
- No efficient general solution for now

## Hoare Logic

## Modal Logic By Notion in Logic

- No effe