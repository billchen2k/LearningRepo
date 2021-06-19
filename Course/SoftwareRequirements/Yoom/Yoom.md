# Yoom Meetings 在线音视频会议系统

**软件需求文档 / Software Requirements Specification**

> 10185101210 陈俊潼

[toc]

## 简介 / Introduction

### 愿景 / Purpose

Yoom Meetings 是一套高性能、高效、创新、安全的多人会议协作系统。后疫情时代，网上协作、远程办公成了大量中小企业的趋势，Work From Home 的流行也让音视频会议成为了企业推进工作必不可少的环节。Yoom Meetings 提供了一套高可用的可靠的会议系统。Yoom Meetings 支持多端入会、会中特效、字幕翻译，同时也针对企业会议室应用提供了整体解决方案，包括 Yoom 会议室的功能，兼容传统视频会议的 SIP 协议连接，支持主流视频会议品牌设备接入 Yoom 音视频会议。本音视频会议系统旨在提高远程协作的流程，提供流畅的音视频会议体验，为各体量的有音视频会议需求的企业提供可靠优质的解决方案。

Yoom Meetings 希望助力组织和个人更高效、更流畅、更满意。

### 范围 / Scope

Yoom Meetings 针对从数十人的小型团队到上万人的大型高校、企业都提出了安全可靠的解决方案，我们将处理音视频会议从发起、会中再到会议结束的过程中的所有过程。为了提供流畅的入会流程，提供了使用 ID 入会、链接入会和 PSTN 入会等多种解决方案；在会中为主持人和联席主持人提供了细粒度的权限管理方案和权限控制；在会后提供了详细的会议参会情况记录与聊天记录回顾，方便主持人回顾会议内容。

本系统的系统关联图如下：

![Context Diagram](YoomMeetings/Context%20Diagram.png)

### 术语定义 / Definition

| 术语          | 英文全称                          | 含义                                                         |
| ------------- | --------------------------------- | ------------------------------------------------------------ |
| RTC           | Real Time Conference              | 实时音视频，本系统提供高并发、低延迟、高清流畅、安全可靠的音视频服务。 |
| SIP           | Session Initiation Protocol       | 会话初始协议，由IETF（Internet Engineering Task Force，因特网工程任务组）制定的多媒体通信协议。 它是一个基于文本的应用层控制协议，用于创建、修改和释放一个或多个参与者的会话。 |
| PSTN          | Public Switched Telephone Network | 公共交换网络，使用电话号码邀请参会人拨入会议的协议           |
| VC            | Video Conference                  | 视频会议系统                                                 |
| PB            | Protocol Buffers                  | 约定接口和相关数据结构的数据描述语言                         |
| App Container | -                                 | App的容器，每个独立的App都需要有一个 App Container 来实现自己的 Container，包括 apis、UI-SDK、PageManager |
| YM-SDK        | -                                 | 包含底层 C++ 能力，视频会议所使用的 RTC SDK.                 |
| YM-Core       | -                                 | 包视频会议的核心业务逻辑，会被多个App复用。运行于App Container内。包括：<br />- UI-SDK：包含 UI 部分的外部 SDK 封装<br />- 状态机：视频会议所使用的状态机<br />- Page-Manager：界面管理及界面容器 |

### 角色定义 / Actors

系统中的角色主要区分成了以下四类：

| 角色名称        | 职责描述                                                     |
| --------------- | ------------------------------------------------------------ |
| Host            | 会议主持人，具备结束会议、管理成员、转移主持人权限、终止会议、禁音所有参会者、修改入会权限或取消禁音所有参会者等最高权限，主持人只能有一人 |
| Co-Host         | 联席主持人，联席主持人可以具有多人，具备主持人除转移主持人以外的所有权限，协助管理会议状态和入会这信息 |
| Participant     | 会议的参与者，可以控制自己的会议状态和离开会议，无法对其他人的状态做出修改或终止本会议 |
| Non-Participant | 会议的非参与者，指准备加入会议的用户，可以通过 PSTN、会议 ID、会议链接加入会议。包括未进入会议室的用户和在会议室等候（如需要）的用户。 |

### 概览 / Overview

#### 状态机

Yoom 对每个参会者维持了一个状态机，用户指示当前用户的状态。

`YMCORE-STATEMACHINE`：状态机图

![State Machine](YoomMeetings/State%20Machine.png)

各状态含义如下：

| State     | 含义                                     |
| --------- | ---------------------------------------- |
| IDLE      | 空闲状态，未进入会议的待命状态           |
| CALLING   | 当用户**呼叫**其他用户时，弹出的呼叫页面 |
| RINGING   | 当用户**被叫**时，弹出的被叫页面         |
| ONTHECALL | 处在会议中的状态                         |

#### 状态迁移接口

- `invite` 正常情况下的 1v1 会议或多人会议的邀请操作
- `joinMeeting `正常情况下
  - 1v1会议：在服务端创建会议成功，并且对方接听，然后进入 ON_THE_CALL
  - 多人会议：在服务端创建会议成功，然后进入 ON_THE_CALL
