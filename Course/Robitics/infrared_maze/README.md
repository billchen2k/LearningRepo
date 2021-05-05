# blackTornadoRobot红外走迷宫功能
走迷宫功能包，可通过红外传感器数据使小车在迷宫中行进。

在param.yaml文件中可调整一些走迷宫时用到的参数。

小车走迷宫的主要逻辑为：将迷宫看作由50cmX50cm方格添加障碍墙之后组成的环境，小车每次行进皆为50cm即行走一格，转弯角度为90度。小车每行进一格后会获取当前红外传感器数据，优先左转，其次直行，最后右转。

### 建图运行方法
首先启动小车

```sh
$ roslaunch robot_bringup robot_bringup.launch
```

然后运行走迷宫程序
```sh
$ roslaunch infrared_maze infrared_maze.launch
```

