## Database Lab 5: Index

> 10185101210 陈俊潼

### 配置信息

| 项                   | 值                                       |
| -------------------- | ---------------------------------------- |
| 系统版本             | macOS 10.5.4                             |
| MySQL 版本           | 8.0.19                                   |
| 计算机内存           | 16 GB                                    |
| 计算机处理器         | Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz |
| SSD 读取速度（单测） | 2.25 GB / s                              |


### 建立数据

首先使用下列语句新建表：

```sql
CREATE TABLE personHealthInfo (
  pNo varchar(18) NOT NULL,
  pName varchar(20),
  location varchar(20),
  healthStatus varchar(20)) 
```

接着新建运行过程：

```mysql
CREATE PROCEDURE generateData(num int)
BEGIN
	declare pno varchar(18);
	declare pname varchar(20);
	declare location varchar(20);
	declare healthStatus varchar(20);
	declare counter   bigint;
	declare location_set varchar(200);
	declare health_set varchar(200);
	set location_set = 'Shanghai,Beijing,Guangzhou';
	set health_set = 'Health,Uncertain,Diagnosis,Cure';
	set counter=1;
	while counter<num do
		set pno=ltrim(cast(floor(rand(counter)*1000000000) as char));
		set pname=concat('p',pno);
		set location= substring_index(substring_index(location_set, ',', floor(1 + (rand() * 3))),',',-1);
		set healthStatus = substring_index(substring_index(health_set, ',', floor(1 + (rand() * 4))),',',-1);
		insert into personHealthInfo(pNo,pName,location, healthStatus)  values(pno,pname,location, healthStatus);
		set counter=counter+1;
	end while;
END;
```

然后调用该过程可以创建不同数量的数据。尝试运行：

```mysql
CALL generateData(1000000)
```

可以看到，创建 1000000 条数据花费的时间为 316.96 秒。

![image-20200528103516926](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-28-sr4eVp.png)



### 查询结果

通过查阅 MySQL 的官方文档：![image-20200528112845423](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-28-752CzZ.png)



在 MySQL 中无法使用 `CREATE [UNIQUE] [CLUSTERED | NONCLUSTERED] INDEX index_name ON table_name(column_name)` 的方式直接显式指定创建聚簇索引索引或者费聚簇索引索引。而是在定义了一个主键后，MySQL 会自动把这个主键作为聚簇索引。所以在接下来的实验中，将先不建立索引进行查询语句统计时间，再为 `pNo` 建立一个主键，进行余下的操作。

值得一提的是，在未建立主键之前，MySQL 会自动查询到第一个 `UNIQUE` 的索引，并基于索引列建立聚簇索引，因此在建立非聚簇索引的时候，我将不会指定 `UNIQUE` 字段。

于是编写 SQL 脚本如下：

```mysql
DELETE FROM personHealthInfo;
CALL generateData(5000);

-- No index, equivelent
SELECT * FROM personHealthInfo WHERE pNo = 406135974;
-- No index, range
SELECT * FROM personHealthInfo WHERE pNo < 406135974;

CREATE INDEX index1 ON personHealthInfo(pNo);
-- Non-cluster index on pNo, equivalent
SELECT * FROM personHealthInfo WHERE pNo = 406135974;
-- Non-cluster index on pNo, range
SELECT * FROM personHealthInfo WHERE pNo < 406135974;
DROP INDEX index1 on personHealthInfo;

ALTER TABLE personHealthInfo ADD PRIMARY KEY (pNo);
-- Cluster index on pNo, equivalent
SELECT * FROM personHealthInfo WHERE pNo = 406135974;
-- Cluster index on pNo, range
SELECT * FROM personHealthInfo WHERE pNo < 406135974;

CREATE INDEX index1 ON personHealthInfo(location);
-- Cluster on pNo & Non-cluster on location
SELECT * FROM personHealthInfo WHERE location = 'Shanghai';
DROP INDEX index1 on personHealthInfo;

CREATE INDEX index1 ON personHealthInfo(healthStatus);
-- Cluster on pNo & Non-cluster on health
SELECT healthStatus, count(*) FROM personHealthInfo WHERE location = 'Shanghai' GROUP BY healthStatus;
DROP INDEX index1 on personHealthInfo;

ALTER TABLE personHealthInfo DROP PRIMARY KEY;
```

例如，使用 5000 条数据可以得到来自 Navicat 的一下 Message，得到对应语句的执行时间：

![image-20200528123038004](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-28-nWEiA4.png)

