# Maude

## Intro

常用 Module：commonly used

### Convention

Maude name: capital

Sort name: First character capital

Variable name: single capital charactor

Operator name: lower case

### Grammar

- sort / sorts
- eq
- op / ops
  - id: identity `op nil: -> List-Nat [ctor id: nil]`

- ceq: conditional equations:
  - `ceq different? (N , M) = true if N =/= M .`
  - `ceq brothzero? (N , M) = true if N == M /\ M == 0 .`

## Function Maudes

Example of PNAT:

![image-20210509160911518](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-05-09-5eiOvI.png)

`prec` 优先级参数，值越小优先级越大

**gather:** to clear ambiguous parsing:

![image-20210509164723717](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-05-09-csLTVZ.png)

### Grammar

mod declaration:

![image-20210604184527864](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-04-zpyErv.png)

include module

- Protecting: Import AS IS, can’t modify
- Including: Allow Overloading
- Extending: ?

sorts and subsorts:

![image-20210604184543289](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-04-QZdSTF.png)

variables:

```haskell
var x : number .
vars c1 c2 c3 : color .
```

operators: *** prefix and mix fix are both supported

![image-20210604184605996](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-04-irKSft.png)

Gather rule: `[ gather e E & ]` , where e: <; E: ≤; &: Any precedence.

conditional equal. →  `/\` AND。注意 `/\` 只作为 ceq 的条件并列，为 condition concatenation。

```haskell
ceq different?( N , M ) = true if N =/= M .
/\ --- AND SIGN
```

// Can also use `owise` flag：

```haskell
ceq reply(I) = "Questions after class, Please" 
	if (S:String) ? := I .
eq reply(I) = "Shut up!" [owise]
```

conditional membership axiom (cmb)

```haskell
cmb N : Nat if N : NzNat .
--- This is the same with:
subsort NzNat < Nat .
```

member axiom:

```haskell
var N : Nat . var M : NzNat .
cmb N / M : NzNat if ( N =/= 0 ) .
--- This is the same with
vars N M : NzNat .
mb N / M : NzNat .
--- Another Example
mb N:Number of Hearts : FemCard .
mb Q of S:Suits : FemCard .
```

if_then_else_fi:

```haskell
max ( M , N ) = if N > M then N else M fi .
```

Using pattern match `:=` as a condition:

```haskell
fmod IRRITABLE-PROFESSOR is

	ceq reply (I) = "Question after class, please" 
					if (S:String)? := I .
endfm
```



### Example: FemCard

Four ways to return first `FemCard` from a deck:

```
--- Using if_then_else_fi
eq FirstFemCard ( C : D ) if CardNum(C) == Q or CardSuit(C) == Heart then C 
	else FirstFemCard(D) fi .
eq FirstFemCard ( null ) = null .
```

```
--- Using ceq
ceq FirstFemCard ( C : D ) = C if CardNum(C) == Q /\ CardSuit(C) == Heart .
eq  FirstFemCard ( D ) [owise] .
eq FirstFemCard ( null ) = null .
```

```
--- Using ceq and _::_
ceq FirstFemCard ( C : D ) = C if C :: FemCard .
eq  FirstFemCard ( D ) [owise] .
eq FirstFemCard ( null ) = null .
```

```
--- Using ceq and pattern matching
ceq FirstFemCard ( C : D ) = C if Q of S:Suit := C .
ceq FirstFemCard ( C : D ) = C if N:Number of Hearts := C .
eq  FirstFemCard ( C : D ) = FirstFemCard [owise] .
eq FirstFemCard ( null ) = null .
```

### Example: BST

```haskell
fmod BINARY-TREE is

including NAT .
sorts BTree Leaf .
subsorts Leaf < BTree .
op leaf : -> Leaf .
op ((_,_,_)) : BTree Nat BTree -> BTree .

vars LT RT : BTree .
vars N N' : Nat .

--- isBSTree

op right-most : BTree -> Nat .
op left-most : BTree -> Nat .
ceq right-most((LT,N,RT)) = right-most(RT) if RT =/= leaf .
eq right-most((LT,N,leaf)) = N .
ceq left-most((LT,N,RT)) = left-most(LT) if LT =/= leaf .
eq left-most((leaf,N,RT)) = N .

op isBSTree : BTree -> Bool .
eq isBSTree(leaf) = true .
ceq isBSTree((LT,N,RT)) = isBSTree(LT) and isBSTree(RT) and right-most(LT) < N and left-most(RT) > N
    if LT =/= leaf /\ RT =/= leaf .
ceq isBSTree((LT,N,RT)) = isBSTree(LT) and right-most(LT) < N
    if LT == leaf /\ RT =/= leaf .
ceq isBSTree((LT,N,RT)) = isBSTree(RT) and left-most(RT) > N
    if LT =/= leaf /\ RT == leaf .
eq isBSTree((LT,N,RT)) = true [ owise ] .

--- Insert

op insert : BTree Nat -> BTree .
eq insert(leaf,N) = (leaf,N,leaf) .

eq insert((LT,N',RT),N) =
    (if N' > N then (insert(LT,N),N',RT)
        else
            (if N' < N then (LT,N',insert(RT,N))
            else
        (LT,N',RT) fi)
    fi) .

--- Search

op search : BTree Nat -> Bool .
eq search(leaf,N) = false .

ceq search((LT,N',RT),N) = ( if N' > N then search(LT,N)
    else
        (if N' < N then search(RT,N) else true fi)
    fi )
    if isBSTree((LT,N',RT)) .

--- Remove

op rm-right-most : BTree -> BTree .
eq rm-right-most(leaf) = leaf .
ceq rm-right-most((LT,N,RT)) = rm-right-most(RT) if RT =/= leaf .
eq rm-right-most((LT,N,leaf)) = LT .

op remove : BTree Nat -> BTree .
eq remove(leaf,N) = leaf .

ceq remove((LT,N,RT),N') = (remove(LT,N'),N,RT) if N > N' /\ isBSTree((LT,N,RT)) .
ceq remove((LT,N,RT),N') = (LT,N,remove(RT,N')) if N < N' /\ isBSTree((LT,N,RT)) .
ceq remove((LT,N,RT),N) = (if LT == leaf then RT else (rm-right-most(LT),right-most(LT),RT) fi)
    if isBSTree((LT,N,RT)) .

endfm
```

