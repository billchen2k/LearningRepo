### 要求的开发环境

本系统将使用 Gitee 作为版本管理系统工具，所有成员将基于 Git 进行版本协作。对各分支做如下规约：


- master ：主分支，由 CI/CD 工具自动 merge，任何成员不应主动提交。

- develop：主要的开发分支。但不应直接在 develop 分支上发起提交，而是基于 develop 分支切出不同的 branch，如 feature / bugfix 等做开发，之后合入 develop。

- release：作为归档分支，在确认版本稳定后切入 release/[version_num] 分支。release 分支中的任何一个提交应当随时具备上线部署的能力，在后续系统出现致命问题时可以随时回滚。

- feature：开发人员的个人开发分支，从 develop 分支切出并在该分支上迭代。内容应和新需求开发相关，在开发完成后 merge 进 develop 分支。

- bugfix：开发人员的个人开发分支，从 develop 分支切出并在该分支上迭代。内容应和缺陷修复相关，在开发完成后 merge 进 develop 分支。

本系统的前端基于 vue.js 开发。为保证小组成员开发环境统一，避免 .idea 文件配置冲突，统一使用 WebStorm 2021.2 作为开发 IDE。使用 yarn 作为依赖管理程序，以保证更高的依赖解析性能，防止 package.lock 文件冲突。

本系统的后台模块开发环境为 IntellijIDEA 2021.2，使用Java 1.8 (adopt-openjdk 1.8) 作为 Java 开发环境。使用 Apache Maven 作为依赖管理程序。

对于开发所用的操作系统，不做限制，但应在 Windows 10 1904 / macOS 10.15 / Ubuntu 16.04 以上。

开发过程中，编译产物（前端对应 `build` 文件夹，后端对应 `target ` 文件夹）不应上传到 Git 仓库中。.idea 文件夹中，服务器配置可以更新至 Git 仓库，窗口配置和开发人员的个人环境配置不应当上传。任何密码、token 及和权限认证相关的信息，不应当以明文的方式上传至协作仓库。

  ### 要求的维护环境

  本系统的维护环境为阿里云的 Linux 服务器，具体配置及环境如下：

- 操作系统：CentOS
- 实例规格：ecs.g7a.large，2vCPU
- 存储容量：40GB
- 运行内容：2G
- 软件环境
  - 数据库：MySQL 8, MongoDB, Redis
  - Java 版本：adopt-openjdk 1.8
  - node.js 版本：14.0
  - Web 服务器：Nginx

 ###  要求的培训

本项目的培训内容包括如下部分：

A. Git：包括版本管理系统的常见操作和分支操作，包括但不限于 pull, push, checkout, rebase, fetch, add, commit.

B. SRE 运维管理：包括服务器性能监控，端口监控及配置管理，以及在系统出现异常和崩溃时对错误日志、访问日志进行回捞操作。同时应当熟练掌握快速部署新发布版本的能力。

C. API 设计：掌握关于 RestFul API 的设计模式和原理，并设计合理的返回体结构，提供详细的 json 体。

D. 数据库设计：具备分析和抽象系统所需的数据模型的能力，了解数据库的设计范式，提供数据库文档供其他开发成员开发，熟练编写 SQL 语句。

E. SpringBoot 及其生态：包括但不限于 SpringBoot, Maven, Swagger, Lombook 等。

F. HTML & CSS：包括但不限于 HTML5, CSS 及现代化 Web 构建技术如 SCSS, LESS 等。

G. JavaScript & Node.js：包括但不限于 JavaScript 和 Node 相关的框架及第三方依赖。

H. vue.js 及其生态：包括但不限于 vue.js, vuex 及 vuetify, bootstrap 等 UI 框架。

对于开发团队中的不同角色，对应的培训内容如下：

| 角色                 | 维护成员 | 前端开发 | 后台开发 |
| -------------------- | -------- | -------- | -------- |
| Git                  | √        | √        | √        |
| SRE                  | √        |          |          |
| Linux 环境           | √        | √        | √        |
| API 设计             |          |          | √        |
| 数据库设计           | √        |          | √        |
| SpringBoot 及其生态  |          |          | √        |
| HTML & CSS           |          | √        |          |
| JavaScript & Node.js |          | √        |          |
| vue.js 及其生态      |          | √        |          |

