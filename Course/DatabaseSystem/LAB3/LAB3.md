1. List all information stored in the table course;

   ```sql
   SELECT * FROM course;
   ```

2. List the dept_name and buildings of all departments;

   ```sql
   SELECT dept_name, building FROM department;
   ```

3. List the instructor's name appears in the table instructor;

   ```sql
   SELECT name FROM instructor;
   ```

4. List the instructor's name whose salary is more than 90000 and dept_name is 'Comp Sci' ;

   ```sql
   SELECT name FROM instructor WHERE dept_name = 'Comp. Sci.' AND salary > 90000;
   ```

5. List the instructor's all information after we gave a 10% raise to each instructor;

   ```sql
   SELECT *, salary*1.1 as raised_salary FROM instructor;
   ```

6. Show the different dept_name in the table instructor;

   ```sql
   SELECT DISTINCT dept_name FROM instructor;
   ```

7. List the course's title ,dept_name,and credits which prerep_id is 'CS-101';

   ```sql
   SELECT title, dept_name, credits FROM course NATURAL JOIN prereq WHERE prereq_id='CS-101';
   ```

8. Find the titles of courses in the Comp Sci department the have 3 credits;

   ```sql
   SELECT title FROM course WHERE credits=3;
   ```

9. List the course_id which prereq_id is 'CS-101';

   ```sql
   SELECT course_id FROM course NATURAL JOIN prereq WHERE prereq_id='CS-101';
   ```

10. Find all courses that were offered at least twice in 2010(not unique);

   ```sql
   SELECT course_id FROM (SELECT course_id, COUNT(course_id) AS c FROM section WHERE `year`=2010 GROUP BY course_id) AS T WHERE c > 1;
   ```

11. Find the instructor names and the courses they taught for all instructors in the Biology department who have taught some course;

    ```sql
    SELECT `name`, course_id FROM instructor NATURAL JOIN teaches WHERE dept_name='Biology';
    ```

12. List all courses taught in Fall 2009;

    ```sql
    SELECT * FROM course NATURAL JOIN section WHERE semester='Fall' AND `year`=2009;
    ```

13. Find the set of all courses taught either in Fall 2010 or in Spring 2009,or both we write.

    ```sql
    SELECT * FROM course NATURAL JOIN section WHERE (semester='Fall' AND `year`=2010) OR (semester='Spring' AND `year`=2009);
    ```

14. Find all courses taught in the Fall 2009 but not in the Spring 2010;

    ```sql
    SELECT * FROM section WHERE (semester='Fall' AND `year`=2009) AND course_id NOT IN (SELECT course_id FROM section WHERE (semester='Spring' AND `year`=2010));
    ```

15. Find the average salary of instructors in the Comp Sci department;

    ```sql
    SELECT avg(salary) FROM instructor WHERE dept_name='Comp. Sci.'
    ```

16. Find the total number of instructors who teach a course in the Spring 2010 semester;

    ```sql
    SELECT count(*) FROM instructor NATURAL JOIN teaches WHERE `year`=2010 AND semester='Spring';
    ```

17. Find the number of tuples in the course relation;

    ```sql
    SELECT count(*) FROM course;
    ```

18. Find the average salary in each department;

    ```sl
    SELECT dept_name, FORMAT(AVG(salary),2) AS avg_salary FROM instructor GROUP BY dept_name;
    ```

19. Find the average salary of instructors in those departments where the average salary is more than 42000;

    ```sql
    SELECT dept_name, AVG(salary) AS avg_salary FROM instructor GROUP BY dept_name HAVING AVG(salary) > 42000;
    ```

20. Find the names of all instructors whose salary is greater than at least one instructor in the Com Sic department.

    ```sql
    SELECT * FROM instructor WHERE salary> (SELECT min(salary) FROM instructor WHERE dept_name='Comp. Sci.');
    ```

**1.**   **Modification of DB**

- Delete all the instroctors with a salary more than 90000;

  ```sql
  DELETE FROM instructor WHERE salary>90000;
  ```

- Adjust the budget of the Comp Sci to 120000;

  ```sql
  UPDATE department SET budget=120000 WHERE dept_name='Comp. Sci.';
  ```

- Salary are increased by 10 percent only the instructors with salary of less than 70000 (not including 70000),and others increased by 5 percent;

  ```sql
  UPDATE instructor SET salary=1.1salary WHERE salary<70000;
  UPDATE instructor SET salary=1.05*salary WHERE salary>=70000;
  ```

**2.**   **View Operation** 

- Create a view named instructor_info with lists the ID,name,and building-name of each instructor.

  ```sql
  CREATE VIEW instructor_info AS (SELECT ID, `name`, building FROM instructor NATURAL JOIN department);
  ```

