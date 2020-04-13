## Python 基础作业 3

预计编程耗时约 1 h。

### 需要了解

- 了解 requests, lxml, json 库（和爬虫相关）
- 了解网页请求大概是在干什么
- 了解 API 是什么
- 了解网页请求中的 header, 参数, cookie, session 的概念
- 了解网页请求的两个主要方法：GET 和 POST
- 了解如何从网页请求的结果中解析数据（这次的返回格式是 json）
  
### 要求

从腾讯音乐的流行排行榜 API 抓取 2020 年 3 月每天的前 10 名的歌曲名、专辑名、歌手名，将结果保存为 output.xlsx 文件。

腾讯音乐排行榜 API：

网页链接：
https://c.y.qq.com/v8/fcg-bin/fcg_v8_toplist_cp.fcg?date=2020-03-01&topid=4&type=top&song_begin=%7B%7D

整理地址和参数到 python 中：
```
url = 'https://c.y.qq.com/v8/fcg-bin/fcg_v8_toplist_cp.fcg'

parameters = {
	'date': '2020-03-01',
	'topid' : 4,
	'type': 'top',
	'song_begin': '{}'
}
```

### 示例格式

| 日期 \ 排名  | 1   | 2   | ... | 10  |
| ----------- | --- | --- | --- | --- |
| 2020-03-31  | xxx | xxx | ... | xxx |
| 2020-03-30  | xxx | xxx | ... | xxx |
| ...         | ... | ... | ... | ... |
| 2020-03-01  | xxx | xxx | ... | xxx |

其中，xxx = 歌手 - 歌曲名（专辑名）