- `cancelInvitation `取消 1v1 会议邀请
- `receiveInvitation` 收到邀请，进入 Ringing 状态
- `refuseInvitation` Ringing 状态拒绝邀请
- `resetInvitation`
  - CALLING状态下：重置会议 1v1 会议或多人会议的邀请，一般用于创建会议失败等等意外情况
  - RINGING状态下：重置会议 1v1 会议或多人会议的邀请，一般用于创建会议失败等等意外情况
- `acceptInvitation` 用户点击操作接受按钮，接受邀请并进入 ON_THE_CALL
- `forceAcceptInvitation` 用户先收到了 Yoom 多人会议的 RINGING 推送，然后通过提示加入相同会议
- `forceInvite1v1` 跨设备切换到 1v1 会议，具体情况是：别的设备在会中，本设备发起 1v1 会议。会先弹出确认框，确认后后端直接下发状态然后进入 CALLING 状态
- `recoveryMeeting` 客户端整体意外 crash 并重启之后，会自动恢复多人会议
- `forceJoinMeeting` 通过卡片进入 Yoom 多人会议，并加入会议的操作
- `previewJoinMeeting` 通过卡片进入自研 SDK 的多人会议，打开预览界面，然后点击加入会议的操作
- `hangup`
  - 主动挂断会议（结束会议 / 自己离开会议）
  - SDK 报错或者加入会议失败导致了离开会议
  - 当参会者申请加入另一个会议时，强制离开当前会议
- `terminate`
  - 被踢出会议
  - 1v1 会议对方断线或离开
  - 其他情况下，服务端下发了IDLE状态会自动退出会议
- `rejoin`
  - 在 SDK 重连失败后，用户点击重新加会，调用 `rejoinVideoChat` 来重新进入会议

## 业务需求 / Solutions

系统用例图如下图所示：

![Use Case Diagram](YoomMeetings/Use%20Case%20Diagram.png)

业务需求命名规范如下表所示：

| 前缀 | 含义                                 | 规则        | 示例                     |
| ---- | ------------------------------------ | ----------- | ------------------------ |
| YM1  | 核心需求，和通话流程强相关           | YM1001 递增 | YM1001：1v1 通话         |
| YM2  | 次核心需求，和通化流程弱相关         | YM2001 递增 | YM2001：会中参会人员管理 |
| YM3  | 额外功能需求，增强用户体验的额外需求 | YM3001 递增 | YM3001：实时字幕         |
| YM4  | 补充需求，可以暂时忽略的需求         | YM401 递增  | N/A                      |

### YM1001：1v1 通话

#### 用户界面

#### 时序图

`YM1001-SQ00: 1v1_start_invitation`：发起 1v1 邀请

![00_1v1_start_invitation](Sequence%20Diagram/00_1v1_start_invitation.png)

`YM1001-SQ01: 1v1_invitation_fail`：1v1 邀请失败：

![01_1v1_invitation_fail](Sequence%20Diagram/01_1v1_invitation_fail.png)

`YM1001-SQ02: 1v1_accept_invitation`：1v1 通话接受邀请：

![02_1v1_accept_invitation](Sequence%20Diagram/02_1v1_accept_invitation.png)

`YM1001-SQ03: 1v1_cancel_invitation`：1v1 通话取消发起邀请：

![03_1v1_cancel_invitation](Sequence%20Diagram/03_1v1_cancel_invitation.png)

`YM1001-SQ04: 1v1_hang_over`：1v1 通话挂断（任意一方）：

![04_1v1_hang_over](Sequence%20Diagram/04_1v1_hang_over.png)

#### 需求描述

- 1v1，即 1 participant VS 1 participant，不同用户之间应当能直接向对方发起 1v1 通话邀请。
- 发起方可以使用对方的用户名、邮箱、手机号来发起 1v1 通话。
- 会前，非参会者可以使用对方的邀请链接、会议 ID 或通过接听 PSTN 电话来加入会议。
- 在 1v1 会议中，任意一方挂断会议，即视为会议终止，双方的连接断开。
- 被叫方
  - 如果正处在 IDLE 状态，则直接发起被叫信息；
  - 如果处于 ONTHECALL 状态，则先向被叫方询问是否挂断当前通话，再加入会议。
- 呼叫方
  - 如果正处于 IDLE 状态，则直接发起呼叫信息；
  - 如果正处于 NvN 会议的 ONTHECALL 状态，则询问呼叫方是否离开（作为 Participant）或结束（作为 Host 或 Co-Host）当前会议，并发起呼叫。
- 1v1 通话的用户体验应当类似直接拨打电话，但该方式发起的会议中途可以再次邀请更多参会者进入会议。更多参会者参与会议后，该会议由 1v1 会议升级为 NvN 会议。升级为 NvN 会议后，会议无法再降级为 1v1 会议。

#### 用例描述

该需求涉及到的用例主要有 Join Meeting By PSTN，Join By 1v1 Invitation，Start 1v1 Call。