- Find all the instructors whose building name is 'Taylor' by the view you created above.

  ```sql
  SELECT name FROM instructor_info WHERE building='Taylor';
  ```

- Try to find the ‘View update policy’ in SQL Server:2

  SQLServer views are not cached, so everytime the user request a view the query is executed.

  ![image-20200416145807889](https://tva1.sinaimg.cn/large/007S8ZIlgy1gdvm7tewnuj30n40pe7bw.jpg)

首先创建两个 `View` 整合数据：

```sql
CREATE view giveout AS (SELECT *, '2020-02-14' as date FROM giveout214 UNION SELECT *,'2020-02-13' as date   FROM giveout213);
CREATE view donation AS (SELECT *, '2020-02-14' as date FROM donation214 UNION SELECT *,'2020-02-13' as date  FROM donation213);
```

1.查找蔡甸区卫生健康局接受的捐赠情况 

```sql
SELECT * FROM (SELECT * FROM giveout214 UNION SELECT * FROM giveout213) AS T WHERE T.target='蔡甸区卫生健康局';
```

![image-20200416151515538](https://i.loli.net/2020/04/16/857CLQpwVHnuRor.png)

2.查找浏阳市华盛山庄的捐赠情况

```sql
SELECT * FROM donation WHERE provider='浏阳市华盛山庄';
```

![image-20200416151536339](https://i.loli.net/2020/04/16/CnWTcbFfrSdAsOe.png)

3.查找2.13到2.14医用口罩捐赠给了哪些单位 

```sql
SELECT DISTINCT target FROM giveout;
```

（结果过长有省略）

![image-20200416151637608](https://i.loli.net/2020/04/16/eXJdGvNj7HWYqn5.png)

4.查询2.13到2.14社会捐赠的医用口罩的数目

```sql
SELECT count(*) FROM donation WHERE asset LIKE "%口罩%";
```

![image-20200416151801059](https://i.loli.net/2020/04/16/VpIc3Co8hadUOtL.png)

5.查询2.13到2.14发放的一次性手套大、中、小号各多少只

```sql
SELECT 'L' AS spec, count(*)  FROM giveout WHERE asset LIKE "%手套%" AND (spec LIKE '%大号%' OR spec LIKE '%L%') UNION
SELECT 'M' AS spec, count(*)  FROM giveout WHERE asset LIKE "%手套%" AND (spec LIKE '%中号%' OR spec LIKE '%M%') UNION
SELECT 'S' AS spec, count(*)  FROM giveout WHERE asset LIKE "%手套%" AND (spec LIKE '%小号%' OR spec LIKE '%S%');SELECT 'L' AS spec, count(*)  FROM giveout WHERE asset LIKE "%手套%" AND (spec LIKE '%大号%' OR spec LIKE '%L%') UNION
SELECT 'M' AS spec, count(*)  FROM giveout WHERE asset LIKE "%手套%" AND (spec LIKE '%中号%' OR spec LIKE '%M%') UNION
SELECT 'S' AS spec, count(*)  FROM giveout WHERE asset LIKE "%手套%" AND (spec LIKE '%小号%' OR spec LIKE '%S%');
```

![image-20200416152538705](https://i.loli.net/2020/04/16/rwSkJ6QHXlxFcd2.png)

6.查询2.14接受了医用N95口罩捐赠的单位有哪几家，各获得多少只

```sql
SELECT target, sum(amount) FROM giveout214 WHERE asset LIKE '%N95%' GROUP BY target;
```

![image-20200416152931487](https://i.loli.net/2020/04/16/xcqW4K6aiYodCIm.png)

7.查找获得物资数量超过2000计量单位的单位有哪几家

```sql
SELECT target, sum(amount) FROM giveout GROUP BY target HAVING sum(amount) > 2000;
```

![image-20200416153220411](https://i.loli.net/2020/04/16/ZBgHot5ayDcXfeq.png)

8.统计2.13到2.14两天平均每天发放了多少数量口罩

```sql
SELECT sum(amount) / 2 FROM giveout;
```

![image-20200416153503565](https://i.loli.net/2020/04/16/TZso4jXc9W3Udkn.png)

9.统计2.13到2.14一共发放的防护服的数量

```sql
SELECT sum(amount) FROM giveout WHERE asset LIKE '%防护服%';
```

![image-20200416153535429](https://i.loli.net/2020/04/16/tVETfB9gYesqd7U.png)

10.查询获得物资感冒清热颗粒的单位有哪几家，数量分别是多少

```sql
SELECT target, sum(amount) FROM giveout WHERE asset LIKE '%感冒清热颗粒%' GROUP BY target;
```

![image-20200416153622024](https://i.loli.net/2020/04/16/DRwfq2LhkOZbY5z.png)

