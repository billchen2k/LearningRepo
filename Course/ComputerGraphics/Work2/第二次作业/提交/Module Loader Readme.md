# Module Loader Readme

> 10185101210 陈俊潼, East China Normal University.

### 简介

本程序可以使用1.dat和2.txt内的数据加载出3D模型，浏览并调整光照、视角等。

程序使用`C# .Net Framework 4.5`，OpenGL使用库`SharpGL`链接。

### 主要功能

![](C:\Users\billc\Desktop\Module Loader Readme.assets\image-20191201151506627.png)

- 加载模型
- 可渲染坐标轴、点云、环境光、散射光、镜面光
- 可以自定义渲染内容
- 自动旋转视角
- 日志记录渲染时间

### 使用方法

数据文件 1.dat 和 2.txt 应当和程序放在同一个目录下。

使用 Render All 选项可以渲染所有内容， Render Dots Only 只渲染云点和坐标轴，Render Surfaces With Light 渲染光照和 3D 模型的混合。也可以直接在上面勾选需要渲染的内容。

勾选 Enable Auto Rotation 可以让模型自动绕 y 轴旋转。

![image-20191201152538066](C:\Users\billc\Desktop\Module Loader Readme.assets\image-20191201152538066.png)

取消勾选 Clear Before Repaint 可以在每一次渲染前不清空深度缓存，保留上一次的渲染数据。

Reset 选项将会清空画布并将视角重置为一个比较合适的初始值，重新调整窗口大小也会重新加载画布清空缓存。

---

*2019.12.1*
*https://billc.io*