##### Join Meeting By PSTN

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Join Meeting By PSTN                                         |
| Actors           | Non-participant, Host                                        |
| Pre-condition    | 用户应当正确登录进了系统；<br />用户应当被 Host 通过 PSTN 邀请通过电话拨入会议；<br />STATE == IDLE \|\| STATE == ONTHECALL |
| Post-condition   | Non-participant 被 Host 邀请进该会议，STATE == ONTHECALL     |
| Main Flow        | Non-participant 收到电话邀请，手机电话响铃<br />Non-participant 接受电话邀请，进入会议 |
| Alternative Flow | Non-participant 收到电话邀请，手机电话响铃<br />Non-participant 挂断电话，邀请失败。 |
| Exception        | None                                                         |

##### Join Meeting By 1v1 Invitation

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Join Meeting By Link                                         |
| Actors           | Non-participant, Host                                        |
| Pre-condition    | 用户应当正确登录进了系统；<br />Non-participant 拥有了 1v1 通话的邀请链接<br />STATE == IDLE \|\| STATE == ONTHECALL |
| Post-condition   | Non-participant 被 Host 邀请进该会议，STATE == ONTHECALL     |
| Main Flow        | Non-participant 打开链接，进入会议                           |
| Alternative Flow | 1.<br />Non-participant 当前正在另一个会议，并打开了链接：<br />Non-participant 选择是否接受会议邀请，如果接受邀请，则退出当前会议，并加入新的会议<br />如果拒接邀请，则忽略该邀请，用户继续在原会议进行通话<br /><br />2.<br />该会议设置了入会权限，需要在等候室确认主持人进入会议系统之后再加入会议。<br />如果主持人允许加入会议，则进入会议，否则会议终止 |
| Exception        | None                                                         |

##### Start 1v1 Call

`YM1001-ST00: start_1v1_call`：该用例对应的状态转换图：

![Flow - Start 1v1 Call](YoomMeetings/Flow%20-%20Start%201v1%20Call.png)

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Start 1v1 Call                                               |
| Actors           | Non-participant，Host                                        |
| Pre-condition    | 用户应当正确登录进了系统；<br />用户应当具备发起会议的权限；<br />STATE == IDLE |
| Post-condition   | 用户成为 Host，同时开始了一个新的会议<br />NEW_STATE == ONTHECALL |
| Main Flow        | Host 找到需要发起 1v1 会议的目标角色，并对其发起通话请求，STATE == CALLING<br />Non-participant 找到对方等待对方接受请求 |
| Alternative Flow | 如果 Non-participant 当前正在另一个会议，处于 ONTHECALL 状态：<br />Non-participant 选择是否接受会议邀请，如果接受邀请，则退出当前会议，加入新的会议<br />如果拒接邀请，则忽略该邀请，用户继续在原会议进行通话<br /> |
| Exception        | 如果无法联系上被叫方，则抛出错误 CANNOT_REACH_CALLEE，提示呼叫方并记录错误信息<br />被叫方上线后将得到未接听来电的信息 |

### YM1002：NvN 通话

#### 用户界面

#### 时序图

`YM1002-SQ01: nvn_start_invitation`：NvN 通话发起邀请：

![05_nvn_start_invitation](Sequence%20Diagram/05_nvn_start_invitation.png)

`YM1002-SQ02: nvn_invitation_fail`：NvN 通话邀请失败：

![06_nvn_invitation_fail](Sequence%20Diagram/06_nvn_invitation_fail.png)

`YM1002-SQ03: nvn_accept_invitation`：NvN 通话接受邀请：

![07_nvn_accept_invitation](Sequence%20Diagram/07_nvn_accept_invitation.png)

`YM1002-SQ04: nvn_refuse_invitation`：NvN 拒绝通话邀请：

![08_nvn_refuse_invitation](Sequence%20Diagram/08_nvn_refuse_invitation.png)

`YM1002-SQ04: nvn_refuse_invitation`：NvN 通话主持人离开会议，并移交主持人权限：

![09_nvn_leave_meeting](Sequence%20Diagram/09_nvn_leave_meeting.png)

`YM1002-SQ04: nvn_refuse_invitation`：NvN 通话结束会议，并解散所有参会者：

![10_nvn_end_meeting](Sequence%20Diagram/10_nvn_end_meeting.png)



#### 需求描述

- NvN，即 N participants VS N participants，通话需要让用户发起或加入一个多人会议
- 会前，发起方可以通过选择参会者的的用户名、邮箱、手机号等来发起 NvN 通话，这些参与者都将进入 CALLING 状态，而发起者无需等待，直接进入会议，成为 Host 并进入 ONTHECALL 状态
- 会前，非参会者可以使用对方的邀请链接、会议 ID 或通过接听 PSTN 电话来加入会议。
- 在 NvN 会议中，Host 可以同时支持 10000 个总参会人进入会议，其中同时打开上传视频流的用户应当支持有 500 位，同时打开上传音频流的用户应当支持有 100 位。
- 在 NvN 会议中，Host 有且只能有一位，Co-Host 可以有多位，由 Host 提名。Participant 可以有多位。具体见需求会中人员管理（YM2001）。
- 被叫方呼叫时：
  - 如果正处在 IDLE 状态，则直接发起被叫信息；
  - 如果被叫方处于 ONTHECALL 状态，则先向被叫方询问是否挂断当前通话，并确认加入会议。
