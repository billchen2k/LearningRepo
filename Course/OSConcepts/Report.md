# PINTOS 实验报告

> 10185101210 陈俊潼

## 安装和配置

为了方便使用 VSCode 做实验，避免安装一个繁重 Ubuntu 虚拟机，便尝试直接在 macOS 上安装 pintos。使用的 pintos 来自：

[https://github.com/maojie/pintos_mac](https://github.com/maojie/pintos_mac)

下载后使用以下 port 命令安装依赖库、gdb和 bochs：

```bash
sudo port install i386-elf-binutils
sudo port install i386-elf-gcc
sudo port install sdl
sudo port install gdb # 用于调试，安装后需要使用命令 ggdb 调试
sudo port install bochs -smp +gdbstub
```

其中 `sudo port install bochs -smp +gdbstub` 后面的两个参数是为了开启 gdb 调试。因为 port 默认安装的 pintos 没有 --enable-gdb-stub 参数（可以通过查阅 port 的 variant 得到，如下图）。

![](Report.assets/image-20191205183338082.png)

为了能够直接输入 gdb 运行 ggdb，可以`vim ~/.bash_profile`，加入一行 `alias gdb='ggdb';`。

接着讲将 pintos 放入任意目录，在终端中将 utils 目录 export PATH:

```bash
# 后面的目录是 utils 所在的目录
export PATH=$PATH:~/OneDrive/Workspace/LearningRepo/Course/OSConcepts/pintos/utils
```

进入 threads 目录运行 make 后，可以尝试运行：

![](Report.assets/2019-12-05-09-44-33.png)

发现无法找到内核。修改 kernal.o 和 loader.o 的位置。在 /utils/pintos 的第 256 行：

![](Report.assets/2019-12-05-09-37-02.png)

/utils/pintos.pm 第 362 行：

![](Report.assets/2019-12-05-10-19-58.png)

/utils/pintos-gdb 第 4 行，调整GDBMACROS的目录：

![](Report.assets/2019-12-05-10-26-06.png)

接着测试调试。

输入命令

```bash
sudo pintos --gdb -s -- run alarm-multiple
```

新建终端，进入 threads/build 目录下输入命令：

```bash
ggdb kernel.o # 使用 port 安装的 mac 下的 gdb 应输入 ggdb
target remote localhost:1234
```

回到 Bochs 运行界面，可以发现已经连接成功：

![image-20191205120711836](Report.assets/image-20191205120711836.png)

这时已经可以在 gdb 中输入命令 `make check`查看检查信息，得到以下反馈：

```
(gdb) target remote localhost:1234
Remote debugging using localhost:1234
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x00000000 in ?? ()
(gdb) make check
pass tests/threads/alarm-single
pass tests/threads/alarm-multiple
pass tests/threads/alarm-simultaneous
FAIL tests/threads/alarm-priority
pass tests/threads/alarm-zero
pass tests/threads/alarm-negative
FAIL tests/threads/priority-change
FAIL tests/threads/priority-donate-one
FAIL tests/threads/priority-donate-multiple
FAIL tests/threads/priority-donate-multiple2
FAIL tests/threads/priority-donate-nest
FAIL tests/threads/priority-donate-sema
FAIL tests/threads/priority-donate-lower
FAIL tests/threads/priority-fifo
FAIL tests/threads/priority-preempt
FAIL tests/threads/priority-sema
FAIL tests/threads/priority-condvar
FAIL tests/threads/priority-donate-chain
FAIL tests/threads/mlfqs-load-1
FAIL tests/threads/mlfqs-load-60
FAIL tests/threads/mlfqs-load-avg
FAIL tests/threads/mlfqs-recent-1
pass tests/threads/mlfqs-fair-2
pass tests/threads/mlfqs-fair-20
FAIL tests/threads/mlfqs-nice-2
FAIL tests/threads/mlfqs-nice-10
FAIL tests/threads/mlfqs-block
20 of 27 tests failed.
make: *** [check] Error 1
```

确认环境配置完成，实验正式开始。

## Project 1

### 忙等待

修改内核的位置：

