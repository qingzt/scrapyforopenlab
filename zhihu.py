import urllib.request
import jsonpath
import json
import pymysql
import datetime
from wordcloud import WordCloud
import time


def insert(every):  #对每一个列表执行插入语句
    db = pymysql.connect(host="127.0.0.1",
                         user="root",
                         password="wssb",
                         database="zhihu")
    cursor = db.cursor()
    SQL = 'insert into ' + table_name + ' values("' + every[0] + '","' + every[
        1] + '",' + str(every[2]) + ',"' + every[3] + '",' + str(
            every[4]) + ',' + str(every[5]) + ',' + str(every[6]) + ',' + str(
                every[7]) + ')'  #拼接成插入字符串
    cursor.execute(SQL)
    db.commit()  #提交
    db.close()


baseurl = 'https://www.zhihu.com/api/v4/creators/rank/hot?domain=0&limit=102&offset=0&period=hour'  #目标网站
headers = {
    'cookie':
    '_zap=4edafd7a-cd56-4669-89f6-fa1628e41200; d_c0=AEATawpdnRWPTiyFWHf13w-E0jTx0w4TpLE=|1664117734; ISSW=1; __snaker__id=YjwhLaRYgKnYrgFQ; gdxidpyhxdE=Qhil%2FGXzqPtE2%2FgAeK3ewnRY1lrW%5CY33%5CvvakJ8rI%2BMOlQUbjQHTK3pYU2BGCq3LPW7jQKDmu9IRUK76uGP2eq8PvK4f%2Ft1P8TuVt0ykzfkOC%2BL0I%5C%2Feml4PeCELH%2FNH85yg7A1cjhT%2FCEJ8kCYQ%2FHZy6EeBeM3rUY5PuDWRQQBuVITN%3A1665847904065; _9755xjdesxxd_=32; YD00517437729195%3AWM_NI=XmGZKbawjCmbzLR85lgg2fPJ%2FKXGl16BnC4aa83n11DyZMdwNVQL0M%2FOmxkaK5bONIFPfUKomoguZZwFgnKpTakrhd909%2FgTQaAIfUAUnKMNETGZ4%2FzEp8GTlcxBaRt6SEc%3D; YD00517437729195%3AWM_NIKE=9ca17ae2e6ffcda170e2e6eeb5f353f78ca3a7d364a19e8ea7c55a828b9a82d560b6bf00b5bb5ea28a9d88f02af0fea7c3b92a9cb389bbca6aa3a9a6a4f06aba949ed9b868a5b9fe87d342ed9598a8ef3bf69ea2a4b76ba3e8fd8fb43b88a796aee77d8e8a9fadb347ed91a399ea6b89ebaeb0cd438690aab6ca65afb1a996d952b59aa98fca7c98bfa593eb70fbf0f7d0e66093bf8faae55f838ba2acd046878c89bbb725ba9bc0d9c660b0bdb8a3e45ab8ea9da6e237e2a3; YD00517437729195%3AWM_TID=RmSf2so7XFJFFRAQRAfVT%2BLgG8VfAD1m; captcha_session_v2=2|1:0|10:1665847108|18:captcha_session_v2|88:WXhRRWQ5a0JWS3V1YWZWTkJtQUpRbEtKR2VxRHNvUE5WUkZpUG5hd2RkRjY4VC85cTRsZU5PNzFkYzRvZ3hPZg==|f2fd3c577b2b07d0a0e67de24068e934a5abcee010f3093b0147ca55ac847776; captcha_ticket_v2=2|1:0|10:1665847113|17:captcha_ticket_v2|704:eyJ2YWxpZGF0ZSI6IkNOMzFfeUZQbEpSUkt4dEVUcjhTXzUwVDlyT2dvanpBWUZUYlM5LU92dHpmNkxGTGRoTFlKd1BwQ1Z3d3pmSXRfMjB3TGlEU0ZNRThFdW5rZk15YkE2ME9MeTBvNHBHVGZGeWRRazBXbVhBaFUySERoRS1FY0dXZV9EQU5xQXpYcWljQVpyalptcG9uSldOWXFweXdpNjVMZ0hlRTguLUlZUm55UnZLb01PeXREc1pSV3Bkd1NGbm00N0E1NHU0eS1nb18wQlNaYk5SRmpGQXcyMHltMlduMENYWUdaa3VBNmNmUzVRUl9McTluZjItNC1YR0RxU2k0SV8tcHRQRngybG9yWjA4c0ZQZmM1LVF5MmwtQ3F1clVVNDdVYlc1SmhtdEVvV3VKMVJfMmRRRnNvamt0N3RZRXFjOFphS1Euc3pQNTg4aWJtUi1hR1RmSWRUT1dmLkpRUG41OS14dmdUa0otYjJFd2ZuRHp2dVJXQnNxWkVUMVFPN0Zaejd2S0hzSlFtZXBtMnhTNHlmdWxscGVGZ2kuMVRzZ1AwWlJNOG14Snh1NTJicDFRNDBMUmdKZFQ1aW91aGwwLXlCYWdRVmZKWFFlZGsyYkdIVUZ6aGtxdDdHZmRkMlNPMXpsWWFCdXhEMEY0QzdvSC1CU3Y0X1FlUkZPOTBVUG8tOWtaMyJ9|40227a0962ae64fdb0085feae65bafb462ca1c7c0c3a39dc8df9c9ec17f4ed37; z_c0=2|1:0|10:1665847127|4:z_c0|92:Mi4xU3VaOUx3QUFBQUFBUUJOckNsMmRGU1lBQUFCZ0FsVk5WeDA0WkFEUEEyTzdYLWVwM0pTMTU0ZTNPZ05KUmJTYTV3|2723ab34c5f990d0a95c64cc234eacd9bbc4e368a240fef4eaf61f62f0803401; q_c1=9af9e9cc817f42c4b3ebbb173e1fc6eb|1665847175000|1665847175000; tst=h; _xsrf=dc86e7eb-3f47-40cf-8cd9-37a3af08ad2f; SUBMIT_0=68114eff-219c-4e08-9fa7-3f7e8cf159e8; SESSIONID=P3pBvVyaSNdiPl9aV28U3daDXoHdXQY4ny4OJg6hm8q; JOID=U1wWAkgfxCSPTkEYJB_DdVZCHIIzSvBWzzoSZkdOj0fkHC8kQmOub-xJQx0kQScgd7ksvWFbvjj4LhBAytD6u1M=; osd=WlkdAEkWwS-NT0gdLx3CfFNJHoM6T_tUzjMXbUVPhkLvHi4tR2isbuVMSB8lSCIrdbgluGpZvzH9JRJBw9XxuVI=; KLBRSID=fb3eda1aa35a9ed9f88f346a7a3ebe83|1665889061|1665888120',
    'user-agent':
    ' Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.0.0 Safari/537.36'
}  #请求头
repeat=int(input('设置定时请输入1，否则输入0'))
if repeat==1:
    settime=int(input('请输入定时时间，以秒为单位'))
