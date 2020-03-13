# Database Homework 1

> 10185101210 陈俊潼

### University 表

在 University 数据库中有 8 张表，具体如下：

- `department` ：描述了大学里各个学院，包含学院名字、楼栋名称、预算等
  - 可以更改学院的位置、更新学院信息、添加和删除，查询学院信息
- `course`：含有各个学院提供的课程信息，包括课程 ID，课程名字，学院名和学分等
  - 可以增加和删除课程，更新已有课程，查询课程信息
- `instructor`：含有教师信息，包括教师的名字、部门、薪资等
  - 可以增加和删除老师，变动教师的部门、薪资信息等，查询教师信息
- `student`：含有学生信息，包括学生的名字，专业，目前已有的学分
  - 可以注册新的学生，更新学生已有的学分、专业等，查询学生信息
- `classroom`：含有教室的信息，包含有教室所在的楼栋，房间号和教室能容纳的人数
  - 可以更改教室信息，新建教室，查询教室信息
- `class`：包括具体的课程信息，含有课程ID，学期学年，楼栋，教师，学院和所需学分等信息
  - 可以新增课程，查询已有课程的信息，更新和删除课程
- `assignment`：包含了每个老师的时间安排信息，含有时间段、老师等信息
  - 可以为每个老师新增新的注册，删除安排，或者查新现有的安排信息
- `registration`：含有每个学生注册了的课程，包括学生 ID，课程 ID 等信息
  - 可以允许学生选课、退课来更新注册信息，允许删除课程 ID

### 更多例子

1. 新冠肺炎疫情下管理世界各地的实时感染数据
2. 实时通信软件存储用户信息和消息记录数据
3. 图书馆借阅管理系统
4. 论坛网站存储用户数据和帖子数据
5. Microsoft Excel 本质上也是一个对普通用户友好的数据库

### Exercise 1.5

- Data rudundancy and inconsistency: The metadata of the video can be frequently updated and modifeid, so keeping them in the file may cause some problem of inconsistency.
- Difficulty in accessing data: Since searching video can only  be done via file name or some basic metadata like upload date and modify date, it will be hard for users to find video when there are enoumous of videos.
- Data isolation: This won't be a big problem for videos because video files can be stored as a consistant format. But if the metadata is updated like there's new data needed, this might be a problem.
- Intergrity problems: The system might do double check on whether the video is fully uploaded and make abundant backup.
- Atomicity problems: There should always be metadata for every video clip. And if the system found the video or the metadata is missing, something shold be done to fix this immidiatly.
- Concurrent-access anomalies: If multiple admin are accessing one metadata file, this problem might occur and cause unexpected result.
- Security problems: Since all the data are stored in files, it's hard to control who have access to these certain files.

### Exercise 1.8

|                         | File Processing System | DBMS                                         |
| ----------------------- | ---------------------- | -------------------------------------------- |
| Accessing Method        | Unathorized            | Detailed privilege control                   |
| Redundancy              | Can't be controlled    | Can be controlled                            |
| Consistency             | Can't be obtained      | Can be obtained                              |
| Data Abstraction Levels | Only physical level    | Physical level, logical level and view level |

### Exercise 1.9

Physical data independence means when the physical data scheme is changed, it won't casuse the uppder level like logical schema and alllication shcema needed for rewritten.

This is important cause the phisical schema is often hidden beneath the logical schema, programmers won't interact with this schema directly. If the physical data independence isn't guaranteed, much more work is needed to adjust the application for the programmers and the probability of occuring errors increase.

### Exercise 1.10

| Responsibilities   | Problems when not discharged                                |
| ------------------ | ----------------------------------------------------------- |
| Consistency        | The same instance stored in different place might conflict  |
| Authorizing        | Operaters with no permission could do illegal modifications |
| Avoid redundancy   | Much of the storage space is wasted                         |
| Efficiency         | Taking too much time retriving data                         |
| Concurrency-access | Unexpected result when cooncurrency access occurs           |

### Exercise 1.11

1. The database should be cross-platform, thus a dediated declaratve query language can be packaged into any programming language like C or Java.
2. Non-programmers can also handle with DBMS without learning an actual programmng language.

### Exercise 1.12

The problem here is redundancy and the potential risk of inconsistency. The building name for each department is directly combined into one faculty table, but each department's location is always the same. This filed is redundant. Further more if one the school decides to change a department's budget, he has to change the budget of all the fields and there might be consistency problems here.