- 呼叫方如果正处于 IDLE 状态，则直接发起呼叫信息；如果呼叫方正处于 NvN 会议的 ONTHECALL 状态，则询问呼叫方是否离开（作为 Participant）或结束（作为 Host 或 Co-Host）当前会议，并发起呼叫。
- 在 NvN 会议中，用户的离开会议行为做如下定义：
  - Participant 离开会议后不影响，继续进行。
  - Co-Host 离开会议时可选择结束会议或离开会议。
    - 选择离开会议后会议继续进行
    - 选择结束会议后会议直接结束，中断所有参会者的连接
  - Host 离开会议时可选择结束会议或离开会议。
    - 选择离开会议后，必须保证会议至少剩下 1 人，并将 Host 权限转移给其他 Co-Host 或 Participant，会议继续正常进行。如果 Host 为会议中的最后一个参会者，离开会议行为和结束会议行为定义相同。
    - 选择结束会议后会议直接结束，中断所有参会者的连接

该需求涉及到的主要用例有 Join Meeting By PSTN, Join Meeting By Meeting ID, Join Meeting by Meeting Link, Start NvN Meeting。

#### 用例描述

##### Join Meeting By PSTN

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Join Meeting By PSTN                                         |
| Actors           | Non-participant, Host                                        |
| Pre-condition    | 用户应当正确登录进了系统；<br />用户应当被 Host 通过 PSTN 邀请通过电话拨入会议；<br />STATE == IDLE \|\| STATE == ONTHECALL |
| Post-condition   | Non-participant 被 Host 邀请进该会议，STATE == ONTHECALL     |
| Main Flow        | Non-participant 收到电话邀请，手机电话响铃<br />Non-participant 接受电话邀请，进入会议 |
| Alternative Flow | Non-participant 收到电话邀请，手机电话响铃<br />Non-participant 挂断电话，邀请失败。 |
| Exception        | None                                                         |

##### Join Meeting By NvN Link

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Join Meeting By NvN Link                                     |
| Actors           | Non-participant, Host                                        |
| Pre-condition    | 用户应当正确登录进了系统；<br />Non-participant 拥有了 1v1 通话的邀请链接<br />STATE == IDLE \|\| STATE == ONTHECALL |
| Post-condition   | Non-participant 被 Host 邀请进该会议，STATE == ONTHECALL     |
| Main Flow        | Non-participant 打开链接，进入会议                           |
| Alternative Flow | 1.<br />Non-participant 当前正在另一个会议，并打开了链接：<br />Non-participant 选择是否接受会议邀请，如果接受邀请，则退出当前会议，并加入新的会议<br />如果拒接邀请，则忽略该邀请，用户继续在原会议进行通话<br /><br />2.<br />该会议设置了入会权限，需要在等候室确认主持人进入会议系统之后再加入会议。<br />如果主持人允许加入会议，则进入会议，否则回到之前的状态（IDLE 或 ONTHECALL） |
| Exception        | None                                                         |

##### Start NvN Call

`YM1002-ST00: start_nvn_call`：该用例对应的状态转换图：

![Flow - Start NvN Call](YoomMeetings/Flow%20-%20Start%20NvN%20Call.png)

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Start NvN Call                                               |
| Actors           | Non-participant，Host                                        |
| Pre-condition    | 用户应当正确登录进了系统；<br />用户应当具备发起会议的权限；<br />STATE == IDLE \|\| STATE == ONTHECALL |
| Post-condition   | 用户成为 Host，同时开始了一个新的会议<br />收到邀请的用户发起被邀请通知，根据状态<br />NEW_STATE == ONTHECALL |
| Main Flow        | Host 选择参会人，并向参会人发起请求，STATE == CALLING<br />Non-participant 处于 IDLE 状态收到请求，接受请求并加入会议，或拒绝请求，回到 IDLE 状态。 |
| Alternative Flow | 1.如果 Non-participant 当前正在另一个会议，处于 ONTHECALL 状态：<br />Non-participant 选择是否接受会议邀请，如果接受邀请，则退出当前会议，加入新的会议<br />如果拒接邀请，则忽略该邀请，用户继续在原会议进行通话<br /> |
| Exception        | 如果无法联系上被叫方，则抛出错误 CANNOT_REACH_CALLEE，提示呼叫方并记录错误信息<br />被叫方重新上线后将得到未接听来电的信息 |

### YM2001：会中权限管理

#### 用户界面

#### 需求描述

