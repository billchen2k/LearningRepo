import requests
import re
import time
from bs4 import BeautifulSoup
def get_one_page(url):
    page_req=requests.get(url,headers={"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36 Edge/17.17134"})
    html=page_req.text.encode('iso-8859-1')
    bf=BeautifulSoup( html,"lxml")
    texts = bf.find_all('div',id='content')
    return texts[0].text.replace('\xa0'*8,'\n\n')

def get_pages(url):
    html_sets={}
    page_req=requests.get(url,headers={"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36 Edge/17.17134"})
    html=page_req.text.encode('iso-8859-1')
    bf=BeautifulSoup( html,"lxml")
    texts = bf.find_all('div',id='list')
    for i in texts[0].find_all("dd"):
        S=re.match(r'/[\s\S]*?/([\d]*.html)',i.find("a")["href"]).groups()[0]
        html_sets[S]=i.find("a").text
    return html_sets

def get_texts(name,urls):
    html_dict=get_pages(urls)
    filename=name+".txt"
    for k in html_dict.keys():
        url=urls+k
        s=get_one_page(url)
        write_on(filename,html_dict[k],s)



def write_on(filename,title,content):
    with open(filename,"a") as f:
        print(title)
        f.write(title+"\n\n\n")
        f.write("\n"+content.replace(u'\xa0', u''))

if __name__=="__main__":
    get_texts(input("小说名字："),input("加载网址："))
