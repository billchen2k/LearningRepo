import requests
import time
import hashlib

id = 10185101210
name = "陈俊潼"

# id = 10185101208
# name = "曾琨伦"

# res = requests.put("https://anti-epidemic.ecnu.edu.cn/clock/record", json={
#     "number": id,
#     "location": "在学校",
#     "health": "健康，未超过37.3",
#     "recordTime": int(time.time() * 1000),
#     "token": hashlib.md5(f"{name}{id}ecnu1024".encode()).hexdigest()
# }).json()

res = requests.put("https://anti-epidemic.ecnu.edu.cn/clock/mini/record", json={
    "number": id,
    "location": "在学校",
    "health": "健康，未超过37.3",
    "recordTime": int(time.time() * 1000),
    "token": hashlib.md5(f"{name}{id}ecnu1024".encode()).hexdigest()
}, headers={
    "MiniToken": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJudW1iZXIiOiIxMDE4NTEwMTIxMCIsImlzcyI6IkVDTlUiLCJuYW1lIjoi6ZmI5L-K5r28IiwiZXhwIjoxNjA3OTIwNjY3fQ.9ss_dWFiEZAiqh65URyfGCAJcPG2F1FfNFGV4fb_cBg"
}).json()

print(res)