- 为了满足不同场景下会议视频的需求，Yoom 支持用户粒度的权限控制，支持针对会议中的不同人员设置不同的权限，确保会议稳定有序地进行。
- 在 NvN 会议中，Host 有且只能有一位，Co-Host 可以有多位，由 Host 提名。Participant 可以有多位。
- Host 默认为发起的人员，具备会议的所有控制权限。包括结束会议、邀请成员、转移主持人、设置联系主持人、移除参会者、禁音 / 取消禁音所有参会者、加入其他会议、更改会议权限级别、开启字幕、开启特效等。
- Host 可以在任意时候自己的权限转移给任意成员，转移之后自己将降级为 Co-Host。为了避免误操作，Host 在转移之后的 1 分钟之内可以选择收回 Host 权限，收回权限后之前被授予 Host 权限的人将恢复原先的权限登记。
- Host 可以将任意成员提升为 Co-Host，Co-Host 具备和 Host 相同的权限，除了设置其他 Co-Host 和移除角色为 Host 或 Co-Host 的成员。
- Participant 具备会议的基本权限，不具备移除成员的权限，但可以邀请其他参会者加入会议。
- Non-participant 只能申请加入会议。

权限决策表如下表所示：

| 权限                   | 定义                    | Host | Co-Host | Participant | Non-participant |
| ---------------------- | ----------------------- | ---- | ------- | ----------- | --------------- |
| 结束会议               | PERM_END_MEETING        | √    | √       |             |                 |
| 离开会议               | PERM_LEAVE_MEETING      | √*   | √       | √           |                 |
| 邀请成员               | PERM_INVITE             | √    | √       |             |                 |
| 设置主持人             | PERM_SET_HOST           | √    |         |             |                 |
| 设置联席主持人         | PERM_SET_COHOST         | √    |         |             |                 |
| 移出参会者             | PERM_KICK_PARTICIPANT   | √    | √       |             |                 |
| 禁音所有参会者         | PERM_MUTE_ALL           | √    | √       |             |                 |
| 申请取消禁音所有参会者 | PERM_UNMUTE_ALL         | √    | √       |             |                 |
| 加入会议               | PERM_TRY_JOIN           | √    | √       | √           | √               |
| 更改会议入会权限级别   | PERM_SET_ENTRANCE_LEVEL | √    | √       |             |                 |
| 开关实时字幕           | PERM_SET_LIVE_CAPTION   | √    | √       | √           |                 |
| 开关自己会中特效       | PERM_SET_EFFECTS        | √    | √       | √           |                 |
| 开关所有人会中特效     | PERM_SET_ALL_EFFECTS    | √    | √       |             |                 |

*：主持人离开会议前，必须将自己的主持人权限转移给他人。如果主持人是会议中的最后一位参会者，则离开会议的行为和结束会议的行为相同。

#### 用例描述

该需求涉及到的用例有 Transfer Host Permission, Mute/Unmute All。

##### Transfer Host Permission

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Join Meeting By PSTN                                         |
| Actors           | Participant, Host                                            |
| Pre-condition    | 会议应当为 NvN 会议，1v1 会议中无主持人之分<br />要转移的用户必须为 Host<br />会议中的参会人员数应当 >= 2 |
| Post-condition   | Host 权限转移给新的用户                                      |
| Main Flow        | 原 Host 选择一个会议中的 Participant 或 Co-Host，将主持人权限转移 |
| Alternative Flow | 原 Host 因为误操作选择一个会议中的 Participant 或 Co-Host，将主持人权限转移<br />在误操作发生的一分钟内，原 Host 选择撤销转移权限<br />原 Host 重新拥有了主持人权限，新的用户恢复为转移前的权限 |
| Exception        | None                                                         |

##### Mute / Unmute All

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Mute/Unmute All                                              |
| Actors           | Host, Co-Host, Participant                                   |
| Pre-condition    | 发起静音或取消静音请求的人应当为 Host 或 Co-Host             |
| Post-condition   | 会中所有 Participant 受影响被静音或收到取消静音的请求        |
| Main Flow        | Mute All:<br />主持人选择 Mute All，并不允许参会人自行打开麦克风。<br />所有 Participant 麦克风立即关闭，Co-Host 和 Host 不受影响。<br />此后 Participant 不可再自行打开麦克风，否则需要向 Co-Host 和 Host 申请权限。<br /><br />Unmute All:<br />所有 Participant 收到申请取消静音的提示，Co-Host 和 Host 不受影响。<br />如果选择接受，则打开麦克风；如果选择拒绝，则继续关闭。此后 Participant 可以自行打开麦克风。 |
| Alternative Flow | Mute All:<br />主持人选择 Mute All，但允许参会人自行打开麦克风。<br />所有 Participant 麦克风立即关闭，Co-Host 和 Host 不受影响。<br />10 秒之后 Participant 可以再自行打开麦克风。 |
| Exception        | 如果有 Participant 网络状况不佳未收到消息：<br />服务端将在 Mute 后在恢复网络后重新发送静音 / Unmute 请求。 |

### YM2002：入会权限管理

#### 用户界面

#### 时序图

`YM2002-SQ01: lobby_participants`：等候室时序图：

