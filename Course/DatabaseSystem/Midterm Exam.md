## Database System Midterm Exam ^2020.5^

> 10185101210 陈俊潼

![image-20200507101455752](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-07-image-20200507101455752.png)

### Part I:

AABAB ABBAC AAAAD

### Part II

#### Question 1.

$$
\begin{align*}
1.\ &\sigma_{price\ge100\and price\le200}(toy)\\
2.\ &\sigma_{price>10}(part)\\
3.\ &\Pi_{tid,tname,toy.price}(\sigma_{pname='engine'}(toy\bowtie part\bowtie toypart))\\
4.\ &toy\leftarrow \Big(\Pi_{tid,tname,40}(\sigma_{tname='hello-kitty'}(toy)) \cup \sigma_{tname\ne'hello-kitty'}(toy)\Big) \\
5.\ &\Pi_{pname}\Big(\sigma_{tname='hello-kitty'}(toy\bowtie part\bowtie toypart))\Big)
\end{align*}
$$

#### Question 2.

```sql
SELECT price FROM toy WHERE tname='hello-kitty';
CREATE VIEW alltoys AS (SELECT tid, tname FROM toy);
SELECT * FROM toy WHERE tname LIKE '%tiger%';
INSERT INTO toy (tid, tname, price) VALUES ('t006', 'jump-tiger', 150);
SELECT tid, SUM(amount) FROM toypart GROUP BY tid;
```

### Part III

The ER-diagram is drawn as follows:

![erd](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-07-erd-Is08xn.png)

From the ER-diagram, we can design the relational scheme is as follows:
cast(<u>cast_id</u>, name, address)

cast_series(==<u>cast_id</u>==, ==<u>series_id</u>==)

series(<u>series_id</u>, name, description)

episode(<u>episode_id</u>, eposide_number, first_aired_year, first_aired_date, length, ==series_id==)

user(<u>uid</u>, username, password)

comment(==<u>uid</u>==, ==<u>episode_id</u>==, content, date)

*Ps. The primary key is denoted underline, and the foreign keys are denoted highlighted.*

### Part IV

#### Question 1.

By computing attribute closure for all attributes, we get:
$$
A^+ = AB\\
B^+ = B\\
C^+ = CD\\
D^+ = D\\
$$
So the candidate key is AC.

#### Question 2.

$$
\text{Since we have }A\rightarrow D, AE^+ = AE\cup D\\
\because E\rightarrow C, \Rightarrow AE^+ = AED\cup C\\
\because CD\rightarrow I, \Rightarrow AE^+ = ACED\cup I\\
\therefore AE^+ = ACDEI
$$

#### Question 3.

- R is not BCNF. Because by computing $C^+ = CTDI$ doesn’t include all attributes in relation R, so C is not a super key, since R is not BCNF.
- The decomposed relation is as follows:
  - R~1~ = {C, T, D, I}
  - R~2~ = {B, R, P}
  - R~3~ = {C, E, S, Y, B, R, O}