start=1
while start:
    requset = urllib.request.Request(url=baseurl, headers=headers)  #制作请求
    response = urllib.request.urlopen(requset)  #获得相应
    content = response.read().decode("utf-8")  #获得源码文件
    with open('rebang.json', 'w', encoding='utf-8') as fp:
        fp.write(content)  #将源码文件保存
    obj = json.load(open('rebang.json', 'r', encoding='utf-8'))  #转化为jsonpath对象
    title_list = jsonpath.jsonpath(obj, '$..title')  #获取标题
    sum = len(title_list)  #得到热榜总数
    infor_list = []  #存放相关信息的列表
    wordcloud=[] #制作词云的列表
    for no in range(0, sum):
        every = []  #热榜的每一条存放在其中
        title = jsonpath.jsonpath(obj, '$.data[' + str(no) +
                                '].question.title')[0]  #获得标题
        type_list = jsonpath.jsonpath(obj, '$.data[' + str(no) +
                                    '].question.topics[*].name')  #获得分类
        wordcloud=wordcloud+type_list
        topics = ",".join(type_list)  #将分类列表转为字符串
        level = jsonpath.jsonpath(obj, '$.data[' + str(no) +
                                '].reaction.score')[0]  #获得热度等级
        url = jsonpath.jsonpath(obj,
                                '$.data[' + str(no) + '].question.url')[0]  #获得连接
        follow_num = jsonpath.jsonpath(
            obj, '$.data[' + str(no) + '].reaction.follow_num')[0]  #获得关注人数
        pv = jsonpath.jsonpath(obj,
                            '$.data[' + str(no) + '].reaction.pv')[0]  #获得阅读量
        answer_num = jsonpath.jsonpath(
            obj, '$.data[' + str(no) + '].reaction.answer_num')[0]  #获得回答人数
        upvote_num = jsonpath.jsonpath(
            obj, '$.data[' + str(no) + '].reaction.upvote_num')[0]  #获得点赞人数
        every.append(title)
        every.append(topics)
        every.append(level)
        every.append(url)
        every.append(follow_num)
        every.append(pv)
        every.append(answer_num)
        every.append(upvote_num)  #将相关信息加入every
        infor_list.append(every)  #将every加入infor
    newcloud=' '.join(wordcloud)#将列表转为用空格分隔的字符串
    table_name = 'zhihu' + str(datetime.datetime.now()).replace(' ', '').replace(
        '-', '').replace(':', '').replace('.', '')[:14]  #建表的表名
    createSQL = 'create table ' + table_name + ' select * from zhihu'  #建表语句
    db = pymysql.connect(host="127.0.0.1",
                        user="root",
                        password="wssb",
                        database="zhihu")  #连接到数据库
    cursor = db.cursor()  #创建游标
    cursor.execute(createSQL)  #执行建表语句
    db.commit()  #提交
    db.close()  #关闭连接
    for no in range(0, len(infor_list)):
        insert(infor_list[no])  #执行插入函数
    selectSQL = 'select title as "标题",topics as "分类",level as "热力值",url as "链接",follow_num as "关注人数",pv as "浏览量",answer_num as "回答数",upvote_num as "点赞数" from ' + table_name
    db = pymysql.connect(host="127.0.0.1",
                        user="root",
                        password="wssb",
                        database="zhihu")
    with db.cursor() as cursor:
        cursor.execute(selectSQL)
        for dept in cursor.fetchall():
            print(dept)
    db.close()  #从数据库中获得输出
    print(table_name)
    wc = WordCloud(font_path="msyh.ttc",width = 1000,height = 700,background_color='white',max_words=100)
    wc.generate(newcloud)
    wc.to_file(table_name+".png")
    if repeat==1:
        time.sleep(settime)#设置定时
    else:
        start=0
