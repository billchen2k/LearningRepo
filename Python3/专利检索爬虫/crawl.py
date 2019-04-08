import selenium
import time
import datetime
import pickle
import sys
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.support.ui import Select
import os
#初始化进入表格检索模式
print('初始化 WebDriver...')
url = 'http://www.shanghaiip.cn/Search/login.do'
driver = webdriver.Chrome()
driver.set_page_load_timeout(300)
driver.set_script_timeout(300)
driver.get(url)
frameMain = driver.find_element_by_xpath('/html/body/iframe')
driver.switch_to_frame(frameMain)
frameTitle = driver.find_element_by_xpath('/html/frameset/frame[1]')
driver.switch_to_frame(frameTitle)
targetButton = driver.find_element_by_link_text('表格检索')
firstSearch = 1

def searcher(startDate, endDate, pattern, startPage):
    global firstSearch
    print (datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S') + ': 正在初始化专利号为 '+ str(pattern) +' 的相关信息爬取...')
    timestart = time.time()
    driver.switch_to_default_content()
    driver.switch_to_frame(frameMain)
    driver.switch_to_frame(frameTitle)
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
    driver.find_element_by_id('strChsBegDate').send_keys(startDate)
    driver.find_element_by_id('strChsEndDate').send_keys(endDate)
    # 专利号设置
    driver.find_element_by_xpath('//*[@id="strChsIC1"]').send_keys(pattern)
    # 搜索
    btnSearch = driver.find_element_by_xpath(
        '//*[@id="frmChsFrom"]/table/tbody/tr[14]/td[3]/img[1]')
    btnSearch.click()
    time.sleep(0.8)
    # 勾选更多信息，并设置每页显示100条
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[2]/td[2]/input').click()
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[4]/td[5]/input').click()
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[2]/td[4]/input').click()
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[2]/td[3]/input').click()
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[3]/td[3]/input').click()
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[3]/td[5]/input').click()
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[4]/td[6]/input').click()
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[5]/td[5]/input').click()
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[3]/td[5]/input').click()
    driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[3]/td[6]/input').click()
    btnRefresh = driver.find_element_by_xpath('//*[@id="notStat2"]/table[2]/tbody/tr[5]/td[7]/img[3]')
    btnRefresh.click()
    time.sleep(0.8)
    s2 = Select(driver.find_element_by_xpath('//*[@id="notStat2"]/table[1]/tbody/tr[2]/td[1]/select[1]'))
    s2.select_by_index(2)
    #打印信息
    timeendsearch = time.time()
    pageLabel = driver.find_element_by_xpath('//*[@id="notStat2"]/table[1]/tbody/tr[2]/td[3]/span')
    dataCount = driver.find_element_by_xpath('//*[@id="resultForm"]/table[1]/tbody/tr[2]/td/table/tbody/tr[3]/td/font')
    dataNum = dataCount.text[1:]
    print('本次搜索结果总页数：' + pageLabel.text[2:])
    print('本次搜索结果总条数：' + dataNum)
    print('搜索用时：%.2f' % (timeendsearch - timestart) + 's')
    totalPage = int(pageLabel.text[2:])
    #处理没有数据的情况
    if dataNum == '0条':
        print('该时间段没有专利号为 ' + pattern + ' 的数据。')
        return
    #处理数据过多的情况
    if totalPage == 1000:
        input('本次搜索结果超过1000页，可能出现错误，请重新选择时间范围。')
        return
    i = 0
    # 从指定页码开始搜索
    if firstSearch == 1 and startPage != 1:
        i = int(startPage) - 1
        print('正在跳转到 %d 页开始爬取。' % (i + 1))
        driver.find_element_by_xpath('//*[@id="currPage1"]').send_keys(str(i + 1))
        driver.find_element_by_xpath('//*[@id="notStat"]/td[3]/img').click()
        firstSearch = 0
    else:
        firstSearch = 0
    # 循环下一页
    if totalPage > 1:
        btnNext = driver.find_element_by_link_text('[下一页]')
   
    while i < totalPage:
        timestartpage = time.time()
        # with open('/Users/billchen/OneDrive/Workspace/LearningRepo/Python3/专利检索爬虫/output/' + startDate + '_'+endDate+'_' + pattern.replace('/','.') + '_PAGE' + str(int(i+1)) + '.pickle', 'wb') as f:
        with open(sys.path[0] + '/output/' + startDate + '_'+endDate+'_' + pattern.replace('/', '.') + '_PAGE_%03d.pickle' % int(i+1),  'wb') as f:
            pickle.dump(driver.page_source, f)
        # 下面两行用于直接输出文本文件
        # with open(sys.path[0] + '/outputtxt/' + startDate + '_'+endDate+'_' + pattern.replace('/', '.') + '_PAGE' + str(int(i+1)) + '.txt',  'w', encoding='utf8') as f:
        #     f.write(driver.page_source)
        if i < totalPage - 1:
            time.sleep(0.2)
            btnNext = driver.find_element_by_link_text('[下一页]')
            btnNext.click()
        timeendpage = time.time()
        print(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S') + ': 已处理 ' + startDate + ' 到 ' + endDate + ' 的第 ' + str(int(i + 1)) + ' 页数据。')
        print('本页处理用时：%.2f' % (timeendpage - timestartpage) + 's')
        i = i + 1
    print(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S') + ": 本次处理完成，已处理 " + startDate + ' 到 ' + endDate + ' 的全部专利号为 ' + pattern + ' 的数据。')

def counter():
    timestart = time.time()
    print("正在统计 pickle 中的数据条数...")
    pickleList = []
    pickleList = os.listdir(sys.path[0] + '/output')
    for a in pickleList:
        if a[0] == '.':
            pickleList.remove(a)
    countALL = 0
    pickleList.sort()
    import lxml
    from lxml import etree
    for p in pickleList:
        with open(sys.path[0] + '/output/' + p, 'rb') as f:
            html = pickle.load(f)
        element = etree.HTML(html)
        thisCount = element.xpath(
            '//*[@id="resultForm"]/table[1]/tbody/tr[2]/td/table/tbody/tr[3]/td/font/text()')
        numtemp = int(thisCount[0][1:-1])
        pagenum = int(p[-10:-7])
        if int(numtemp / 100) + 1 == pagenum:
            num = numtemp % 100
        else:
            num = 100
        print(p + ' 中存有 '+str(num)+' 条信息。目前累计有 %d 条信息' % countALL)
        countALL = countALL + int(num)
    timeend = time.time()
    print('统计完成。在 ' + str(len(pickleList)) + ' 条 pickle 中共有 ' + str(countALL) + ' 条信息。耗时 %2fmin' % ((timeend - timestart) / 60.0))

def main():
    with open(sys.path[0] + '/patterns.pickle', 'rb') as f:
        patternData = pickle.load(f)
    startdate = input("输入开始时间（格式：19951201）：")
    enddate = input("输入结束时间（格式：19951231）：")
    startpattern = input("输入开始检索的专利号（留空以遍历全部）：")
    startpage = input("输入开始检索的页码（留空以从首页遍历）：")
    if startpage == '':
        startpage = '1'
    timestartall = time.time()
    # 创建工作目录
    if not os.path.exists(sys.path[0] + '/output'):
        os.makedirs(sys.path[0] + '/output')
    if startpattern == '':
        for patternNow in patternData[1:-1]:
            searcher(startDate=startdate, endDate=enddate, pattern=patternNow[0], startPage = startpage)
    else:
        startindex = patternData.index([startpattern])
        for patternNow in patternData[startindex:-1]:
            searcher(startDate=startdate, endDate=enddate, pattern=patternNow[0], startPage = startpage)
    timeendall = time.time()
    print(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S') +': 执行完成，总共用时：%.4f' % ((timeendall - timestartall)/3600) + 'h')
    input("Press anykey to continue...")

if __name__ == '__main__':
    if len(sys.argv) == 1:
        main()
    elif (sys.argv[1] == '-c' or sys.argv[1] == '-c'):
        main()
    elif (sys.argv[1] == '-n' or sys.argv[1] == '-n'):
        counter()
    else:
        print ("使用方法：直接运行来爬取数据。\n使用参数 --s 来解析已爬取到 output 文件夹下的数据，--c 来爬取数据，--n 来统计已爬取的数量。")
