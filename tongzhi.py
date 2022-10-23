from lxml import etree
import urllib
import urllib.request
import datetime
import pymysql
import time
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
repeat=int(input('设置定时请输入1，否则输入0'))
if repeat==1:
    settime=int(input('请输入定时时间，以秒为单位'))
start=1
while start:
    request = urllib.request.Request(url=url, headers=headers)  #制作请求头
    response = urllib.request.urlopen(request)  #获取相应
    content = response.read().decode('utf-8')  #获取源码
    tree = etree.HTML(content)  #转化为xpath对象

    titlelist = tree.xpath('//div[@id="div_more_news"]/div/div/a/@title')  #名称列表
    urllist = tree.xpath('//div[@id="div_more_news"]/div/div/a/@href')  #链接列表
    datelist = tree.xpath('//div[@id="div_more_news"]/div/div[3]/text()')  #日期列表

    table_name = 'tongzhi' + str(datetime.datetime.now()).replace(' ', '').replace(
        '-', '').replace(':', '').replace('.', '')[:14]  #表名
    createSQL = 'create table ' + table_name + ' select * from tongzhi where 1=2'  #创建表SQL语句

    db = pymysql.connect(host="127.0.0.1",
                        user="root",
                        password="wssb",
                        database="tongzhi")  #链接到数据库
    cursor = db.cursor()  #游标
    cursor.execute(createSQL)  #执行建表语句
    for i in range(0, len(urllist)):
        insertSQL = 'insert into ' + table_name + ' values("https://www.bkjx.sdu.edu.cn/' + urllist[
            i] + '","' + titlelist[i] + '","' + datelist[i] + '")'  #插入的SQL

        cursor.execute(insertSQL)  #执行插入语句
    db.commit()  #提交到数据库

    with db.cursor() as cursor:
        cursor.execute('select * from ' + table_name)
        for dept in cursor.fetchall():
            print(dept)  #输出
        cursor.execute('insert into tongzhi select * from '+ table_name+' where title not in (select title from tongzhi)')#去重
        #cursor.execute('drop table ' + table_name)
    db.commit()
    db.close()  #关闭连接
    print(table_name)
    if repeat==1:
        time.sleep(settime)#设置定时
    else:
        start=0
