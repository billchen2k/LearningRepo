# K-Means

> 10185101210 陈俊潼
>
> East China Normal University

K-Means 均值聚类，主要代码位于 kmeans.ipynb 中。依次执行所有代码块即可。

## K=2

K = 2 时，随机选择两个点作为聚类起点（用红色标注）：

![2021-01-02-NA5GOD](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-NA5GOD.png)

经过了四次迭代后中心坐标不再改变。迭代过程如下图所示：

![2021-01-02-W9TyOs](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-W9TyOs.jpg)
![2021-01-02-DIhsS5](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-DIhsS5.jpg)
![2021-01-02-GCnoTZ](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-GCnoTZ.jpg)

最终聚类结果：

![2021-01-02-LRpmOf](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-LRpmOf.jpg)


主要日志：

```
<2021-01-02 19:53:59 INFO>: K-Means started. K = 2, MAX_EPOCHS = 10
<2021-01-02 19:54:00 INFO>: [EPOCH 0] Centroid updated: [[16.6 13.4] [ 6.8  7.8]]
<2021-01-02 19:54:00 INFO>: [EPOCH 0] Current SSE: 16.695507816124437; Centroid offset: 8.366600265340756
<2021-01-02 19:54:00 INFO>: [EPOCH 1] Centroid updated: [[14.33 14.56] [ 5.09  4.82]]
<2021-01-02 19:54:00 INFO>: [EPOCH 1] Current SSE: 12.57577169192891; Centroid offset: 4.276133513433808
<2021-01-02 19:54:00 INFO>: [EPOCH 2] Centroid updated: [[13.9 14.2] [ 4.6  4.2]]
<2021-01-02 19:54:00 INFO>: [EPOCH 2] Current SSE: 11.654674875992491; Centroid offset: 0.9681621903028267
<2021-01-02 19:54:01 INFO>: [EPOCH 3] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:54:01 INFO>: [EPOCH 3] Current SSE: 11.654674875992491; Centroid offset: 0.0
<2021-01-02 19:54:01 INFO>: Centroid coordinates: [[13.9 14.2] [ 4.6  4.2]]
```

最终可以得到聚类中心的坐标为：`(4.6, 4.2) (13.9, 14.2)`

## K=2-5

将 K 分别设置为 2、3、4、5，并分别计算。得到分别的最终的聚类结果和聚类中心如下：

![2021-01-02-hzd3SD](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-hzd3SD.jpg)

![2021-01-02-6kxCAA](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-6kxCAA.jpg)

![2021-01-02-sWHJLe](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-sWHJLe.jpg)

得到 SSE 和 K 的关系如下。可以看出随着 K 的增加，SSE 的值逐渐减小，可以认为分类效果更好。但当 K = 5 时，分类簇相对数据点过多，每次的聚类效果会存在一定的随机性：

![2021-01-02-qoLEJG](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-qoLEJG.png)

主要日志如下：

