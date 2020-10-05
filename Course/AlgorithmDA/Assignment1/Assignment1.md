# 算法设计与分析 Assignment 1

> 10185101210 陈俊潼

## 1

| A           | B            | O    | o    | $\Omega$ | $\omega$ | $\Theta$ |
| ----------- | ------------ | ---- | ---- | -------- | -------- | -------- |
| $lg^kn$     | $n^\epsilon$ | NO   | NO   | YES      | YES      | NO       |
| $n^k$       | $c^n$        | NO   | NO   | YES      | YES      | NO       |
| $\sqrt{n}$  | $n^{\sin n}$ | NO   | NO   | NO       | NO       | NO       |
| $2^n$       | $2^{n/2}$    | YES  | YES  | NO       | NO       | YES      |
| $n^{\lg c}$ | $c^{\lg n}$  | YES  | NO   | YES      | NO       | YES      |
| $\lg(n!)$   | $\lg(n^n)$   | YES  | NO   | YES      | NO       | YES      |

## 2

Each line represents an equivalent class, and the growth rate increases as the line goes down.
$$
n^{1/\lg n}\\
1 \\
lg(lg^*n), lg^*lg(n)\\
 \ln \ln n\\
lg^2(n)\\
lg^*n, \ln n\\
\lg ^2 n\\
n \\
nlgn\\
n^2 \\
n^3 \\
2^{\sqrt{2lgn}}\\
\sqrt{2}^{\lg n}, 2^{\lg n}, 2^{lg^* n}\\
4^{\lg n}\\
(\lg n)!\\
(\lg n)^{\lg n},n^{\lg \lg n} \\
\Big(\frac{2}{3}\Big)^n\\
2^n\\
n \cdot 2^n\\
e^n\\
n!\\
(n+1)!\\
2^{2^n}\\
2^{2^{n+1}}\\
$$

## 3

a. False. Because if $\log n = O(n^2)$, but $n^2 \ne O(\log n)$.

b. False. Because $n^2 + n = \Theta (n^2) \ne \Theta(min(n, n^2))$

c. True.

Because $f(n) = O(g(n))$ then $\exists c, n_0. f(n_0) \le cg(n)$

So $\lg(f(n_0)) \le \lg(cg(n)) = \lg c + \lg g(n)$

So $\lg f(n) = O (\lg(g(n)))$.

d. False.

Because $f(n) = O(g(n))$ then $\exists c, n_0. f(n_0) \le cg(n_0)$

So $2^{f(n_0)} \le 2^{cg(n_0)}$ 

So $2^{f(n_0)} = O(2^{cg(n_0)})$ , in which case $c > 0$, so $O(2^{cg(n_0)})\ne O(2^{g(n_0)})$

## 4

The pseudocode is as follows:

```
SELECTION-SORT-REVERSE(A, n)

current_pos := n - 1
while current_pos >= 0
	greatest_pos = 0
	current_greatest = 0
	for i := 0 to current_pos:
		if A[i] > current_greatest
			current_greatest := A[i]
	EXCHANGE_ELEMENT(greatest_pos, n - 1)
	current_pos := current_pos - 1
```

Loop invariant: The array[current_pos, n-1] is always a sorted array.

Bestcase: $\Theta(n^2)$

Worstcase: $\Theta(n^2)$

