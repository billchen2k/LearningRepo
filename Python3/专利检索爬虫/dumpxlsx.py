import os
import sys
import pandas
import openpyxl
from openpyxl import load_workbook
import time
year = 1995
countAll = 0
starttime = time.time()
# result.xlsx 必须事先存在
while year <= 2018:
    thistime = time.time()
    csvPath = sys.path[0] + '/result/%d.csv' % year
    excelPath = sys.path[0] + '/result.xlsx'
    csvReader = pandas.read_csv(csvPath, encoding='utf_8_sig')
    excelWriter = pandas.ExcelWriter(excelPath, engine='openpyxl')
    countThis = csvReader.shape[0] - 1
    countAll = countAll + countThis
    # 使用 openpyxl 来追加数据，而不是覆盖
    book = load_workbook(excelPath)
    excelWriter.book = book
    print("正在将 %d 年的 %d 条数据转换为 xlsx..." % (year, countThis))
    csvReader.to_excel(excelWriter, sheet_name=str(year))
    excelWriter.save()
    year = year + 1
    thisend = time.time()
    print("该条处理完成，耗时 %.2f s。" % (thisend - thistime))
endtime = time.time()
print("处理完成。耗时 %.4f min，共转换 %d 条数据。" % ((endtime - starttime)/60, countAll))

