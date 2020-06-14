## 🌲Tree Search Problem with OpenMPI

> East China Normal University
>
> 10185101210 陈俊潼, 2020.6.15

### 简介

本程序使用 OpenMPI 库实现了旅行商问题。三个程序的算法均为循环形式的暴力搜索 DFS。项目使用 macOS 编译，CPU 型号为 Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz。

包含三个程序、一个地图生成脚本和 `makefile`。这三个程序分别是：

- `tsp_serial.cpp` ：串行程序
- `tsp1.cpp`：每个进程一旦发现新的最佳回路后，要将最佳回路的代价发送给其他所有进程。
- `tsp2.cpp`：每个进程有自己的的本地最佳回路数据结构，直到它完成搜索为止。当所有的进程运行完后再调用一个全局归约操作找出最小代价回路。

### 使用方式

- 生成图： `python generater <node count>` ，用于生成具有 node count 城市的全连接双向图。
- 编译：`make`
- 运行串行程序：`make runs` 或 `./tsp_serial.cpp <graph file>`
- 运行并行程序 1 （广播剪枝）：`make run1` 或 `mpirun -np <node count> tsp1.cpp <graph file>`，其中 graph file 为图文件。
- 运行并行程序 2 （全局规约）：`make run2` 或 `mpirun -np <node count> tsp2.cpp <graph file>`，其中 graph file 为图文件。

### 运行结果对比

为了避免运行时间过长，截图展示的数据是 12 个节点的运行结果。

串行程序：

![image-20200615014016246](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-06-15-pOL4ph.png)

并行程序 1（广播剪枝）（部分输出已省略）：

![image-20200615014103947](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-06-15-MqSvNR.png)

并行程序 2（全局规约）：

![image-20200615014153743](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-06-15-NcGEi4.png)

尝试不同的节点数，对比结果如下：

| 节点数 | 串行           | 并行，广播剪枝 | 并行，全局规约 |
| ------ | -------------- | -------------- | -------------- |
| 4      | 0 ms           | 0 ms           | 0 ms           |
| 10     | 278 ms         | 12 ms          | 45 ms          |
| 12     | 29746 ms       | 121 ms         | 4331 ms        |
| 16     | $\infty$ | 18747 ms       | $\infty$ |

