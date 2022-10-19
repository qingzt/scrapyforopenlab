from time import sleep
import urllib.request
import jsonpath
import json
from pandas import UInt8Dtype
import pymysql
import re
#https://api.bilibili.com/x/relation/stat?vmid=214482102&jsonp=jsonp


def getjson(uid):
    headers = {
        'accept': '*/*',
        'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6',
        'cookie':
        "_uuid=9C282C3D-10BA4-5DD5-7EC5-B4BE107310526847686infoc; buvid_fp=1d9c49e5518b90543311de6440e9db65; buvid3=111E4544-7D69-5903-CE73-99A7CA05428647734infoc; b_nut=1664118848; nostalgia_conf=-1; i-wanna-go-back=-1; DedeUserID=85484616; DedeUserID__ckMd5=13ac39d92eea2f47; b_ut=5; rpdid=|(J~RYlm|kmk0J'uYYRkYJ|)~; buvid4=E1BB34B1-A558-3E2A-ED0A-0251FF83D5CB47734-022092523-jFX7KwtKp+TZtEjgewFpPg==; LIVE_BUVID=AUTO3716652824057403; fingerprint=6e79c919a01968d73ff63c5f4d373e74; bp_video_offset_85484616=717502431900991500; CURRENT_QUALITY=120; SESSDATA=aacb9d60,1681465409,60251*a1; bili_jct=ca5eb7425f71d8eee87624c105f517d3; innersign=0; CURRENT_FNVAL=16; sid=5jn29idu; b_lsid=F4CE4A10E_183E07E41F0; PVID=2",
        'user-agent':
        ' Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.0.0 Safari/537.36 Edg/106.0.1370.42',
        'sec-ch-ua':
        '"Chromium";v="106", "Microsoft Edge";v="106", "Not;A=Brand";v="99"',
        'sec-ch-ua-mobile': '?0',
        'sec-fetch-dest': 'script',
        'sec-fetch-mode': 'no-cors',
        'sec-fetch-site': 'same-site',
        'sec-ch-ua-platform': '"Windows"',
        'referer':
        'https://space.bilibili.com/' + uid + '/fans/follow?tagid=-1'
    }
    followurl = 'https://api.bilibili.com/x/relation/followings?vmid=' + uid + '&pn=1&ps=50&order=desc&jsonp=jsonp&callback=__jp3'
    requset = urllib.request.Request(url=followurl, headers=headers)
    response = urllib.request.urlopen(requset)
    content = response.read().decode("utf-8")
    content = content[6:-1]
    with open(uid + 'A.json', 'w', encoding='utf-8') as fp:
        fp.write(content)
    followurl = 'https://api.bilibili.com/x/relation/followings?vmid=' + uid + '&pn=2&ps=50&order=desc&jsonp=jsonp&callback=__jp3'
    requset = urllib.request.Request(url=followurl, headers=headers)
    response = urllib.request.urlopen(requset)
    content = response.read().decode("utf-8")
    content = content[6:-1]
    with open(uid + 'B.json', 'w', encoding='utf-8') as fp:
        fp.write(content)


def getfollowuid(uid):
    obj = json.load(open(uid + 'A.json', 'r', encoding='utf-8'))
    followlist = jsonpath.jsonpath(obj, '$..mid')
    obj = json.load(open(uid + 'B.json', 'r', encoding='utf-8'))
    if jsonpath.jsonpath(obj, '$..mid'):
        followlist = followlist + jsonpath.jsonpath(obj, '$..mid')
    db = pymysql.connect(host="127.0.0.1",
                         user="root",
                         password="wssb",
                         database="bili")
    cursor = db.cursor()
    cursor.execute("create table Bili" + uid + " select * from uid")
    for no in range(0, len(followlist)):
        cursor.execute("insert into Bili" + uid + " values(" +
                       str(followlist[no]) + ')')
    db.commit()
    db.close()


def tong(uidA, uidB):
    selectSQL = '(select uid from Bili' + uidA + ') intersect (select * from Bili' + uidB + ')'
    db = pymysql.connect(host="127.0.0.1",
                         user="root",
                         password="wssb",
                         database="Bili")
    with db.cursor() as cursor:
        cursor.execute(selectSQL)
        uidt = cursor.fetchall()
    db.close()
    return uidt


