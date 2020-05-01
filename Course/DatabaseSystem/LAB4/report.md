## Database LAB 3

> 10185101210 陈俊潼

### 准备工作

在 Microsoft SQL Server 下载客户端并配置安装。安装后配置 SQL Server 的 TCP/IP 协议和 Named Pipes 协议为开启状态，以允许远程连接：

<img src="https://i.loli.net/2020/04/30/MdmcUSjQvsVaRTN.png" alt="image-20200430154528132" style="zoom:50%;" />

接着安装 Microsoft SQL Server Management Studio，启动软件并连接数据库，为 sa 用户指定登录密码。

![](https://i.loli.net/2020/04/30/neRKZyBdJkw4z1h.png)



### Exercise 1

编写触发器如下：

```mssql
CREATE trigger sectionTrigger FOR section ON INSERT
AS
BEGIN
	DECLARE @tid int;
	SELECT @tid = time_slot_id FROM inserted;
	IF NOT EXISTS (SELECT * FROM time_slot WHERE time_slot_id)
	BEGIN
		print 'Referential intergrity not satisfied.'
		ROLLBACK;
	END
END
```

### Exercise 2

根据要求，创建数据库employer和warehouse数据库表:

![](https://i.loli.net/2020/04/30/ajdIJvEqi6T4FWA.png)

并构建如图所示的虚拟数据，建立了三个员工，两个仓库：

![](https://i.loli.net/2020/04/30/qgZtk7YjKM1FDx8.png)


根据需求，随机建立一些演示数据。这里使用的数据如下：表 employer:

|ID| employerNo|name|sex|salary|warehouseNo|
| ---- | ---- | ------------ | ---- | ---- | ---- |
| 1    | Zg3  | Bill Chen    | male | 3000 | Wh1  |
| 2    | Zg4  | William Chen | male | 3000 | Wh2  |
| 3    | Zg3  | Charles Chen | male | 3000 | Wh1  |
| NULL | NULL | NULL         | NULL | NULL | NULL |

表 warehouse:
|ID|warehouseNo|city|area|buildTime|
| ---- | ---- | -------- | ---- | ---------- |
| 1    | Wh1  | Shanghai | 600  | 2020-01-01 |
| 2    | Wh2  | Beijing  | 600  | 2019-01-01 |
| NULL | NULL | NULL     | NULL | NULL       |

接着为了实现在更新仓库名的时候同步更新雇员表内的仓库名，这里创建 trigger:

```mssql
create trigger warehousetrigger on warehouse for update
as
begin
	declare @old char(10)
	declare @new char(10)
	select @new = warehouseNo from inserted
	select @old = warehouseNo from deleted
	update employer set warehouseNo=@new where warehouseNo=@old
	print 'Updated.'
end
```

![](https://i.loli.net/2020/04/30/amk7rhUl9HcbYWV.png)

接下来验证是否成功。执行 `UPDATE warehouse SET warehouseNo='Wh1new' WHERE ID=1;` :

![](https://i.loli.net/2020/04/30/bSKDOZAnxQplWBq.png)

执行成功后，发现 `employer` 表中的信息也随之发生了更新。

![](https://i.loli.net/2020/04/30/o4RSmgIxwi7AUYr.png)



### Exercise 3

首先新建两个数据库表。为了简化表示，保留了几个必要字段。对于用户，保留了ID，姓名，等级和总消费额；对于账单，只保留了账单ID，用户ID和，日期，订单价格和签收状态。建立数据关系后，构造简单的示例数据。

这里 grade 作为会员等级，使用 0 表示普通用户，1 表示白金会员，2 表示铂金会员。累计金额满 10000 元 和 20000 元可以升级到白金会员和铂金会员。

![](https://i.loli.net/2020/04/30/DfXaxBYHFIh7dut.png)

为了能够实时切换打折策略，这里新建了一个 `config` 表，用于存储策略：

![](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-30-image-20200430182638628.png)

这里只存储了一个`strategy` 行，0 和 1 对应的不同的打折策略。

接下来按照以下逻辑实现打折策略：

| startege 值 | 订单金额累计时间 | 临界商品是否打折 |
| ----------- | ---------------- | ---------------- |
| 0           | 支付前           | 是               |
| 1           | 支付后           | 否               |
| 2           | 签收后           | 否               |

接下来首先编写修改策略的控制存储：

```mssql
CREATE proc changeStrategy
@strategy int
AS
BEGIN
	UPDATE config SET value = @strategy WHERE policy = 'strategy';
	print 'Stratedy updated.'
END
```

现在使用 `execute changeStrategy x` 即可更改策略。

针对不同的策略，在插入新订单的时候会有不同的升级措施和打折措施。于是编写针对 `order` 的 trigger 如下：

```mssql
CREATE TRIGGER orderInsertTrigger ON [order] FOR INSERT
AS
BEGIN
	DECLARE @s int;
	DECLARE @uid int;
	DECLARE @sum float;
	DECLARE @thisamount float;
	SELECT @s = value FROM config WHERE policy = 'strategy';
	SELECt @uid = customer_id FROM inserted
	SELECT @thisamount = amount FROM inserted
	IF @s = 0
	BEGIN
		--- Count before payment
		SELECT @sum=sum(amount) FROM [order] WHERE customer_id = @uid;
		IF @sum >= 20000
		BEGIN
			UPDATE customer SET grade=2 WHERE customer_id = @uid;
			print 'Customer grade set to 2.'
		END
		ELSE IF @sum >= 10000
		BEGIN
			UPDATE customer SET grade=1 WHERE customer_id = @uid;
			print 'Customer grade set to 1.'
		END
	END
	ELSE IF @s = 1
	BEGIN
		--- Count after payment
		SELECT @sum=sum(amount) FROM [order] WHERE customer_id = @uid AND 
		([status] = 'paid' OR [status] = 'delivered');
		IF @sum >= 20000
		BEGIN
			UPDATE customer SET grade=2 WHERE customer_id = @uid;
		END
		ELSE IF @sum >= 10000
		BEGIN
			UPDATE customer SET grade=1 WHERE customer_id = @uid;
		END
	END
	ELSE IF @s = 2
	BEGIN
		--- Count after delivered
		SELECT @sum=sum(amount) FROM [order] WHERE customer_id = @uid AND [status] = 'paid';
		IF @sum >= 20000
		BEGIN
			UPDATE customer SET grade=2 WHERE customer_id = @uid;
			print 'Customer grade set to 2.'
		END
		ELSE IF @sum >= 10000
		BEGIN
			UPDATE customer SET grade=1 WHERE customer_id = @uid;
			print 'Customer grade set to 1.'
		END
	END
	UPDATE customer SET total_amount = @sum WHERE customer_id = @uid;
END
```

以上是针对插入的 trigger。考虑到第三种策略需要在用户签收后再计算订单总额，再针对第三种策略新建一个针对更新的  trigger：

```mssql
CREATE TRIGGER orderUpdateTrigger ON [order] FOR UPDATE
AS
BEGIN
	DECLARE @s int;
	DECLARE @uid int;
	DECLARE @sum float;
	DECLARE @thisamount float;
	DECLARE @newstatus varchar(50);
	SELECT @s = value FROM config WHERE policy = 'strategy';
	SELECt @uid = customer_id FROM inserted
	SELECT @thisamount = amount FROM inserted
	SELECT @newstatus = status FROM inserted
	print 'Update trigger running...'
	IF @s = 2 AND @newstatus = 'delivered'
	BEGIN
		--- Update after delivered	
		SELECT @sum=sum(amount) FROM [order] WHERE customer_id = @uid AND status = 'delivered';
		print 'Order delivered.'
		IF @sum >= 20000
		BEGIN
			UPDATE customer SET grade=2 WHERE customer_id = @uid;
			print 'Customer grade set to 2.'
		END
		ELSE IF @sum >= 10000
		BEGIN
			UPDATE customer SET grade=1 WHERE customer_id = @uid;
			print 'Customer grade set to 1.'
		END
		UPDATE customer SET total_amount = @sum WHERE customer_id = @uid;
	END
END
```

完成后，我们将策略设置成 2，即在订单签收后更新总额。

执行以下 SQL 语句：

```mssql
EXECUTE changeStrategy 2;

INSERT INTO [order] (order_id, customer_id, order_time, amount, status)　VALUES (2, 1, CURRENT_TIMESTAMP, 10000, 'unpaid');
```

此时发现用户表中的账单总数没有更新，等级仍然是 0。

![](https://i.loli.net/2020/04/30/upnfP5vhtOd4cWL.png)

接着执行`UPDATE [order] SET status='delivered' WHERE order_id = 2;`，模拟订单签收操作。可以看到，已经触发了触发器。

![](https://i.loli.net/2020/04/30/OsHLbG2mFBjRITg.png)



再次查询 `order` 和 `customer`表的信息，可以看见已经得到了更新：

![](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-30-image-20200430211032582.png)



再次把策略设置为 0，即只要提交订单就计算总额。运行以下命令：

```mssql
EXECUTE changeStrategy 0;

INSERT INTO [order] (order_id, customer_id, order_time, amount, status)　VALUES (3, 2, CURRENT_TIMESTAMP, 20005, 'unpaid');
```

可以看到订单还未签收，用户等级已经更新到铂金会员：

![](https://i.loli.net/2020/04/30/XmCAoaGFTMcIfU3.png)

此时两个表的查询数据结果如下：

![](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-30-image-20200430212038413.png)



### Exercise 4

首先建立数据库表，并虚拟数据：

![](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-30-image-20200430170112434.png)

仅供测试使用，这里的身份证号用了一位数字代替，对于症状的描述也简化成了Good 和 Bad 两种情况。认为体温良好的范围为 36.0 - 37.5 摄氏度，同时新增加的病例默认会在早晨服用 ID 为 1 的药物。

于是编写存储过程如下：

```mssql
CREATE proc [dbo].[newPatient]
@pid int
AS
BEGIN
	IF NOT EXISTS (SELECT * FROM patient WHERE pid = @pid)
		BEGIN
			INSERT INTO patient(pid, pname, psex, page, pdiagnosis_time, pdiagnosis_place, pcondition) VALUES (@pid, 'unknown', 'unknown', 'unknown', CURRENT_TIMESTAMP, 'Shanghai', 'Not Cured');
			INSERT INTO patient_medicine(pid, medid, eattime) VALUES (@pid, 1, 'morning')
			print 'New patient added.'
		END
	ELSE
		print 'Patient existed.'
END
```

执行 `execute newPatient 1` 会得到：

![](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-30-image-20200430171637227.png)

此时再执行 `execute newPatient 6` 会得到：

![](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-30-image-20200430171602246.png)

同时 `patient` 表和 `patient_medicine` 表中的数据都会得到更新：

![](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-30-image-20200430171732582.png)

接着编写触发器如下：

```mssql
CREATE trigger [dbo].[diagnosisTrigger] ON [dbo].[patient_detection] FOR INSERT
AS
BEGIN
DECLARE @count int;
DECLARE @pid int;
SELECT @pid = pid FROM inserted;
DROP TABLE #normalDays;
SELECT * INTO #normalDays FROM patient_detection WHERE pid=1 AND dtemperature>=36.0 AND dtemperature<=37.5;
IF @pid IN (SELECT a.pid FROM #normalDays a, #normalDays b, #normalDays c WHERE DATEDIFF(DAY, b.dtime, a.dtime)=1 AND DATEDIFF(DAY, c.dtime, b.dtime)=1
	AND c.dsymptom='Good' AND c.dchestimage='Good' AND b.dnucleicacid='False' AND c.dnucleicacid='False')
	BEGIN
		UPDATE patient SET pcondition='Cured' WHERE pid=@pid;
		print 'Patient cured.'
	END
DROP TABLE #normalDays;
END
```

此时，执行 ：

```mssql
INSERT into patient_detection(pid, dtime, dtemperature, dsymptom, dchestimage, dnucleicacid)
VALUES (1, '2020-03-11', 36.5, 'Good', 'Good', 'False');
```

可以看到来自 trigger 的提示：

![](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-30-image-20200430175933621.png)

病患情况也已经更新成 Cured。

![](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-30-image-20200430180004077.png)



---

###  附录

练习 1、2、4使用的表导出的脚本（位于 master 数据库内）：

```mssql
USE [master]
GO
/****** Object:  User [##MS_PolicyEventProcessingLogin##]    Script Date: 2020/4/30 21:24:40 ******/
CREATE USER [##MS_PolicyEventProcessingLogin##] FOR LOGIN [##MS_PolicyEventProcessingLogin##] WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  User [##MS_AgentSigningCertificate##]    Script Date: 2020/4/30 21:24:40 ******/
CREATE USER [##MS_AgentSigningCertificate##] FOR LOGIN [##MS_AgentSigningCertificate##]
GO
/****** Object:  Table [dbo].[employer]    Script Date: 2020/4/30 21:24:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[employer](
	[ID] [int] NOT NULL,
	[empNo] [varchar](50) NOT NULL,
	[empName] [varchar](50) NULL,
	[sex] [nchar](10) NULL,
	[salary] [nchar](10) NULL,
	[warehouseNo] [nchar](10) NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[normalDays]    Script Date: 2020/4/30 21:24:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[normalDays](
	[pid] [nchar](10) NULL,
	[dtime] [datetime] NULL,
	[dtemperature] [nchar](10) NULL,
	[dsymptom] [varchar](50) NULL,
	[dchestimage] [varchar](50) NULL,
	[dnucleicacid] [varchar](50) NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[patient]    Script Date: 2020/4/30 21:24:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[patient](
	[pid] [nchar](10) NULL,
	[pname] [varchar](50) NULL,
	[psex] [nchar](10) NULL,
	[page] [nchar](10) NULL,
	[pdiagnosis_time] [datetime] NULL,
	[pdiagnosis_place] [varchar](50) NULL,
	[pcondition] [nchar](10) NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[patient_detection]    Script Date: 2020/4/30 21:24:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[patient_detection](
	[pid] [nchar](10) NULL,
	[dtime] [datetime] NULL,
	[dtemperature] [nchar](10) NULL,
	[dsymptom] [varchar](50) NULL,
	[dchestimage] [varchar](50) NULL,
	[dnucleicacid] [varchar](50) NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[patient_medicine]    Script Date: 2020/4/30 21:24:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[patient_medicine](
	[pid] [nchar](10) NULL,
	[medid] [nchar](10) NULL,
	[eattime] [varchar](50) NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[warehouse]    Script Date: 2020/4/30 21:24:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[warehouse](
	[ID] [int] NULL,
	[warehouseNo] [varchar](50) NULL,
	[city] [varchar](50) NULL,
	[area] [int] NULL,
	[buildTime] [date] NULL
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[newPatient]    Script Date: 2020/4/30 21:24:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE proc [dbo].[newPatient]
@pid int
AS
BEGIN
	IF NOT EXISTS (SELECT * FROM patient WHERE pid = @pid)
		BEGIN
			INSERT INTO patient(pid, pname, psex, page, pdiagnosis_time, pdiagnosis_place, pcondition) VALUES (@pid, 'unknown', 'unknown', 'unknown', CURRENT_TIMESTAMP, 'Shanghai', 'Not Cured');
			INSERT INTO patient_medicine(pid, medid, eattime) VALUES (@pid, 1, 'morning')
			print 'New patient added.'
		END
	ELSE
		print 'Patient existed.'
END
GO
```



练习 3 中的数表生成脚本（位于 shopping 数据库内）：

```mssql
USE [master]
GO
/****** Object:  Database [shopping]    Script Date: 2020/4/30 21:22:09 ******/
CREATE DATABASE [shopping]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'shopping', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\DATA\shopping.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'shopping_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\DATA\shopping_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
 WITH CATALOG_COLLATION = DATABASE_DEFAULT
GO
ALTER DATABASE [shopping] SET COMPATIBILITY_LEVEL = 150
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [shopping].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [shopping] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [shopping] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [shopping] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [shopping] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [shopping] SET ARITHABORT OFF 
GO
ALTER DATABASE [shopping] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [shopping] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [shopping] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [shopping] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [shopping] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [shopping] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [shopping] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [shopping] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [shopping] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [shopping] SET  DISABLE_BROKER 
GO
ALTER DATABASE [shopping] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [shopping] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [shopping] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [shopping] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [shopping] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [shopping] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [shopping] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [shopping] SET RECOVERY FULL 
GO
ALTER DATABASE [shopping] SET  MULTI_USER 
GO
ALTER DATABASE [shopping] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [shopping] SET DB_CHAINING OFF 
GO
ALTER DATABASE [shopping] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [shopping] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [shopping] SET DELAYED_DURABILITY = DISABLED 
GO
EXEC sys.sp_db_vardecimal_storage_format N'shopping', N'ON'
GO
ALTER DATABASE [shopping] SET QUERY_STORE = OFF
GO
USE [shopping]
GO
/****** Object:  Table [dbo].[config]    Script Date: 2020/4/30 21:22:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[config](
	[policy_id] [int] NULL,
	[policy] [varchar](50) NULL,
	[value] [varchar](50) NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[customer]    Script Date: 2020/4/30 21:22:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[customer](
	[customer_id] [nchar](10) NOT NULL,
	[name] [varchar](50) NOT NULL,
	[grade] [nchar](10) NULL,
	[total_amount] [nchar](10) NULL,
 CONSTRAINT [PK_customer] PRIMARY KEY CLUSTERED 
(
	[customer_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[order]    Script Date: 2020/4/30 21:22:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[order](
	[order_id] [int] NOT NULL,
	[customer_id] [int] NULL,
	[order_time] [datetime] NULL,
	[amount] [float] NULL,
	[status] [nchar](10) NULL,
 CONSTRAINT [PK_order] PRIMARY KEY CLUSTERED 
(
	[order_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[changeStrategy]    Script Date: 2020/4/30 21:22:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE proc [dbo].[changeStrategy]
@strategy int
AS
BEGIN
	UPDATE config SET value = @strategy WHERE policy = 'strategy';
	print 'Stratedy updated.'
END
GO
USE [master]
GO
ALTER DATABASE [shopping] SET  READ_WRITE 
GO

```

