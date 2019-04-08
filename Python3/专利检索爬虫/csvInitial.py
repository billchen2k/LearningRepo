import csv
import time
import os
import sys
csvDst = [csvDst95, csvDst96, csvDst97, csvDst98, csvDst99, csvDst00, csvDst01, csvDst02, csvDst03, csvDst04, csvDst05, csvDst06,
          csvDst07, csvDst08, csvDst09, csvDst10, csvDst11, csvDst12, csvDst13, csvDst14, csvDst15, csvDst16, csvDst17, csvDst18]
head = ['分类号', '申请人', '发明人', '申请号', '申请日', '发明名称', '申请国家', '邮编',
        '联系地址', '国家/省市', '专利公开号', '主分类号', '公开/公告日', '法律状态']
open_csv95 = open('/Users/billchen/OneDrive/Workspace/LearningRepo/Python3/专利检索爬虫/result/1995.csv', 'a+', newline='')
csvDst95 = csv.writer(open_csv95, dialect='excel')
if not os.path.exists(sys.path[0] + '/result'):
        os.makedirs(sys.path[0] + '/result')
for 
