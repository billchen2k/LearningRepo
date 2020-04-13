## Python 基础作业 1

预计编程耗时约 15 min。

### 需要了解

- 在 python 中导入包
- 使用 `conda` 或 `pip` 命令安装第三方包
- python 文件读写
- 文件编码 *（为了保证跨平台和协作时的完整性，通常在程序中使用的编码都是 `utf-8`）*
- 了解一下 [Python 代码规范](https://zh-google-styleguide.readthedocs.io/en/latest/google-python-styleguide/python_style_rules/) （仅供参考）
  
### 要求

- 定义一个名为 `print_and_save()` 的函数，打印一次当前的日期时间，并把输出追加保存到编码为 `utf-8` 的文本文件 output.txt 中。每秒调用一次函数，60s 后停止并自动退出。
- 文件应当保存在脚本运行目录下的 output/ 文件夹下。如果该文件夹不存在，应当先创建。

### 输出格式

XXXX 年 XX 月 XX 日 XX 时 XX 分 XX 秒