![11_lobby_participants](Sequence%20Diagram/11_lobby_participants.png)

`YM2002-SQ02: lobby_waiters`：等候室参会人时序图：

![12_lobby_waiters](Sequence%20Diagram/12_lobby_waiters.png)

#### 需求描述及用例描述

- 为了保证会议内容的安全性，避免意外人员参与到会议中，为 Host 和 Co-Host 提供切换入会权限的能力。
- 对于任意 NvN 会议，有如下三种入会权限级别：

| 权限                   | 定义                        | 含义                                       |
| ---------------------- | --------------------------- | ------------------------------------------ |
| 允许所有人加入会议     | ENT_PERM_ALLOW_ALL          | 允许任何具备会议 ID 或会议链接的人加入会议 |
| 允许同组织加入会议     | ENT_PERM_ALLOW_ORGANIZATION | 仅允许同一组织的用户加入会议               |
| 仅允许邀请的人加入会议 | ENT_PERM_INVITE_ONLY        | 仅允许主持人和联系主持人通过邀请成员       |

- 在对应权限设置之后，该权限所对应的其他任意人员均无法进入会议。
- 在对应的劝下下，Host 和 Co-Host 还可以开启会议等候室功能。
  - Host 和 Co-Host 在会议中始终可以将参会者「移入等候室」；
  - Host 和 Co-Host 可以在会议中选择是否设置「将入会范围受限的新参会方置于等候室」
  - 该功能仅影响新加入会议的参会方；
  - 当 Host 和 Co-Host 设置该功能时，满足入会权限的用户在新加入会议时直接进入会议，不满足入会权限的用户加入时会自动进入等侯室；
  - 当 Host 和 Co-Host 未设置该功能时，满足入会权限的用户直接进入会议，不满足入会权限的用户无法加入会议；
- 等候室功能与入会方式的联动：
  - 主持人可呼叫所有用户加入会议；
  - 仅设置入会权限，未设置「入会受限用户新加入会议时置入等候室」处理逻辑：
    - 满足入会权限的参会者可以直接进入会议，不满足入会权限的无法加入会议；
    - 会议中的参会者可成功呼叫符合入会范围的用户；无法呼叫入会受限用户；
- 对主持人而言，还有以下功能：
  - 准入：准入单次生效，该参会者将从等候室页面进入会议中；
  - 移出：
    - 移出等候室单次生效；
    - 主持人点击移出，给予主持人弹窗确认是否移出，文案：确认将{name}移出等候室？确认/取消；
    - 该用户从等候室中弹出。给予弹窗提示，文案：“主持人已将你移出会议”；
    - 该用户被移出后，再次加入会议时如果依然不符合当前的入会范围，则进入等候室；
  - 全部准入：
    - 当前等候室人员 >= 2人时有此功能；
    - 等候室中所有用户按照进入等候室的先后顺序依次进入会议中；
    - 等候室+会议中的人数超过了会议允许的人数上限，主持人「全部准入」，将人数上限内的用户准入会议，其余的保留在等候室；
      - 等候室list按照进入的先后顺序排列，最新进入等候室的位于list顶部，同时提示主持人：已超出会议人数上限，其他用户将继续留在等候室；
  - 查看人员详情：打开参会人panel对等候室中的成员进行操作；

会议等候室的流程图如下图所示：

![Flow - Lobby](YoomMeetings/Flow%20-%20Lobby.png)

#### 用例描述

与该需求相关的 Use Case 有 Enter Waiting Lobby, Manage Waiting Participants。

##### Transfer Host Permission

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Enter Waiting Lobby                                          |
| Actors           | Non-participant                                              |
| Pre-condition    | Non-participant 处于 IDLE 状态<br />申请进入的会议室开启了等候室功能<br />Non-participant 不具备直接进入该会议的权限 |
| Post-condition   | Non-participant 进入等候室<br />STATE = ONTHECALL            |
| Main Flow        | 申请加入会议者直接通过会议 ID 或会议链接申请加入会议，进入等候室<br />会议 Host 和 会议 Co-Host 收到提醒，并可以对等候室中的参会者进行管理 |
| Alternative Flow | None                                                         |
| Exception        | None                                                         |

##### Manage Waiting Participants

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Manage Waiting Participants                                  |
| Actors           | Host, Co-Host, Participant                                   |
| Pre-condition    | 等候室中有 >= 1 位处于等候状态的参会者                       |
| Post-condition   | 等候室中的参会者被移除等候室或被允许进入到等候室             |
| Main Flow        | Permit Entrance：<br />准入单次生效，该参会者将从等候室页面进入会议中；<br /><br />Remove：<br />移出等候室单次生效，主持人点击移出，确认后该用户从等候室中弹出。<br />该用户被移出后，再次加入会议时如果依然不符合当前的入会范围，则再次进入等候室。<br /><br />Permit All:<br />当前等候室人员 >= 2人时，等候室中所有用户按照进入等候室的先后顺序依次进入会议中 |
| Alternative Flow | Permit All:<br />当前等候室人员 >= 2人时，如果等候室与会议中的人数超过了会议允许的人数上限，<br />则准入后将人数上限内的用户准入会议，其余的保留在等候室。 |
| Exception        | None                                                         |

