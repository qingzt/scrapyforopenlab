1-1
create table test1_student
(sid char(12) not null,
name varchar(10) not null,
sex char(2),
age int,
birthday date,
dname varchar(30),
class varchar(10))

1-2
create table test1_course
(cid char(6) not null,
name varchar(40) not null,
fcid char(6),
credit numeric(4,1))

1-3
create table test1_student_course
(sid char(12) not null,
cid char(6) not null,
score numeric(5,1),
tid char(6),
sctime date)

1-4
insert into test1_student values
(201800020101,'王欣','女',21,to_date('19940202','yyyymmdd'),'计算机学院','2010')

insert into test1_student values
(201800020102,'李华','女',20,to_date('19950303','yyyymmdd'),'软件学院','2009')

1-5
insert into test1_course values
(800001,'数据结构',null,2)

insert into test1_course values
(800002,'数据库',800001,2.5)

1-6
insert into test1_student_course values
(201800020101,300001,91.5,200101,to_date('2009-07-15 09-09-09','yyyy-mm-dd hh24-mi-ss'))

insert into test1_student_course values
(201800020101,300002,92.6,200102,to_date('2009-07-15 10-10-10','yyyy-mm-dd hh24-mi-ss'))