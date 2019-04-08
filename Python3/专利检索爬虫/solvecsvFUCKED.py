from lxml import etree
import lxml
import pickle

with open('/Users/billchen/OneDrive/Workspace/LearningRepo/Python3/专利检索爬虫/20050101_20101231_B09B_PAGE1.pickle', 'rb') as f:
    source = ''
    p = pickle.load(f)
html = etree.HTML(p)