### YM3001：实时字幕

#### 用户界面

#### 需求描述

- 在相同语言开会场景下，对于会中说过的话能有记录，可以在任意参会者随时分神后继续参与会议，同时也能为后续回顾功能提供回顾参考。在用户想旁听会议，但无法开启扬声器、没有耳机的时候，可以透过字幕观看会议事实发生的内容。
- 在 NvN 会议中，Host，Co-Host 和 Participant 均有权限开启实时字幕功能。
- 实时字幕开启方式：
  - 从更多操作里开启
  - 第一次开启字幕默认显示语言为应用语言
  - 点击开启后，给予字幕开启中的提示，直到第一个字幕出现方算开启成功
  - 开启失败，给予用户提示，同时按钮设置为关闭状态
- 字幕显示方式：
  - 打开字幕失败后，给予用户toast提示。如果最后一句话出现后过一分钟还没有人说话字幕消失，只留历史字幕。在长时间无人说话情况，视图实时字幕区不显示任何字幕
  - 视图字幕区字幕最大显示行数依据后续反馈进行调整，且文本内容不可选中。
- 提供字幕历史回顾：
  - 在第一句字幕显示出来之后，具备可以点击入口通往字幕历史，字幕历史的显示内容依据不用的设备提供不同的维度。点击进入字幕历史后，可针对字幕显示进行设定，设定只会影响改动后的字幕，不对已经有的字幕造成影响。
  - 字幕历史中的内容同样不可选中。
- 默认开启字幕配置：
  - 用户开启后，每次进入 1v1 会议或者 NvN 会议都默认开启字幕功能，记忆在用户的设备上。开启/关闭不影响当前会议字幕显示。
- 预计需要支持 150 - 200 个会议的并发，服务端应当能够同时支撑这些数量的实时字幕转写。
- 实时字幕可以**在经过用户同意之后**收集用户经过脱敏处理的语音信息和识别出来的字幕信息，以供后续提高字幕转写识别的准确度。

该过程的流程图如下图所示：

![Flow - Transcript](YoomMeetings/Flow%20-%20Transcript.png)

#### 用例描述

该需求涉及到的 Use Case 有 Enable/Disable Transcript。

##### Enable / Disable Transcript

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Enable / Disable Transcript                                  |
| Actors           | Host, Co-Host, Participant                                   |
| Pre-condition    | 申请者应当在 NvN 会议中，且所在组织具备开启实时字幕的能力。  |
| Post-condition   | 会议将会开始实时转写字幕，并提供字幕历史回顾。               |
| Main Flow        | Enable Transcript:<br />如果用户是第一次开启功能，询问用户是否允许手机数据以用于训练模型提升转译效果。<br />无论用户拒绝还是接受，都直接开启实时字幕，开始准写<br /><br />Disable Transcript:<br />停止转译实时字幕，但仍然提供回顾历史字幕的功能。 |
| Alternative Flow | None                                                         |
| Exception        | 未能成功开启实时字幕：<br />上报错误，并向用户发送 toast 提示错误信息，尝试在 10 秒后再次开次，最多重试 3 次。 |

### YM3002：会中特效

#### 用户界面

#### 需求描述

#### 用例描述

与该需求相关的用例描述为 Enable / Disable Effects.

##### Enable / Disable Effects

| Key              | Value                                                        |
| ---------------- | ------------------------------------------------------------ |
| Use Case         | Enable / Disable Transcript                                  |
| Actors           | Host, Co-Host, Participant                                   |
| Pre-condition    | 申请者应当在 NvN 会议中，且所在组织具备开启实时字幕的能力。  |
| Post-condition   | 会议将会开始实时转写字幕，并提供字幕历史回顾。               |
| Main Flow        | Enable Transcript:<br />如果用户是第一次开启功能，询问用户是否允许手机数据以用于训练模型提升转译效果。<br />无论用户拒绝还是接受，都直接开启实时字幕，开始准写<br /><br />Disable Transcript:<br />停止转译实时字幕，但仍然提供回顾历史字幕的功能。 |
| Alternative Flow | None                                                         |
| Exception        | 未能成功开启实时字幕：<br />上报错误，并向用户发送 toast 提示错误信息，尝试在 10 秒后再次开次，最多重试 3 次。 |

## 系统属性 / System Attributes

### 可靠性 / Reliability

### 安全性 / Security

### 可用性 / Availability

### 可维护性 / Maintainability

## 外部系统限制 / Design Constraints

### 终端平台要求

#### 移动端

Yoom Meetings 安卓端最低适配到基于 Android 5.0 的设备，手机的分辨率不应低于 720x1080。最低的内存配置为 2GB，推荐的内存配置为 3GB 及以上。

iOS 端支持在 iOS 12.0 及以上的系统的所有苹果设备，包括：

