# CS Logic Assignment 4

> 10185101210 陈俊潼

Read the following specification: Alice, Bob and Charles live in an apartment. One day Alice is found dead in her room. Please translate the following clues into predicate logic formulas:

Construct model $\mathcal{M} = \{\mathcal{F}, \mathcal{P}\}$. First define following predicate relations $\mathcal{P}$:
$$
H(a, b): \text{a hates b.}\\
R(a, b): \text{a is richer than b.}\\
K(a, b): \text{a killed b.}
$$
And nullary function symbols $\mathcal{F}$ as follows:
$$
a: \text{Alice} \\
b: \text{Bob}\\
c: \text{Charles}\\
$$
(1) A killer always hates, and is no richer than his victim:
$$
\forall x \forall y K(x,y) \to H(x,y) \and \neg R(x,y)
$$
(2) Charles hates no one that Alice hates:
$$
\forall x H(a, x) \to \neg H(c, x)
$$
(3) Alice hates everybody except Bob:
$$
H(a, a) \and H(a, b)
$$
(4) Bob hates everyone who is either not richer than Alice or hated by Alice
$$
\forall x \Big(H(a, x) \and \neg R (x,a) \to H(b, x)\Big)
$$
(5) No one hates everyone.
$$
\forall x \exists y\neg H(x, y)
$$
(6) No one is richer than himself/herself. Who is richer can be determined for any two different persons.
$$
\forall x (\neg R(x, x))\\
\forall x\forall y(x \ne y \to R(x, y) \or R(y,x))
$$
From above predicate assumptions, we can get following deductions about hating relations:

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-11-30-1o4uJb.png" alt="image-20201130222440369" style="zoom:50%;" />

From (1) we know that every killer always hates the victim, we know that Charles can’t be the killer, since he doesn’t hate Alice. Now there are two possible killers

1. Alice suicided.
2. Bob killed Alice.

If it was the second circumstance that Bob killed Alice, from (1) we know that **Bob is no richer than Alice**. Then from (4) we know that Bob hates everyone who is not richer than Alice, so that **Bob hates bob**. However, from the graph above we had already confirmed that Bob hates Charles and Alice. Now if Bob also hates bob himself, Bob is hating everyone in this dormitory, which violates (5): No one hates everyone. So Bob can’t be the killer

In conclusion, Alice is the killer, she suicided.