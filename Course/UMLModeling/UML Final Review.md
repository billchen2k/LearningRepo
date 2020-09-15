#  UML Final Review

## Preface

UML: Unified Modeling Language 统一建模语言

![image-20200906120053169](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-Pqqcfr.png)

模型：Model: 模型对显示的简化

Q. 为什么要建模？

A. 因为不能完整地理解一个复杂的系统，所以要对他建模；建模是为了成功开发复杂的项目

Q. 建模的四个目的：

1. 帮助我们按照需要对系统可视化
2. 允许我们详细说明系统结构功能
3. 给出一个知道我们构造系统的模板
4. 对我们所作出的决策进行文档化

视图 View 视点 ViewPoint：从某个方面得到的模型

语法 Syntax 语义 Semantics

**Visual Modeling:** 使用标准图形符号建模

UML 的概念模型：

![image-20200906123748416](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-5FFpZt.png)

UML 主要用于软件密集型系统，主要运用在企业信息系统、银行与金融服务、电信、运输、零售、医疗电子；是一种表达工具，可以方便地表达设计师的思想

**公共机制：**主要包含详述、修饰、通用划分、扩展机制

4+1 View:

![image-20200906180720684](../../../../Library/Application%20Support/typora-user-images/image-20200906180720684.png)

## 对象

Object: 拥有数据和行为的一个实体

类：共享相同属性、操作、方法或行为的一组对象的描述符

Inheritance: 继承 Inheritance is a way of relating two classes sos that one class may use another class's members without redefining them

Polymorphism: 多态：接口的多种不同的实现方式

- 多态可以编写使用父类的程序代码，但可以使用任何类型的子类（代码比较灵活）

Encapsulation: 封装：隐藏对象方法实现细节

Interface 接口：The interface should completely describe how users of the class interact with the class.

Abstract 抽象：Giving the user the minimal interface possible

- 如果一个类没有包含足够多的信息来描述一个具体的对象，这样的类就是抽象类。
- 一个类中含有抽象方法（被abstract修饰），那么这个类必须被声明为抽象类（被abstract修饰）。明为抽象类（被abstract修饰）明为抽象类（被abstract修饰）明为抽象类（被abstract修饰）.

## 用例，用例图

### :exclamation: 四种关系的箭头

- 关联关系：两个事物之间是一种 组织、结构关系，持续时间是稳定的
- 依赖关系：两个事物之间的关系是短暂的、一方依赖另一方；箭头指向被依赖的一方
- 继承关系（泛化关系）：一般事物与特殊事物之间的关系
- 实现关系：接口与具体实现事物之间的关系（插座 与 发电厂）

![image-20200906134652555](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-qSycR7.png)



Actor: 参与者：代表位于系统之外并和系统进行交互的一类事物（人、物、其他软件子系统等）

Boundary 系统边界：立足于当前要解决的问题领域，系统边界描述了系统内部与外部之间交互的集合

用例：是对一组侗族序列的描述，系统执行这些动作序列来为参与者产生一个可观察的结果值。

### 关系

#### 参与者与参与者

- 泛化：特殊与一般的关系，用户和系统用户等：

  - 实现，空心箭头

    

#### 用例与用例

- 泛化
- 包含 includes：子用例是一个常用功能块，可以用在多个基用例中，而且基用例必须包含了子用例，基用例才能正常进行。
- 拓展 extends：子用例是独立的用例，完成一定的功能
  - 拓展和泛化均为虚线箭头，使用`<<include>>` 或`<<extend>>` 来描述
  - ==方向：小指大==

![image-20200906140012186](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-pPVrPX.png)

### 用例描述

Eg.

```
Use Case: NotifyOverdraft
Brief Description: Notifies the Customer that his account has become overdrawn.
Pre-Condition: This service is only available if the Customer has purchased the overdraft notification service.

Main Success Scenario:
1. The use case starts as extension of ProcessTransactions at {Summarize Transactions} if the Customer has purchased the overdraft notification service and the set of completed transactions has caused the account to become overdrawn.
2. The System determines the Customer's preferred notification mechanism.
3. The System composes the overdraft notification.
4. The System transmits the overdraft notification to the Customer using the Customer's preferred notification mechanism.
5. The use case ends.
```

![image-20200906140352343](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-A8pDob.png)

## 类

类：具有相同属性（或者数据、信息、状态）、相同行为（或者方法、操作）的一组对象的描述符，是真实世界事物的抽象。

UML 中类的表示：

![image-20200906154347846](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-vuje1z.png)

修饰符：

- Public (+)

