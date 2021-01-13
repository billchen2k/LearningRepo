

#            CSLogic Final Review

<center>January 2021</center>

Background:

First-order Logic in CS: formalising the argument in propositional logic 一阶逻辑（区别于高级的量化逻辑）

Mathematics is not automatable.

## Propositional Logic

**Priority** : $\neg, \and,\or, \to$

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

![image-20210110232800074](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-Giomb9.png)

Some equivalent examples:

![image-20210110233623924](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-CwWkvw.png)

### Normal Forms

#### :star: CNF — Validity

CNF Def:

![image-20210110232828870](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-NIdAdG.png)

Calculating Process:

方法一：使用真值表。例子：

![image-20210110234000158](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-B3qLma.png)

**方法二：$\texttt{CNF(NNF(IMPL_FREE}(\Phi\texttt{)))}$**

NNF: negation normal form

Impl_free -> get rid of $\to$

![image-20210111011132734](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-nwTMPh.png)

**Def: Satisfiability** —— 真值表中有一个为真

![image-20210111012152022](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-IbSeNV.png)

**Def: Validity** —— 真值表所有都为真

![image-20210111012140822](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-iSKku0.png)

用 CNF 检查 Validity。检查每个 disjunction 中是否都有 $p \or \neg p$。

#### Horn Clauses — Satisfiability

Example of Horn Clauses:

![image-20210111011256224](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-SZptPm.png)

Example of checking satisfiability:

![image-20210111011701050](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-foO3UA.png)

Example:

![image-20210111013435861](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-ev4bbw.png)

## Predicate Logic

*The need for a richer language.*

### Formal Language

Def:

![image-20210111014814732](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-ut60PB.png)

- Function symbols $\mathcal{F}$ (with arity)
- Predicate symbols $\mathcal{P}$ （with arity)
- Constants $\mathcal{C}$

Note that one can always do without function symbols, by using a predicate symbol instead. However, it is usually neater to use function symbols. **To generate a neater symbol.**

- **Free variable**: $\phi$ is a leaf node such that there’s no path upwards from node $x$ to $\forall x$ or $\exists x$.
- Bound variable: Vice versa.

Example:

![image-20210111014859230](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-jYwPY6.png)

**Subtitution**:

:exclamation: Only free variable can substitute!

![image-20210111014953066](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-mVwHWB.png)

### Natural Deduction $\vdash$

Rules:

![image-20210111015901097](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-NRaLu9.png)

$\forall$:

![image-20210111020211599](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-Lqx8b3.png)

$\exists$:

![image-20210111023943097](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-11-QbfLyP.png)

Comparison between a legal statement vs illegal proof:

![image-20210112164105207](../../../../Library/Application%20Support/typora-user-images/image-20210112164105207.png)

**:exclamation: The fresh variable should never get out of the box**

### Semantics $\vDash_l$

Predicate logic can’t list out a truth table for it.

#### Def: Models

![image-20210112165112856](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-0jUfIF.png)

![image-20210112211601689](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-LlgWOU.png)

**Def: Look-Up Tables**

![image-20210112171549575](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-PqLm6B.png)

With Look-Up Tables & Model we can get the satisfaction relation **(structural induction)**:

![image-20210112171613877](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-sAoF2I.png)

#### **Satisfiability & Semantic Entailment:**

![image-20210112172034964](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-0lDMY0.png)

 Examples:

![image-20210112185937533](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-OF7qXC.png)Equality

![image-20210112185651019](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-lnHr1a.png)

#### Undecidability

![image-20210112173155553](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-hOmMWr.png)

![image-20210112173330948](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-323uDl.png)

## Verification by Model Checking

Model Checking: Model based, automated.

### Proof Based vs Model Based

![image-20210112185129769](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-B2fJF0.png)

### CTL Computation Tree Logic

![image-20210112183009786](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-eBWUWE.png)

Where *Temporal Connectives* means:

#### Semantics

- A and E to quantify over the breadth in a branching point
  - A: All alternatives
  - E: Exists at least one alternative
- G and F to quantify along the paths:
  - G: All future paths, Globally
  - F: There exists at least one Future state
- X: NeXt State along the path
- U: Until Operator: **U**ntil: *φ* has to hold *at least* until at some position *ψ* holds. This implies that *ψ* will be verified in the future.
  - ![image-20210112213957164](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-jqVexo.png)

![image-20210112193739677](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-lvA58r.png)

**Priorities:**

![image-20210112183343463](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-XxFqNI.png)

#### CTL Model

Semantics:

![image-20210112191632948](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-iA8SIK.png)

**Some useful equivalences:**

![image-20201221203100461](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-uv3ZIR.png)

![image-20201221203557578](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-10-SK8ptN.png)

### **Labeling algorithm**

Used to check CTL satisfiability.

- May cause the problem of state explosion
- No efficient general solution for now
- No efficient general solutions

**Procedure:**

This runs on a reduced version of CTL.

![image-20210112202030334](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-AYlMZV.png)

![image-20210112202044630](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-MxXvG9.png)

Transition:
$$
AG(\phi) = \neg E(\top U\phi)
$$


## Hoare Logic

*A proof based method*.

### Hoare Triples

The construct of precondition, postcondition and code:

![image-20210112204813434](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-XnZKJg.png)



- Partial correctness: we do not require the program to terminate.
- Total correctness: we do require the program to terminate.

### Proof Rules

![image-20210112204858902](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-KM7flA.png)



Examples:

![image-20210112204914564](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-QGu6NY.png)

![image-20210112204931841](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-3MReDd.png)

## Modal Logic*

Semantics:

![image-20210112204459429](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-JFfkVq.png)

Example:

![image-20210112204557479](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-12-M0sMbb.png)