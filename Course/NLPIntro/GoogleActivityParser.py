from lxml import etree
import pandas as pd
contents = etree.parse("./MyActivity.html")
root = contents.getroot()
bodyroot = root.xpath("/html/body/div")
nodes = [one.xpath("div/div[2]/node()") for one in bodyroot.getchildren()]
parsedNodes = [[one[0], one[1].text, one[2]] for one in nodes if len(one) == 3]
formattedNodes = [[one[0].replace("\xa0", ""), one[1], one[2]] for one in parsedNodes]
df = pd.DataFrame(formattedNodes)
df.rename(columns = {0: "Operation", 1:"Content", 2:"Date"})
df.to_csv("activity.csv")