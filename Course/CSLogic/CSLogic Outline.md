# CSLogic Outline

## Predicate Logic

- Function symbols:
- Predicate symbols:

Note that one can always do without function symbols, by using a predicate symbol instead. However, it is usually neater to use function symbols. To generate a neater symbol.

- Free variable: $\phi$ is a leaf node such that there’s no path upwards from node $x$ to $\forall x$ or $\exists x$.
- Bound variable: Vice versa.

## Verification by Model Checking

- Some useful equivalences:

![image-20201221203100461](CSLogic Outline.assets/image-20201221203100461.png)

![image-20201221203557578](CSLogic Outline.assets/image-20201221203557578.png)

### Labeling algorithm

- May cause the problem of state explosion
- No efficient general solution for now