```
<2021-01-02 19:53:59 INFO>: K-Means started. K = 2, MAX_EPOCHS = 10
<2021-01-02 19:54:00 INFO>: [EPOCH 0] Centroid updated: [[16.6 13.4] [ 6.8  7.8]]
<2021-01-02 19:54:00 INFO>: [EPOCH 0] Current SSE: 16.695507816124437; Centroid offset: 8.366600265340756
<2021-01-02 19:54:00 INFO>: [EPOCH 1] Centroid updated: [[14.33 14.56] [ 5.09  4.82]]
<2021-01-02 19:54:00 INFO>: [EPOCH 1] Current SSE: 12.57577169192891; Centroid offset: 4.276133513433808
<2021-01-02 19:54:00 INFO>: [EPOCH 2] Centroid updated: [[13.9 14.2] [ 4.6  4.2]]
<2021-01-02 19:54:00 INFO>: [EPOCH 2] Current SSE: 11.654674875992491; Centroid offset: 0.9681621903028267
<2021-01-02 19:54:01 INFO>: [EPOCH 3] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:54:01 INFO>: [EPOCH 3] Current SSE: 11.654674875992491; Centroid offset: 0.0
<2021-01-02 19:54:01 INFO>: Centroid coordinates: [[13.9 14.2] [ 4.6  4.2]]
<2021-01-02 19:56:29 INFO>: K-Means started. K = 2, MAX_EPOCHS = 10
<2021-01-02 19:56:30 INFO>: [EPOCH 0] Centroid updated: [[13.9 14.2] [ 4.6  4.2]]
<2021-01-02 19:56:30 INFO>: [EPOCH 0] Current SSE: 11.654674875992491; Centroid offset: 5.123475382979798
<2021-01-02 19:56:30 INFO>: [EPOCH 1] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:30 INFO>: [EPOCH 1] Current SSE: 11.654674875992491; Centroid offset: 0.0
<2021-01-02 19:56:30 INFO>: Centroid coordinates: [[13.9 14.2] [ 4.6  4.2]]
<2021-01-02 19:56:45 INFO>: K-Means started. K = 2, MAX_EPOCHS = 10
<2021-01-02 19:56:45 INFO>: [EPOCH 0] Centroid updated: [[ 4.6  4.2] [13.9 14.2]]
<2021-01-02 19:56:45 INFO>: [EPOCH 0] Current SSE: 11.654674875992491; Centroid offset: 4.695742752749558
<2021-01-02 19:56:46 INFO>: [EPOCH 1] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:46 INFO>: [EPOCH 1] Current SSE: 11.654674875992491; Centroid offset: 0.0
<2021-01-02 19:56:46 INFO>: Centroid coordinates: [[ 4.6  4.2] [13.9 14.2]]
<2021-01-02 19:56:46 INFO>: K-Means started. K = 3, MAX_EPOCHS = 10
<2021-01-02 19:56:46 INFO>: [EPOCH 0] Centroid updated: [[17.   12.  ] [ 4.6   4.2 ] [11.83 15.67]]
<2021-01-02 19:56:46 INFO>: [EPOCH 0] Current SSE: 7.232632038258262; Centroid offset: 4.2354325503883175
<2021-01-02 19:56:46 INFO>: [EPOCH 1] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:46 INFO>: [EPOCH 1] Current SSE: 7.232632038258262; Centroid offset: 0.0
<2021-01-02 19:56:46 INFO>: Centroid coordinates: [[17.   12.  ] [ 4.6   4.2 ] [11.83 15.67]]
<2021-01-02 19:56:46 INFO>: K-Means started. K = 4, MAX_EPOCHS = 10
<2021-01-02 19:56:47 INFO>: [EPOCH 0] Centroid updated: [[13.18 13.73] [ 4.    5.  ] [ 3.75  1.75] [ 6.5   5.5 ]]
<2021-01-02 19:56:47 INFO>: [EPOCH 0] Current SSE: 6.5849737413632425; Centroid offset: 8.974999712240148
<2021-01-02 19:56:47 INFO>: [EPOCH 1] Centroid updated: [[13.9  14.2 ] [ 3.    5.5 ] [ 3.75  1.75] [ 6.25  6.  ]]
<2021-01-02 19:56:47 INFO>: [EPOCH 1] Current SSE: 5.93599494586555; Centroid offset: 1.5171539797749958
<2021-01-02 19:56:48 INFO>: [EPOCH 2] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:48 INFO>: [EPOCH 2] Current SSE: 5.93599494586555; Centroid offset: 0.0
<2021-01-02 19:56:48 INFO>: Centroid coordinates: [[13.9  14.2 ] [ 3.    5.5 ] [ 3.75  1.75] [ 6.25  6.  ]]
<2021-01-02 19:56:48 INFO>: K-Means started. K = 5, MAX_EPOCHS = 10
<2021-01-02 19:56:48 INFO>: [EPOCH 0] Centroid updated: [[16.6  13.4 ] [10.   12.5 ] [ 6.    5.33] [12.   16.67] [ 2.5   2.5 ]]
<2021-01-02 19:56:48 INFO>: [EPOCH 0] Current SSE: 4.53122887111425; Centroid offset: 3.8503968049482324
<2021-01-02 19:56:49 INFO>: [EPOCH 1] Centroid updated: [[17.   12.  ] [10.   12.5 ] [ 6.    5.33] [12.75 17.25] [ 2.5   2.5 ]]
<2021-01-02 19:56:49 INFO>: [EPOCH 1] Current SSE: 4.023086665782328; Centroid offset: 1.7386137517510254
<2021-01-02 19:56:49 INFO>: [EPOCH 2] Centroid updated: [[17.   12.  ] [10.33 13.33] [ 6.    5.33] [13.33 18.  ] [ 2.5   2.5 ]]
<2021-01-02 19:56:49 INFO>: [EPOCH 2] Current SSE: 3.9356681049237885; Centroid offset: 1.3070322617798442
<2021-01-02 19:56:49 INFO>: [EPOCH 3] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:49 INFO>: [EPOCH 3] Current SSE: 3.9356681049237885; Centroid offset: 0.0
<2021-01-02 19:56:49 INFO>: Centroid coordinates: [[17.   12.  ] [10.33 13.33] [ 6.    5.33] [13.33 18.  ] [ 2.5   2.5 ]]
```