| iPad       | iPhone                                                       | Apple Watch |
| ---------- | ------------------------------------------------------------ | ----------- |
| iPad<br /> | iPhone 7<br />iPhone 8<br />iPhone X<br />iPhone XS (Pro) (Max)<br />iPhone 11 (Pro) (Max)<br />iPhons 12 (Pro) (Max) (Mini)<br />iPhone SE 2020 | 暂未适配    |



PS. 暂时不兼容使用鸿蒙系统的华为终端手机设备，预计在 2021 年第四季度完成适配工作。

#### 桌面端

Yoom Meetings 的 Windows 端可在 Windows 7 及更高版本的系统上运行。目前已在 Windows 10 20H2 版本上测试通过，无运行异常。

最低配置要求：

- Intel Corel i3
- 4GB 运行内存
- 1280 x 720 分辨率

推荐配置要求：

- Intel Corel i3
- 8GB 运行内存
- 1280 x 720 屏幕分辨率

mac 端目前兼容了 macOS 10.11 及更高级的版本，在苹果 2014 年及之后发布的设备中可用。

#### 网页端

受限于浏览器 API 限制，Yoom Meetings 应当在以下浏览器上运行

| 系统    | Chrome | Firefox | Safari | Edge | Edge Chromium | Internet Explorer | Opera |
| ------- | ------ | ------- | ------ | ---- | ------------- | ----------------- | ----- |
| Windows | √      | √       | -      | √    | √             | ×                 | √     |
| Android | √      | √       | -      | -    | √             | -                 | √     |
| iOS     | √      | √       | √*     | -    | √             | -                 | √     |
| macOS   | √      | √       | √*     | -    | √             | -                 | √     |
| Linux   | √      | √       | -      | -    | -             | -                 | √     |

注：在使用 Yoom Meetings 之前，请将浏览器升级至最新版本。以上兼容性报告均在截止 2021 年 6 月 15 日前的最新版本上测试。

*：会中特效功能暂时无法在 Safari 浏览器上使用。


### 网络要求

#### 网络上行带宽要求

在 1v1 会议中，为了保证会议质量，使用 Yoom Meetings 系统的网络上行带宽需要满足下列需求：

| 场景     | 终端                 | 带宽要求              |
| -------- | -------------------- | --------------------- |
| 音频会议 | 移动端/桌面端/网页端 | 64 Kbps               |
| 视频会议 | 移动端               | 1 Mbps （高质量视频） |
| 视频会议 | 桌面端               | 3 Mbps （高质量视频） |
| 视频会议 | 网页端               | 2 Mbps （高质量视频） |
| 屏幕共享 | 移动端/桌面端/网页端 | 2 Mbps （高质量屏幕） |

备注：各终端在网络条件受限的情况下，Yoom 会自动调整带宽至 0.5 Mbps。

在 NvN 会议中，为了保证会议质量，使用

#### 网络下行带宽要求

为了保证会议质量，使用 Yoom Meetings 系统的网络下行带宽需要满足下列需求：

| 场景                  | 终端                 | 带宽要求                |
| --------------------- | -------------------- | ----------------------- |
| 音频会议              | 移动端/桌面端/网页端 | 192 Kbps                |
| 视频会议 - 宫格视图   | 移动端               | 0.5 Mbps （高质量视频） |
| 视频会议 - 缩略视图   | 移动端               | 0.5 Mbps （高质量视频） |
| 视频会议 - 宫格视图   | 桌面端               | 1 Mbps （高质量视频）   |
| 视频会议 - 缩略视图   | 桌面端               | 2 Mbps （高质量视频）   |
| 视频会议 - 演讲者视图 | 桌面端               | 3 Mbps （高质量视频）   |
| 视频会议 - 宫格视图   | 网页端               | 1 Mbps （高质量视频）   |
| 视频会议 - 缩略视图   | 网页端               | 2 Mbps （高质量视频）   |
| 视频会议 - 演讲者视图 | 网页端               | 3 Mbps （高质量视频）   |

备注：以上带宽要求为实现单流推送的最低网络要求，如要实现更高质量的会议或支持千方会议，需要将各项的带宽需求提升 3 倍，否则可能会出现性能问题或卡顿。



---

## 附录 / Appendix

### 修订记录 / Version Records

### V0.2



### V0.1

| Key      | Value                                       |
| -------- | ------------------------------------------- |
| 版本号   | 0.1                                         |
| 修订日期 | 2021-06-01                                  |
| 修订内容 | 初始版本发布                                |
| 需求影响 | 无                                          |
| 评审人   | @William Tester, @Charlie Tester            |
| 评审日期 | 2021-06-02                                  |
| 评审结果 | 通过                                        |
| 文件存档 | https://example.com/yoommeetings/sds0.1.pdf |

---

本需求文档基于在实习期间接触到的真实商业项目完成，出于商业保密要求，需求文档具体参数内容、系统名称等内容为合理范围内的的虚构，仅供满足课程考核需求。

陈俊潼 ·  2021 年 6 月

华东师范大学 · 软件工程学院
