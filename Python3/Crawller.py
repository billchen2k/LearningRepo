from bs4 import BeautifulSoup
import selenium
import requests
import time
from selenium import webdriver
from selenium import *
url ='https://www.ithome.com'
header = {
    'User-Agent':'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_3) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/12.0.3 Safari/605.1.15'}
source = requests.get(url, headers=header)
source.encoding = 'UTF-8'
s = BeautifulSoup(source.text, 'lxml')
div = s.find_all('a', target='_blank')
urls =[]
for a in div:
    temp = a.attrs['href']
    if (temp[0:25] == 'https://www.ithome.com/0/' and a.sting != 'None'):
        print(a.string)

driver = webdriver.Chrome()
driver.get('https://ithome.com')
driver.find_element_by_class_name('sfa sideweixin').click()
# for aurl in urls:
#     newsource = requests.get(aurl, headers=header)
#     newsource.encoding = 'UTF-8'
#     soup = BeautifulSoup(newsource.text, 'lxml')
#     newdiv = s.find_all('p')
#     for b in newdiv:
#         print (b.string)
