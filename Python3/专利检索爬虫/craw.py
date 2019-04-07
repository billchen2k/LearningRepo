from bs4 import BeautifulSoup
import selenium
from selenium import webdriver
from selenium.webdriver.support.ui import Select
#进入表格检索模式
url = 'http://www.shanghaiip.cn/Search/login.do'
driver = webdriver.Chrome()
driver.get(url)
frameMain = driver.find_element_by_xpath('/html/body/iframe')
driver.switch_to_frame(frameMain)
frameTitle = driver.find_element_by_xpath('/html/frameset/frame[1]')
driver.switch_to_frame(frameTitle)
targetButton = driver.find_element_by_link_text('表格检索')
targetButton.click()
driver.switch_to_default_content()
driver.switch_to_frame(frameMain)
frameBottom = driver.find_element_by_xpath('//*[@id="frame_bottom"]/frame[3]')
driver.switch_to_frame(frameBottom)
# 开始设置搜索条件
# 申请日
boxDateLimit = driver.find_element_by_id('selChsDate')
s1 = Select(boxDateLimit)
s1.select_by_index(1)
# 搜索方式
radTime = driver.find_element_by_xpath('//*[@id="radChsDate1"]')
radTime.click()
# 时间范围
driver.find_element_by_id('strChsBegDate').send_keys('19950101')
driver.find_element_by_id('strChsEndDate').send_keys('19951231')
# 专利号设置
# driver.find_element_by_xpath('')
# 搜索
btnSearch = driver.find_element_by_xpath(
    '//*[@id="frmChsFrom"]/table/tbody/tr[14]/td[3]/img[1]')
btnSearch.click()
