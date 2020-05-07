# Database Homework 6

> 10185101210 陈俊潼

### 8.1

$$
\because r_1 \cap r_2 = A \\ \text{Calculate A}^+ \text{As follows:}\\Let A^+ =A, \because A\rightarrow BC, A^+ = ABC;\\ \because B\rightarrow D, A^+ = ABCD\\\therefore \text{A is a super key of r.}\\\therefore \text{The decomposition is lossless.}
$$

### 8.2

The functional dependencies are as follows:
$$
A\rightarrow B,\ C\rightarrow B.
$$

### 8.6

$$
\text{Compute attribute closure for A,B,C,D,E:} \\
A^+ = \{ABCDE\}\\
B^+ = \{B\}\\
C^+ = \{C\}\\
D^+ = \{D\} \\
E^+ = \{ABCDE\}\\
\text{And compute the attribute closure for BC and CD}\\
BC^+ = \{ABCDE\}\\
CD^+ = \{ABCDE\}\\
\therefore F^+ = \{B\rightarrow B, C \rightarrow C, D \rightarrow D, \\
A* \rightarrow \delta, E*\rightarrow\delta,BC*\rightarrow\delta,CD*\rightarrow\delta\}\\
\text{Where } \delta \text{ is all the subset of {A,B,C,D,E},}\\
\text{ and * denotes any attribute combination.}\\
\text{The candidate keys are A, E, BC, CD.}
$$

 ### 8.9

The query is as follows. If the functional dependency satisfies, this query should return an empty result.

```sql
SELECT * FROM r R1, r R2 WHERE R1.b = R2.b AND R1.c <> R2.c
```

Assertion:

```mssql
CREATE ASSERTION fdchecker CHECK(
    NOT EXIST (SELECT * FROM r R1, r R2 WHERE R1.b = R2.b AND R1.c <> R2.c)
)
```

### 2

The decomposed relation schema is as follows:

teaches = (C, T)

timetable = (H, R, C)

teacherin = (H, T, R)

grade = (C, S, G)

studentin = (H, S, R)

### 3

By calculating $A^+,B^+, C^+, D^+, AB+ $  We get:

$A^+ = A$

$B^+ = B$

$C^+ = ACD$

$D^+ = D$

$AB+ = ABCD$

So the candidate key are AB, BC, we can use AB as its primary key.

### 4

a): Since A->B, So AC -> BC -> D, can be derived.

b): Not possible.

c): Since A->B, so AD -> BD, so we can decompose it into <u>AD->B</u> and AD -> D, can be derived.

### 5

From X->Y and X-> Z we know X->YZ.

Similarly, we have Y->XZ, Z->XY.

Now the set is {X->YZ, Y->XZ,  Z->XY}.

For X->YZ, Calculate $X^+$ in set {X->Z, Y->XZ,  Z->XY}. $X^+ = XYZ$, so Y here is extraneous.

Now the set is  {X->Z, Y->XZ,  Z->XY}.

For Y->XZ, calculate $Y^+$ in set  {X->Z, Y->Z,  Z->XY}, $Y^+ = XYZ$, so X here is extraneous.

Now the set is  {X->Z, Y->Z,  Z->XY}.

For Z->XY, X or Y here are not extraneous. So the minimal form of FDs are  {X->Z, Y->Z,  Z->XY}.