于是分别以 5,000 条，10,000 条，100,000 条， 1,000,000 条数据进行三次实验，可以得到以下结果，单位均为秒：

| Subject (Time unit: seconds)             | 5000  | 10,000 | 100,000 | 1,000,000 |
| ---------------------------------------- | ----- | ------ | ------- | --------- |
| Generating data                          | 1.908 | 3.635  | 4.168   | 309.184   |
| No index, equivalent                     | 0.001 | 0.003  | 0.03    | 0.293     |
| No index, range                          | 0.002 | 0.003  | 0.071   | 0.366     |
| Non-cluster index on pNo, equivalent     | 0.001 | 0.001  | 0.001   | 0.000     |
| Non-luster index on pNo, range           | 0.002 | 0.005  | 0.040   | 0.360     |
| Cluster index on pNo, equivalent         | 0.000 | 0.000  | 0.000   | 0.000     |
| Cluster index on pNo, range              | 0.001 | 0.003  | 0.033   | 0.028     |
| Cluster on pNo & Non-cluster on location | 0.002 | 0.004  | 0.048   | 1.515     |
| Cluster on pNo & Non-cluster on health   | 0.003 | 0.007  | 0.082   | 1.711     |

对结果作图表如下（纵轴为指数坐标轴）：

![chart](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-28-EExwjZ.png)

以上结果全部通过在 LOCALHOST 上运行的 MySQL 服务器得到，避免了网络传输的不稳定性对结果造成的影响。

可以看见，在建立了非聚簇索引之后，等值搜索的速度立即下降到接近于 0。而对于范围搜索，在中型和大型的数据量下，还是可以看见有轻微的下降结果。

进一步地，对 `pNo` 建立聚簇索引之后，可以发现范围搜索的速度相比非聚类的速度又下降了许多，100 万条数据的情况下从 0.36 秒下降到来了 0.028 秒。

而对于最后两条二级索引，经过试验，第一次查询会经过较长时间（如图、表所示），用时 1.5 秒。不过由于数据库的缓存机制，在第二次查询的时候，速度就可以提升到 0.026 秒左右。为了对比该查询不经过索引的查询时间，我重新运行了一次语句，但只对 `pNO` 建立聚簇索引而不对 `healthStatus` 或 `location` 建立索引。可以得到最后两条语句的查询时间分别为：

![image-20200528135350311](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-28-mIjw85.png)

发现运行时间反倒比之前的更短了。经过探索，我认为原因在于如果对 `healthStatus` 或 `location` 建立了非聚簇索引，那么数据库在查询到涉及这两个字段的查询时就会从非聚簇索引中查找到所有满足条件的子节点。然而，非聚簇索引的子节点在磁盘中并不是顺序存储的，大量的随机访问会产生很多不必要的磁盘读取时间。相应的，如果不对 `healthStatus` 或 `location` 建立非聚簇索引，那么数据库会从 `pNo` 的聚簇索引依次遍历并判断是否满足查询要求。由于聚簇索引是顺序读取，磁盘的读取速度将会大大提高，从而得到更快的查询速度。

### 更多思考

#### 索引创建的规则

1. MySQL 默认会为第一个 `UNIQUE` 的非空索引栏创建聚簇索引。
2. 通常对于数据量较大的情况，创建一个用于查找的索引是必须的。这样可以有效地减少查找时间，提高查找效率。
3. 如果已经有了一个聚簇索引，要谨慎地选择第二索引。除非对第二索引的查询需求非常大，否则不推荐在数据库中建立第二索引，这样有可能反而会降低查询性能。

#### 自增主键上的聚簇索引

这样的聚簇索引是有意义的。聚簇索引决定了数据项在存盘中的存储顺序。对自增主键进行聚簇索引，意味着一系列的主键将会是序列存储的，这对查询和更新操作都非常有利，可以使用二分查找等高效率的方式维护数据。

#### 连续操作的性能要求

在创建一百万条数据时，计算机甚至会出现假死的情况。检查系统运行情况：

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-28-RcFmjB.png" alt="image-20200528140432780" style="zoom: 50%;" />

除了发现 CPU 温度急剧上升外，也能看到 MySQL 占用了大量 CPU 资源并不断写入磁盘和读取磁盘数据。

---

实验统计数据及图表源文件：

[https://billc.oss-cn-shanghai.aliyuncs.com/file/2020-05-28-LAB5.xlsx](https://billc.oss-cn-shanghai.aliyuncs.com/file/2020-05-28-LAB5.xlsx)

