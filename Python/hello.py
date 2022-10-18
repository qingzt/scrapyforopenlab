from time import sleep
import urllib.request
import urllib.parse


def download(page):
    base_url = 'https://movie.douban.com/j/chart/top_list?type=24&interval_id=100%3A90&action=&'
    headers = {
     'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.0.0 Safari/537.36 Edg/106.0.1370.42'
    }
    data = {
        'start': (page-1)*20,
        'limit': 20
    }
    data = urllib.parse.urlencode(data)
    url = base_url+data
    request = urllib.request.Request(url=url, headers=headers)
    response = urllib.request.urlopen(request)
    content = response.read().decode('utf8')
    with open('douban_'+str(page)+'.json', 'w', encoding='utf-8') as fp:
        fp.write(content)


start = int(input('请输入起始页'))
end = int(input('请输入结束页'))
for page in range(start, end+1):
    download(page)
    sleep(1)