- Private (-)
- Protected (#)
- Implementation (~)
  - access means that the class is accessible only by the implementation of the package containing the class

### 类的关系

- 泛化关系 Generalization Relation
- 依赖关系 Dependency （使用虚线+岔箭头）
- 关联关系：结构性的联系

#### 关联关系的修饰

名称、方向、角色、数量映射关系等

![image-20200906161003422](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-cEF8oS.png)

![image-20200906161114195](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-izGuYI.png)



- 多重性：![image-20200906180410415](../../../../Library/Application%20Support/typora-user-images/image-20200906180410415.png)

#### 聚合 / 组合 Aggregation & Composition

聚合： ‘整体’有管理 ‘部分’的特有的职责。它用端点带有空菱形的线段表示，空菱形与‘整体’类相连接。

组合：‘整体’拥有 ‘部分’的生命；它用端点带有实菱形的线段表示，实菱形与‘整体’类相连接。

可以理解为聚集（空心）只包含部分，而组合则是完全包含 Eg.

<img src="../../../../Library/Application%20Support/typora-user-images/image-20200906175904537.png" alt="image-20200906175904537" style="zoom:50%;" />

<img src="../../../../Library/Application%20Support/typora-user-images/image-20200906175930939.png" alt="image-20200906175930939" style="zoom:50%;" />

刁钻的例子：

![image-20200906180755583](../../../../Library/Application%20Support/typora-user-images/image-20200906180755583.png)

#### 关联类

Motivation: Some attributes are not easily be accommodated in either of the classes with many-to-many relationship.

关联类也是一个类，包括了类、联系和虚线（类似于 DMBS 中的 Relation Entity）



### 类图

- 约束：指定了类要满足的一个或多个规则
- 约束**放在括号 { } 中**
  - ![img](https://img-blog.csdn.net/20160611212659079?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

## 交互

交互的基本概念：消息

- 调用（call）：启动某个对象的操作

  - 操作是对象所实现的服务

  - 对象也可以给自己发送消息

- **返回**(return)：操作向调用者返回一个值

- **发送**(send)：向一个对象发送一个信息

  - 同步消息

  - 异步消息

- **创建**(create)：此消息的发送导致目标对象被创建。

- **销毁**(destroy)：此消息的发送导致目标对象被销毁 

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-2uZGt1.png" alt="image-20200906192530993" style="zoom:67%;" />



实例的命名：名称：类型（必须为实例命名）：如：`c1:ClassA` 。

孤儿实例 orphan objects: 省略类型名的对象

匿名实例：只有类型名

**语境**： 就是可以发生交互的情况、场景

**连接**：连接是关联的实例，主要有以下约束：

- Association, Self, Global, Local

Eg.

![image-20200906193823706](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-eiQWqV.png)

交互图有两种类型：

### 顺序图 Sequence Diagram

强调消息的时间顺序。

对象生存线：Object Lifeline 每个对象的底部中心都具备的一条虚线

控制焦点：由消息引发的动作执行过程，被描述为控制焦点。

<img src="../../../../Library/Application%20Support/typora-user-images/image-20200906194930849.png" alt="image-20200906194930849" style="zoom:50%;" />



<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-DsiyCg.png" alt="image-20200906201605741" style="zoom:50%;" />

### 通信图 Communication Diagram

强调接受和发送消息的对象的组织结构。

交互图的另一种表现形式；在语义上和顺序图等价

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-YmtHDU.png" alt="image-20200906195001883" style="zoom:50%;" />

Link：连接可以有名字，消息可以借助此连接关系传递；仅从图符的绘制无法在通信图上读出消息发送的顺序。

## 活动，活动图

一个例子：

![image-20200906202508567](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-KJ957N.png)

概念：

- 活动节点：是活动的组织单元，用一个两头为圆形的方框来表示

- 分支：一个菱形来表示分支

- 泳道：Swimlanes 将一个活动图的活动分组

- 并发控制流 concurrent、分岔控制流

  ![image-20200906204314584](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-cgGJgU.png)

迭代：

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-yiszR2.png" alt="image-20200906204041846" style="zoom:50%;" />

- 使用圆圈与带环圆圈来表述初始状态与终止状态
- 活动节点可嵌套

一个更全面的例子：

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-BqLwqX.png" alt="image-20200906205047259" style="zoom: 50%;" />



> 活动图是 UML 对系统动态方面建模的五种图之一（分别是用例图 / 活动图 / 顺序图 / 通信图 / 状态图）

### *数据流图

UML 不包含，但表达能力和活动图相同

## 状态

Motivation: 考察**单个**实体的动态行为时。

这是为了能够更好地处理

概念：对向生命中起中的一个条件或状况

状态机：说明对象在它的生命期中, 响应事件所经历的状态序列 以及它们对每个事件的响应

- 事件：对一个在时间和空间上占有一定位置的、有意义的事情的描述
- 迁移：在状态 A，发生事件并满足一定条件，转移到状态 B

### 状态组成部分

1. 名称 - 首字母大写
2. 进入退出动作 entry / exit action
3. 内部迁移 internal transition
4. 子状态 substate
5. 延迟事件 deferred event

**一个状态的表示：**

![image-20200906212351993](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-Ye8Jkb.png)

事件表示：==触发事件名称 [触发条件] / 迁移动作（三部分可省略，但至少需要有一个部分）

迁移表示：叉形箭头实线

### 状态图

一个完整的例子：

![image-20200906212650170](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-4kfz54.png)

和交互图与活动图相比：

- 都是对共同工作对象群体的行为建模
- 动态行为

但状态机是对**单个对象**的行为建模。

（活动图更强调从活动到活动的控制流、多个业务角色）

状态图强调对象的潜在的状态和这些状态之间的迁移

## 高级类 & 高级关系

### 类目

- 类目：类目是一种描述行为特征（以操作的形式）和结构特征（以属性的形式）的模型元素
  - 类 class 是类目的一种

同样具有和类相同的可见性（`# ~ + -`）

抽象操作：方法可以是未定义的

- 模板类：是一个参数化的类（定义了一系列形式化的参数

### 高级关系

更多关联关系：

- 依赖关系构造型（使用 `<<...>>` 表示）
  - 绑定依赖 `bind` 是依赖关系的一个变体，箭头指向模板类
  - 导出依赖 `derive` 依赖关系的变体
  - `permit` 源从目标获得特定的可见性



## 接口、包与进程

### 接口

构件 Component: 系统的一个物理的可替换部分，遵从一组接口的要求，并提供对这些接口的实现

- 由类、子构件组成的，能够完成相对独立的子功能

接口强调外部行为规范，不强调动态行为的实现方法。**遵循同一个接口的构件可以互相替换**。

图示：需要接口 与 提供接口

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-uN749S.png" alt="image-20200906232301079" style="zoom:50%;" />

接口名字通常以 I 开头：`IHalftoning`

- 接口的实现关系：是两个类目的语义关系

  <img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-SANvvQ.png" alt="image-20200906233348122" style="zoom: 67%;" />

### 包

UML 组织建模元素的机制

为了有效地控制和管理模型的设计、表达和更改，达到有效地可视化、详述、构造和文档化的目的，必须对模型元素进行组织

![image-20200906234016396](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-xWKvsT.png)

- 导入和导出 `import` `access`

### 进程与线程

- 主动类：其实例是主动对象，拥有一个或者多个进程 / 线程
- 控制流 Flow of Control：纯顺序系统，只有一个控制流；并发系统有多个控制流

**建模元素**：

- 定时标记 timing mark：
  - ![image-20200906234428524](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-06-7l5qpj.png)

时间表达式：绝对或相对的时间表达

定时约束：==以约束的形式表示 {b-a < 10ms}==

## 构件、部署

构件的主要成分 Component

- 端口 PORT 被封装的构件的特定窗口
- 连接件 Connector 是一种规则，指导有端口的构件之间互联
- 把构件连接起来形成符合构件或系统

构件图：依赖关系使用虚线箭头表示

Eg.：

![image-20200907000816274](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-lGArAW.png)

使用构件图可以为应用程序 API 建模

更详细的例子：

![UML-组件图](https://pic3.zhimg.com/v2-93a83fcc1b6b65cdd54e8b0d0e426e58_1440w.jpg?source=172ae18b)



### 部署图

用于描述系统硬件的物理拓扑结构以及在此结构上运行的软件

构成部署图的主要元素：

- 节点(node) 
- 构件(component) 
- 关系(relationship) | connection 
  - 依赖关系和关联关系
  - Rose中只有一种：连接（connection)
  - Cf: Link | Relationship ? 
- 还可以包含
  - 注解、约束、
  - 包、子系统
  - 用于将模型元素分成较大的组块

Eg.

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-bW00vU.png" alt="image-20200907001615475" style="zoom:67%;" />

## More...

### 对象图

- 对象图：表示对象与对象之间的关系

![image-20200907002949145](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-06ECgt.png)

与使用类图的目的一样，使用对象图对系统的静态视图或者静态进程视图建模，但是对象图着眼于真实或者原型化的实例。这种视图主要支持系统的功能需求，即，系统应当提供给它的最终用户的服务。对象图可以对静态数据结构建模。

### 形式化建模

Motivation：针对开发重大项目（如原子弹、航天飞船等），不允许出现差错

形式化方法是基于严格数学基础，对计算机硬件和软件系统进行形式描述、开发和验证的技术。

（感受即可）

![image-20200907003618168](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-v3KnDO.png)

饼：形式化方法需要适应软件定义使能的软件新形态，适应软件作为社会基础设施的地位，在基础概念、规约、验证和工具等方面进一步发展，并与人工智能、网络空间安全、量子计算、生物计算等领域和方向交叉、融合。

### 可信软件

“可信性”是在正确性、可靠性、安全性、时效性、完整性、可用性、可预测性、生存性、可控性等众多概念的基础上发展起来的一个新概念。

![image-20200907003720656](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-09-07-LHHdXI.png)

Programming language of TRUST WORTHY:  `sysML` `OCL`

 