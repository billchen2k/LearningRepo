## Python 基础作业 4 

预计编程耗时约 1.5 h。

### 需要了解

- **网页中的定位节点 xpath** （重要）
- 学会使用 Chrome 或其他浏览器的调试工具
- 更强大的爬虫库 Selenium 的安装和配置
- 给 Chrome 配置 Selenium 的方法
- ~~如何科学上网使用 Google 获取资料和文档~~
  
> 爬虫常用的几个路线：

1. requests 包发送单个链接+参数请求 -> lxml / BeautifulSoup 库解析节点
2. 对于相对复杂的请求爬取：requests 包使用 session，发送多个链接并保留 cookie + 参数请求 -> lxml / BeautifulSoup 库解析节点
3. 对于难顶的请求（动态加载、iframe 等），使用 selenuim 模拟真人访问 -> selinium / lxml / BeautifulSoup 解析节点内容

> selinium VS requesrs

- requests 是没有 GUI 的，直接封装参数、cookie 来模拟浏览器请求，大多数情况都可以用 requests 解决。主要缺点是对于动态加载的内容比较无力。
- selinium 本质上是一个虚拟的浏览器，模拟人类在网页中的点击。理论上可以应对任何爬虫需求。但占内存，且慢，能不用就不用。

  
### 要求

- 使用 requests 库， 在 IT 之家首页 ([https://www.ithome.com/](https://www.ithome.com/))中获取最近更新列表中的 5 页新闻链接：

![](https://tva1.sinaimg.cn/large/007S8ZIlgy1gds370opblj30k00500sv.jpg)

- 依次跳转到这 5 页新闻中，爬取他们的评论量。由于评论量是动态加载的，这里大概率需要使用到 selenium 框架。
  - 有可能不一定需要用到沉重的 selenuim 框架，可以检视网页请求，也许能够发现使用 requests 获取评论量的方式。
- 将前 5 页新闻的标题、链接、评论量按照评论量从高到低排序，输出至 output.csv 中。

### 示例格式

| No. | 标题 | 链接 | 评论量 |
| --- | ---- | ---- | ------ |
| 0   | xxx  | xxx  | ...    |
| 1   | xxx  | xxx  | ...    |
| 2   | xxx  | xxx  | ...    |
| ... | ...  | ...  | ...    |