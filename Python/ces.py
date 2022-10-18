import datetime


table_name = str(datetime.datetime.now()).replace(' ', '').replace('-','').replace(':', '').replace('.', '')[:14]
createSQL = 'create table '+table_name+' select * from zhihu'
print(createSQL)
