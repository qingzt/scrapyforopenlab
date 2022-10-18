from lxml import etree
import urllib
import urllib.request
import datetime
import pymysql

# //*[@id="line_u7_0"]/div[2]/a

url = "https://www.bkjx.sdu.edu.cn/sanji_list.jsp?urltype=tree.TreeTempUrl&wbtreeid=1010"

headers = {
    'accept': '*/*',
    'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6',
    'user-agent':
    ' Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.0.0 Safari/537.36 Edg/106.0.1370.42',
    'sec-ch-ua':
    '"Chromium";v="106", "Microsoft Edge";v="106", "Not;A=Brand";v="99"',
    'sec-ch-ua-mobile': '?0',
    'sec-fetch-dest': 'script',
    'sec-fetch-mode': 'no-cors',
    'sec-fetch-site': 'same-site',
    'sec-ch-ua-platform': '"Windows"',
}
request = urllib.request.Request(url=url, headers=headers)
response = urllib.request.urlopen(request)
content = response.read().decode('utf-8')
tree = etree.HTML(content)

titlelist = tree.xpath('//div[@id="div_more_news"]/div/div/a/@title')
urllist = tree.xpath('//div[@id="div_more_news"]/div/div/a/@href')
datelist = tree.xpath('//div[@id="div_more_news"]/div/div[3]/text()')

table_name = 'tongzhi' + str(datetime.datetime.now()).replace(' ', '').replace(
    '-', '').replace(':', '').replace('.', '')[:14]
createSQL = 'create table ' + table_name + ' select * from tongzhi'

print(table_name)

db = pymysql.connect(host="127.0.0.1",
                     user="root",
                     password="wssb",
                     database="tongzhi")
cursor = db.cursor()
cursor.execute(createSQL)
for i in range(0, len(urllist)):
    insertSQL = 'insert into ' + table_name + ' values("https://www.bkjx.sdu.edu.cn/' + urllist[
        i] + '","' + titlelist[i] + '","' + datelist[i] + '")'

    cursor.execute(insertSQL)
db.commit()

with db.cursor() as cursor:
    cursor.execute('select * from ' + table_name)
    for dept in cursor.fetchall():
        print(dept)
db.close()
