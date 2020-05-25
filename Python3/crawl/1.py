import requests
from lxml import etree

URL = "http://wap.stockstar.com/list/3491"


def crawl():
    text = requests.get(URL).text
    elements = etree.HTML(text)
    list = elements.xpath('//*[@id="toUpdateSection"]/div[2]//a/text()')
    return list


result = crawl()
for one in result:
    with open("stock.txt", 'a+') as f:
        f.write("{} 由唐誉珈获取\n".format(one))
print("Finished.")
