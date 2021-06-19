# Software Requirements

## 需求研发

![image-20210618220546882](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-18-WIaxmu.png)

![image-20210618215723134](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-18-MkvzdY.png)

主要内容提纲：

![image-20210618221308720](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-18-Hk4CKE.png)

列车控制系统

- 业务需求：**用户对系统应达到的高层次业务目标**
  - 列成系统应能承载旅客运输、QPS...
- 用户需求：**使用软件产品的用户需要实现的应用任务**
  - 例如驾驶人员能控制速度、维护人员有权读日志

- 系统需求：**包含了软件产品的系统顶层需求**
  - 如列车自动保护系统、连锁控制系统
- 功能需求：为了实现业务需求而开发的软件功能：
  - 如能根据加速度计算位置
- 业务规则：政策、法规、行业规范与标准
- 质量属性：软件运行的稳定性和安全性等属性
- 约束条件：系统设计的限制条件与约定
- 外部接口：软件系统与外部环境的交互通道

### 系统的愿景与范围

- VISION：What the product is about and what it will become
- SCOPE: what portion of the product will address

业务需求：产品背景、市场机遇、业务目标、市场分析、风险评估

#### 关联图 Context Diagram

使用椭圆表示系统本身，箭头表示和外界的互动

![image-20210618223359846](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-18-qZv7Bp.png)

开始之前：对用户进行分类 

### 需求分析

需求获取的 CRUD 矩阵（Create Read Update Delete）：从数据变量的产生、读取、更新和删除这几个状态变化来判断需求的完整性或充分性 

需求理解：使用用例图 Usecase

- 用例描述：Actors, Description, Precondition, Postcondition, Normal Course, Alternative Course, Exceptions

事件-响应表：

![image-20210618225729110](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-18-nAkfkY.png)

![image-20210618225843172](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-18-E5y3LI.png)



#### 数据流图

撰写的需求文档是用户想要的软件

- 决策图、数据流图、状态转换图、决策表与决策树、类图、对话图、ER 图等
- **数据流图**：描述数据如何在模块之间流动，Eg. ↓
- ![image-20210618231430250](/Users/billchen/Library/Application%20Support/typora-user-images/image-20210618231430250.png)

条件数据流图 CDFD：源于 SOFL Structured Object-Oriented Formal Language），最早由刘少英教授提出

Remark：数据流图直观易懂，但时序逻辑不清晰，难以刻画反应式行为

#### 决策表

- 刻画系统行为，刻画不同逻辑下系统的运作规则
- ![image-20210618232156835](../../../../Library/Application%20Support/typora-user-images/image-20210618232156835.png)

- 相同状态可以合并

#### 对话图

- 通过描述界面的转移关系简介呈现系统行为来分析
- ![image-20210618232602976](../../../../Library/Application%20Support/typora-user-images/image-20210618232602976.png)



#### 状态转换图

可以理解为状态机

State Transition Diagram STD

![image-20210618232816759](../../../../Library/Application%20Support/typora-user-images/image-20210618232816759.png)

![image-20210618233129017](../../../../Library/Application%20Support/typora-user-images/image-20210618233129017.png)



- 安全性分析要求：存在转移关系的状态具有同一个输入数据，对状态转移前后这一输入数据的取值进行检查，分析输入数据取值在状态转移前后“变化、不变、跳变、停止输入、输入异常......等情况下输出的正确性，直至覆盖所有转移。

### 需求文档

结构合理：模板化、标准化

名称问题：software requirements specification，需求描述文档（规格说明、规约等）

模板之一：IEEE Standard for SRS。

![image-20210618230534777](/Users/billchen/Library/Application%20Support/typora-user-images/image-20210618230534777.png)

![image-20210618230743596](/Users/billchen/Library/Application%20Support/typora-user-images/image-20210618230743596.png)

软件需求规格说明：

![image-20210618230801024](/Users/billchen/Library/Application%20Support/typora-user-images/image-20210618230801024.png)

#### Extend: 形式化方法

基于数学的描述软件系统行为的方法，精确描述、开发和验证。

常用语言：Z语言，B方法，Event-B方法，VDM方法，SOFL

### 需求确认 & 验证

- 人员结构：撰写者、构建者、后继使用者、与需求文档构建过程发生交互的人员

- 使用软件原型
  - 水平原型
  - 垂直原型
  - 可抛弃原型
  - 演化式原型
- 对需求的管理进行量化：

## 需求管理

需求管理的内容：应对需求变化。变更控制的模板：

![image-20210619162817817](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-06-19-bH81ao.png)

模板记录，评审，影响分析