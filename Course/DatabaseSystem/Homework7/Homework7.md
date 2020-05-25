## Database Homework 7

> 10185101210 陈俊潼
> 2020.5

### 11.2

This is not possible.

Because clustering indices determined the physical sequence of each relation. For each relation, there’s only one order to store its physical data.

### 11.3

The trees is shown as follows:

![image-20200523010958908](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-23-CaRbjw.png)

![image-20200523011047589](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-23-wU1Ny1.png)

![image-20200523011124346](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-23-9IXYCe.png)

### 11.4

![image-20200523011249322](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-23-0z0nFt.png)

![image-20200523011442904](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-23-PeDZ7h.png)

![image-20200523011503877](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-23-uuS8Uj.png)

![image-20200523011813159](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-23-aFE85q.png)


### 11.7

![image-20200523012624876](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-23-NxtMLH.png)

### 1.11

**a.** The bitmap index is:

| salary | Bitmap index |
| ------ | ------------ |
|Below 50000| `001000000000`|
|50000 - Below 60000| `000000000000`|
|60000 - Below 70000| `100010010000`|
|70000 - Above|`010101101111`|

**b.**

1. Construct bimap index for `dept_name`:

   | dept_name  | Bitmap index   |
   | ---------- | -------------- |
   | Comp. Sci. | `100000100010` |
   | FInance    | `010000001000` |
   | Music      | `001000000000` |
   | Physics    | `000101000000` |
   | History    | `000010010000` |
   | Biology    | `000000000100` |
   | Elec. Eng. | `000000000001` |

2. Use $Finance \cap 70000 - Above$ we get: `010000001000`.

3. Then traverse the result after apply `and` computation with index which satisfies `salary > 80000`.

### 11.23

To index strings, we can only store the prefix of string on non-leaf nodes that is enough to distinguish different strings, and only store the full string in leaf nodes. Like storing ‘Will’ at a non-leaf node and ‘William’ at leaf nodes, then ‘Willy’ and ‘Williams’ will be son nodes of the same non-leaf node. By this way, the fanout of nodes can be increased.