def getinfor(uid):
    headers = {
        'accept': '*/*',
        'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6',
        'cookie':
        "_uuid=9C282C3D-10BA4-5DD5-7EC5-B4BE107310526847686infoc; buvid_fp=1d9c49e5518b90543311de6440e9db65; buvid3=111E4544-7D69-5903-CE73-99A7CA05428647734infoc; b_nut=1664118848; nostalgia_conf=-1; i-wanna-go-back=-1; DedeUserID=85484616; DedeUserID__ckMd5=13ac39d92eea2f47; b_ut=5; rpdid=|(J~RYlm|kmk0J'uYYRkYJ|)~; buvid4=E1BB34B1-A558-3E2A-ED0A-0251FF83D5CB47734-022092523-jFX7KwtKp+TZtEjgewFpPg==; LIVE_BUVID=AUTO3716652824057403; fingerprint=6e79c919a01968d73ff63c5f4d373e74; bp_video_offset_85484616=717502431900991500; CURRENT_QUALITY=120; SESSDATA=aacb9d60,1681465409,60251*a1; bili_jct=ca5eb7425f71d8eee87624c105f517d3; innersign=0; CURRENT_FNVAL=16; sid=5jn29idu; b_lsid=F4CE4A10E_183E07E41F0; PVID=2",
        'user-agent':
        ' Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.0.0 Safari/537.36 Edg/106.0.1370.42',
        'sec-ch-ua':
        '"Chromium";v="106", "Microsoft Edge";v="106", "Not;A=Brand";v="99"',
        'sec-ch-ua-mobile': '?0',
        'sec-fetch-dest': 'script',
        'sec-fetch-mode': 'no-cors',
        'sec-fetch-site': 'same-site',
        'sec-ch-ua-platform': '"Windows"',
        'referer': 'https://space.bilibili.com/' + uid + '/fans/follow'
    }
    inforurl = 'https://api.bilibili.com/x/space/acc/info?mid=' + uid + '&token=&platform=web&jsonp=jsonp'
    requset = urllib.request.Request(url=inforurl, headers=headers)
    response = urllib.request.urlopen(requset)
    contentinfor = response.read().decode("utf-8")
    fansurl = 'https://api.bilibili.com/x/relation/stat?vmid=' + uid + '&jsonp=jsonp'
    requset = urllib.request.Request(url=fansurl, headers=headers)
    response = urllib.request.urlopen(requset)
    contentfans = response.read().decode("utf-8")
    infor = [uid]
    pattern = re.compile('name":"(.*?)","sex')
    infor.append(pattern.findall(contentinfor)[0])
    pattern = re.compile('level":(.*?),"jointime')
    infor.append(pattern.findall(contentinfor)[0])
    pattern = re.compile('follower":(.*?)}')
    infor.append(pattern.findall(contentfans)[0])
    return infor


def addto(uidt, uidA, uidB):
    createSQL = 'create table tong' + uidA + 'and' + uidB + '(uid varchar(200),name varchar(20),level int,fans int)'
    db = pymysql.connect(host="127.0.0.1",
                         user="root",
                         password="wssb",
                         database="Bili")
    course = db.cursor()
    course.execute(createSQL)
    for no in range(0, len(uidt)):
        infor = getinfor(uidt[no][0])
        insertSQL = 'insert into tong values("' + infor[0] + '","' + infor[
            1] + '",' + infor[2] + ',' + infor[3] + ')'
        course.execute(insertSQL)
        sleep(1)
    db.commit()
    course.execute('select * from tong')
    for dept in course.fetchall():
        print(dept)
    db.close()


def chachengfen(uidA, uidB):
    getjson(uidA)
    getjson(uidB)
    getfollowuid(uidA)
    getfollowuid(uidB)
    addto(tong(uidA, uidB), uidA, uidB)


uidA = str(input("请输入用户A的UID"))
uidB = str(input("请输入用户B的UID"))
chachengfen(uidA, uidB)
