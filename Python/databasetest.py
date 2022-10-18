import pymysql
def insert():
    db = pymysql.connect(host="127.0.0.1",user="root",password="wssb",database="zhihu")
    cursor = db.cursor()
    cursor.execute()
    db.commit()
    db.close()
