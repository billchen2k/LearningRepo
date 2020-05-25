import requests
from lxml import etree

URL = "http://opac.zufe.edu.cn:8080/opac/openlink.php?location=ALL&title=%E8%B4%A2%E6%94%BF%E5%AD%A6&doctype=ALL&lang_code=ALL&match_flag=forward&displaypg=20&showmode=list&orderby=DESC&sort=CATA_DATE&onlylendable=no&count=266&with_ebook=on&page="


def crawl():
    res = []
    for i in range(14):
        print("Handling page {}...".format(i))
        thisURL = URL + str(i)
        text = requests.get(thisURL).text
        elements = etree.HTML(text)
        thisList = elements.xpath('//*[@id="content"]/div[4]//a/text()')
        for one in thisList:
            if (one != "馆藏"):
                res.append(one[one.find('.') + 1:])
        pass
    # 去重
    return list(set(res))


result = crawl()
for one in result:
    with open("book.txt", 'a+') as f:
        f.write("{} 由唐誉珈获取\n".format(one))
print("Finished.")
