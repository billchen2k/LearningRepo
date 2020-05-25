import requests
from lxml import etree
import json

URL = "http://fy.iciba.com/ajax.php?a=fy"
headers = {
    "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36",
    "Content-Type": "application/x-www-form-urlencoded; charset=UTF-8"

}
def get_translation(src):
    try:
        data = {
            "f": "auto",
            "t": "auto",
            "w" : str(src)
        }
        response = requests.post(URL, data=data, headers=headers)
        res = json.loads(response.text)
        return res["content"]["out"][1:]
    except:
        try:
            return res["content"]["word_mean"][0]
        except:
            return "出现错误了哦，再试一次吧。"



print("输入中文会自动翻译成英文，反之亦然。使用 [Ctrl] + [C] 退出。")
while (1):
    print("翻译结果：" + get_translation(input("输入内容 >> ")))
