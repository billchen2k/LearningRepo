# -*- coding: utf-8 -*-
import requests
from bs4 import BeautifulSoup
from lxml import etree
import csv
import pickle
import time
timestart = time.time()
with open('/Users/billchen/OneDrive/Workspace/LearningRepo/Python3/专利检索爬虫/output/20160101_20181231_C02F_PAGE_306.pickle', 'rb') as f:
    doc_2 = pickle.load(f)

def save_csv(out_txt):
    global timestart
    open_csv = open('/Users/billchen/OneDrive/Workspace/LearningRepo/Python3/专利检索爬虫/result.csv', 'a+', newline='')
    out_str = str(out_txt)
    a = []
    b = []
    c = []
    d = []
    e = []
    f = []
    g = []
    h = []
    i = []
    j = []
    k = []
    l = []
    m = []
    n = []
    xcontent = etree.HTML(out_str)
    num1 = 1
    head = ['分类号', '申请人', '发明人', '申请号', '申请日', '发明名称', '申请国家','邮编', '联系地址', '国家/省市', '专利公开号', '主分类号', '公开/公告日', '法律状态']
    while num1 < 101:
        
        strnum = str(num1)
        tempk = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[1]/td[2]/text()')                        
        
        
        tempa = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[10]/td[2]/text()')
        
        
        tempb = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[3]/td[2]/text()')
        
        
        tempc = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[4]/td[2]/text()')
        


        tempd = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[1]/td[2]/a/text()')
        
        
        tempe = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[7]/td[2]/text()')
        

        tempf = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[2]/td[2]/text()')
        

        tempg = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[8]/td[2]/text()')
        

        temph = xcontent.xpath( '//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[12]/td[1]/text()')
        temphh = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[12]/td[2]/text()')
        if not len(tempk) == 0:
            if temph[0][0] == "邮":
                h.append(temphh[0][0:-1])
                tempnn = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[13]/td[2]/text()')
                n.append(tempnn[0])
            else:
                h.append(' ')
                n.append(temphh[0])

        tempi = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[5]/td[2]/text()')
        
        
        tempj = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[11]/td[2]/text()')
        

        templ = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[9]/td[2]/text()')
        

        tempm = xcontent.xpath('//*[@id="tab"]/tbody/tr[' + strnum + ']/td/table/tbody/tr[6]/td[2]/text()')
        if not len(tempk) == 0:
            m.append(tempm[0][0:-1])
            l.append(templ[0][0:-1])
            j.append(tempj[0][0:-1])
            i.append(tempi[0][0:-1])
            g.append(tempg[0][0:-1])
            f.append(tempf[0][0:-1])
            e.append(tempe[0][0:-1])
            d.append(tempd[0][0:-1])
            c.append(tempc[0][0:-1])
            b.append(tempb[0][0:-1])
            a.append(tempa[0][0:-1])
            k.append(list(filter(lambda x: x, tempk[0].split(' ')))[1])

    
        num1 = num1+1
    label = zip(a, b, c, d, e, f, g, h, i, j, k, l, m, n)
    csv_write = csv.writer(open_csv, dialect='excel')
    csv_write.writerow(head)
    w=0
    for v in label:
        
        csv_write.writerow(v)
        w = w + 1
    print(w)
    open_csv.close()
    timeend = time.time()
    print("%.2fs" % (timeend - timestart))
        

save_csv(doc_2)