## 随机数据

使用大量生成的随机数据可以更好地展示聚类效果。例如，随机生成主要集中在左下角的 300 个点并再次分别使用 K = 2 - 5 聚类，得到如下结果：

![2021-01-02-N6E2Y6](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-N6E2Y6.jpg)
![2021-01-02-Ndn6Ww](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-Ndn6Ww.jpg)
![2021-01-02-zS0WAB](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-zS0WAB.jpg)
![2021-01-02-3e04ub](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-3e04ub.jpg)

其中 SSE 和 K 之间存在类似的关系：

![image-20210102200823889](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-02-r5QfI4.png)

主要日志如下：

```
<2021-01-02 19:53:59 INFO>: K-Means started. K = 2, MAX_EPOCHS = 10
<2021-01-02 19:54:00 INFO>: [EPOCH 0] Centroid updated: [[16.6 13.4] [ 6.8  7.8]]
<2021-01-02 19:54:00 INFO>: [EPOCH 0] Current SSE: 16.695507816124437; Centroid offset: 8.366600265340756
<2021-01-02 19:54:00 INFO>: [EPOCH 1] Centroid updated: [[14.33 14.56] [ 5.09  4.82]]
<2021-01-02 19:54:00 INFO>: [EPOCH 1] Current SSE: 12.57577169192891; Centroid offset: 4.276133513433808
<2021-01-02 19:54:00 INFO>: [EPOCH 2] Centroid updated: [[13.9 14.2] [ 4.6  4.2]]
<2021-01-02 19:54:00 INFO>: [EPOCH 2] Current SSE: 11.654674875992491; Centroid offset: 0.9681621903028267
<2021-01-02 19:54:01 INFO>: [EPOCH 3] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:54:01 INFO>: [EPOCH 3] Current SSE: 11.654674875992491; Centroid offset: 0.0
<2021-01-02 19:54:01 INFO>: Centroid coordinates: [[13.9 14.2] [ 4.6  4.2]]
<2021-01-02 19:56:29 INFO>: K-Means started. K = 2, MAX_EPOCHS = 10
<2021-01-02 19:56:30 INFO>: [EPOCH 0] Centroid updated: [[13.9 14.2] [ 4.6  4.2]]
<2021-01-02 19:56:30 INFO>: [EPOCH 0] Current SSE: 11.654674875992491; Centroid offset: 5.123475382979798
<2021-01-02 19:56:30 INFO>: [EPOCH 1] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:30 INFO>: [EPOCH 1] Current SSE: 11.654674875992491; Centroid offset: 0.0
<2021-01-02 19:56:30 INFO>: Centroid coordinates: [[13.9 14.2] [ 4.6  4.2]]
<2021-01-02 19:56:45 INFO>: K-Means started. K = 2, MAX_EPOCHS = 10
<2021-01-02 19:56:45 INFO>: [EPOCH 0] Centroid updated: [[ 4.6  4.2] [13.9 14.2]]
<2021-01-02 19:56:45 INFO>: [EPOCH 0] Current SSE: 11.654674875992491; Centroid offset: 4.695742752749558
<2021-01-02 19:56:46 INFO>: [EPOCH 1] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:46 INFO>: [EPOCH 1] Current SSE: 11.654674875992491; Centroid offset: 0.0
<2021-01-02 19:56:46 INFO>: Centroid coordinates: [[ 4.6  4.2] [13.9 14.2]]
<2021-01-02 19:56:46 INFO>: K-Means started. K = 3, MAX_EPOCHS = 10
<2021-01-02 19:56:46 INFO>: [EPOCH 0] Centroid updated: [[17.   12.  ] [ 4.6   4.2 ] [11.83 15.67]]
<2021-01-02 19:56:46 INFO>: [EPOCH 0] Current SSE: 7.232632038258262; Centroid offset: 4.2354325503883175
<2021-01-02 19:56:46 INFO>: [EPOCH 1] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:46 INFO>: [EPOCH 1] Current SSE: 7.232632038258262; Centroid offset: 0.0
<2021-01-02 19:56:46 INFO>: Centroid coordinates: [[17.   12.  ] [ 4.6   4.2 ] [11.83 15.67]]
<2021-01-02 19:56:46 INFO>: K-Means started. K = 4, MAX_EPOCHS = 10
<2021-01-02 19:56:47 INFO>: [EPOCH 0] Centroid updated: [[13.18 13.73] [ 4.    5.  ] [ 3.75  1.75] [ 6.5   5.5 ]]
<2021-01-02 19:56:47 INFO>: [EPOCH 0] Current SSE: 6.5849737413632425; Centroid offset: 8.974999712240148
<2021-01-02 19:56:47 INFO>: [EPOCH 1] Centroid updated: [[13.9  14.2 ] [ 3.    5.5 ] [ 3.75  1.75] [ 6.25  6.  ]]
<2021-01-02 19:56:47 INFO>: [EPOCH 1] Current SSE: 5.93599494586555; Centroid offset: 1.5171539797749958
<2021-01-02 19:56:48 INFO>: [EPOCH 2] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:48 INFO>: [EPOCH 2] Current SSE: 5.93599494586555; Centroid offset: 0.0
<2021-01-02 19:56:48 INFO>: Centroid coordinates: [[13.9  14.2 ] [ 3.    5.5 ] [ 3.75  1.75] [ 6.25  6.  ]]
<2021-01-02 19:56:48 INFO>: K-Means started. K = 5, MAX_EPOCHS = 10
<2021-01-02 19:56:48 INFO>: [EPOCH 0] Centroid updated: [[16.6  13.4 ] [10.   12.5 ] [ 6.    5.33] [12.   16.67] [ 2.5   2.5 ]]
<2021-01-02 19:56:48 INFO>: [EPOCH 0] Current SSE: 4.53122887111425; Centroid offset: 3.8503968049482324
<2021-01-02 19:56:49 INFO>: [EPOCH 1] Centroid updated: [[17.   12.  ] [10.   12.5 ] [ 6.    5.33] [12.75 17.25] [ 2.5   2.5 ]]
<2021-01-02 19:56:49 INFO>: [EPOCH 1] Current SSE: 4.023086665782328; Centroid offset: 1.7386137517510254
<2021-01-02 19:56:49 INFO>: [EPOCH 2] Centroid updated: [[17.   12.  ] [10.33 13.33] [ 6.    5.33] [13.33 18.  ] [ 2.5   2.5 ]]
<2021-01-02 19:56:49 INFO>: [EPOCH 2] Current SSE: 3.9356681049237885; Centroid offset: 1.3070322617798442
<2021-01-02 19:56:49 INFO>: [EPOCH 3] Centroids are almost stable. Iterating stopped.
<2021-01-02 19:56:49 INFO>: [EPOCH 3] Current SSE: 3.9356681049237885; Centroid offset: 0.0
<2021-01-02 19:56:49 INFO>: Centroid coordinates: [[17.   12.  ] [10.33 13.33] [ 6.    5.33] [13.33 18.  ] [ 2.5   2.5 ]]
<2021-01-02 20:00:27 INFO>: K-Means started. K = 2, MAX_EPOCHS = 10
<2021-01-02 20:00:28 INFO>: [EPOCH 0] Centroid updated: [[1.35 1.7 ] [0.8  0.48]]
<2021-01-02 20:00:28 INFO>: [EPOCH 0] Current SSE: 9.084632833500144; Centroid offset: 1.0783800944922404
<2021-01-02 20:00:28 INFO>: [EPOCH 1] Centroid updated: [[1.44 1.7 ] [0.75 0.5 ]]
<2021-01-02 20:00:28 INFO>: [EPOCH 1] Current SSE: 8.946377149429686; Centroid offset: 0.1007166547161402
<2021-01-02 20:00:28 INFO>: [EPOCH 2] Centroid updated: [[1.48 1.66] [0.72 0.51]]
<2021-01-02 20:00:28 INFO>: [EPOCH 2] Current SSE: 8.884159078981497; Centroid offset: 0.07103114142885013
<2021-01-02 20:00:29 INFO>: [EPOCH 3] Centroids are almost stable. Iterating stopped.
<2021-01-02 20:00:29 INFO>: [EPOCH 3] Current SSE: 8.836643983084578; Centroid offset: 0.043257381258992034
<2021-01-02 20:00:29 INFO>: Centroid coordinates: [[1.48 1.66] [0.72 0.51]]
<2021-01-02 20:00:29 INFO>: K-Means started. K = 3, MAX_EPOCHS = 10
<2021-01-02 20:00:29 INFO>: [EPOCH 0] Centroid updated: [[1.09 0.27] [1.36 1.38] [0.26 0.89]]
<2021-01-02 20:00:29 INFO>: [EPOCH 0] Current SSE: 7.24164583345518; Centroid offset: 0.7790249329727592
<2021-01-02 20:00:30 INFO>: [EPOCH 1] Centroid updated: [[1.06 0.33] [1.52 1.64] [0.36 0.76]]
<2021-01-02 20:00:30 INFO>: [EPOCH 1] Current SSE: 6.352441733742936; Centroid offset: 0.3493782817722399
<2021-01-02 20:00:30 INFO>: [EPOCH 2] Centroid updated: [[1.16 0.36] [1.51 1.71] [0.39 0.71]]
<2021-01-02 20:00:30 INFO>: [EPOCH 2] Current SSE: 6.296660431436018; Centroid offset: 0.1406256889944029
<2021-01-02 20:00:30 INFO>: [EPOCH 3] Centroid updated: [[1.28 0.39] [1.47 1.76] [0.41 0.66]]
<2021-01-02 20:00:30 INFO>: [EPOCH 3] Current SSE: 6.223448294655537; Centroid offset: 0.14565255864462445
<2021-01-02 20:00:31 INFO>: [EPOCH 4] Centroid updated: [[1.35 0.41] [1.44 1.78] [0.42 0.64]]
<2021-01-02 20:00:31 INFO>: [EPOCH 4] Current SSE: 6.232771335317366; Centroid offset: 0.08361889313321569
<2021-01-02 20:00:31 INFO>: [EPOCH 5] Centroid updated: [[1.41 0.46] [1.43 1.81] [0.44 0.62]]
<2021-01-02 20:00:31 INFO>: [EPOCH 5] Current SSE: 6.231241594598399; Centroid offset: 0.09348551773401224
<2021-01-02 20:00:31 INFO>: [EPOCH 6] Centroid updated: [[1.48 0.48] [1.4  1.83] [0.48 0.59]]
<2021-01-02 20:00:31 INFO>: [EPOCH 6] Current SSE: 6.158039505450404; Centroid offset: 0.09843152231474
<2021-01-02 20:00:32 INFO>: [EPOCH 7] Centroid updated: [[1.65 0.57] [1.34 1.86] [0.52 0.55]]
<2021-01-02 20:00:32 INFO>: [EPOCH 7] Current SSE: 6.062791253276619; Centroid offset: 0.20894904002053158
<2021-01-02 20:00:32 INFO>: [EPOCH 8] Centroid updated: [[1.76 0.67] [1.29 1.9 ] [0.54 0.53]]
<2021-01-02 20:00:32 INFO>: [EPOCH 8] Current SSE: 5.970752114170463; Centroid offset: 0.1622267864028703
<2021-01-02 20:00:33 INFO>: [EPOCH 9] Centroid updated: [[1.79 0.72] [1.27 1.92] [0.55 0.53]]
<2021-01-02 20:00:33 INFO>: [EPOCH 9] Current SSE: 5.957964970912589; Centroid offset: 0.07071241626807692
<2021-01-02 20:00:33 INFO>: Centroid coordinates: [[1.79 0.72] [1.27 1.92] [0.55 0.53]]
<2021-01-02 20:00:33 INFO>: K-Means started. K = 4, MAX_EPOCHS = 10
<2021-01-02 20:00:33 INFO>: [EPOCH 0] Centroid updated: [[1.28 1.66] [1.35 0.68] [0.22 0.77] [0.87 0.22]]
<2021-01-02 20:00:33 INFO>: [EPOCH 0] Current SSE: 5.450719950948322; Centroid offset: 1.1258711743598417
<2021-01-02 20:00:33 INFO>: [EPOCH 1] Centroid updated: [[1.37 1.86] [1.62 0.69] [0.31 0.75] [0.75 0.26]]
<2021-01-02 20:00:33 INFO>: [EPOCH 1] Current SSE: 4.72262510112004; Centroid offset: 0.39057378065049275
<2021-01-02 20:00:34 INFO>: [EPOCH 2] Centroid updated: [[1.34 1.92] [1.81 0.72] [0.37 0.81] [0.74 0.3 ]]
<2021-01-02 20:00:34 INFO>: [EPOCH 2] Current SSE: 4.653745415605375; Centroid offset: 0.22042674272586063
<2021-01-02 20:00:34 INFO>: [EPOCH 3] Centroid updated: [[1.32 1.93] [1.86 0.76] [0.37 0.84] [0.74 0.31]]
<2021-01-02 20:00:34 INFO>: [EPOCH 3] Current SSE: 4.66324215468795; Centroid offset: 0.07678847887676
<2021-01-02 20:00:35 INFO>: [EPOCH 4] Centroid updated: [[1.29 1.94] [1.9  0.81] [0.39 0.86] [0.73 0.31]]
<2021-01-02 20:00:35 INFO>: [EPOCH 4] Current SSE: 4.684047289306287; Centroid offset: 0.07242621504329899
<2021-01-02 20:00:35 INFO>: [EPOCH 5] Centroid updated: [[1.26 1.96] [1.92 0.85] [0.41 0.87] [0.73 0.31]]
<2021-01-02 20:00:35 INFO>: [EPOCH 5] Current SSE: 4.702882296202382; Centroid offset: 0.05958200898169935
<2021-01-02 20:00:35 INFO>: [EPOCH 6] Centroids are almost stable. Iterating stopped.
<2021-01-02 20:00:35 INFO>: [EPOCH 6] Current SSE: 4.7118083155550705; Centroid offset: 0.04844511252831861
<2021-01-02 20:00:35 INFO>: Centroid coordinates: [[1.26 1.96] [1.92 0.85] [0.41 0.87] [0.73 0.31]]
<2021-01-02 20:00:35 INFO>: K-Means started. K = 5, MAX_EPOCHS = 10
<2021-01-02 20:00:36 INFO>: [EPOCH 0] Centroid updated: [[0.97 0.72] [0.31 1.98] [1.36 1.92] [2.02 0.8 ] [0.42 0.41]]
<2021-01-02 20:00:36 INFO>: [EPOCH 0] Current SSE: 3.8977596033449764; Centroid offset: 0.5643413862150298
<2021-01-02 20:00:36 INFO>: [EPOCH 1] Centroid updated: [[0.99 0.7 ] [0.47 1.98] [1.57 1.89] [2.06 0.81] [0.43 0.41]]
<2021-01-02 20:00:36 INFO>: [EPOCH 1] Current SSE: 3.7565910073650803; Centroid offset: 0.2697654559890776
<2021-01-02 20:00:37 INFO>: [EPOCH 2] Centroid updated: [[1.   0.7 ] [0.58 2.  ] [1.75 1.84] [2.06 0.74] [0.42 0.41]]
<2021-01-02 20:00:37 INFO>: [EPOCH 2] Current SSE: 3.6897836128881876; Centroid offset: 0.22950402065172437
<2021-01-02 20:00:37 INFO>: [EPOCH 3] Centroid updated: [[1.   0.7 ] [0.66 1.99] [1.85 1.81] [2.08 0.69] [0.42 0.42]]
<2021-01-02 20:00:37 INFO>: [EPOCH 3] Current SSE: 3.656776268252373; Centroid offset: 0.14171336542501425
<2021-01-02 20:00:38 INFO>: [EPOCH 4] Centroids are almost stable. Iterating stopped.
<2021-01-02 20:00:38 INFO>: [EPOCH 4] Current SSE: 3.654811106661147; Centroid offset: 0.03564353575472734
<2021-01-02 20:00:38 INFO>: Centroid coordinates: [[1.   0.7 ] [0.66 1.99] [1.85 1.81] [2.08 0.69] [0.42 0.42]]
```