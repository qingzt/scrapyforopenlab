6-1
create or replace view test6_01 as
select sid,name,dname
from pub.student
where dname='物理学院'
and age<20
order by sid

6-2
create or replace view test6_02 as
select s.sid,name,sum(score) sum_score
from pub.student s left join pub.student_course sc on s.sid=sc.sid
where class=2009
and dname='软件学院'
group by s.sid,name

6-3
create or replace view test6_03 as
select s.sid,name,score
from pub.student s left join pub.student_course sc on s.sid=sc.sid
where class=2010
and dname='计算机科学与技术学院'
and cid=300005

6-4
create or replace view test6_04 as
select sid,name
from pub.student
where sex='男'
and sid in (((
    select sid
    from pub.student_course
    where cid=300005
    and score>=60
)
union
(
    select sid
    from pub.student_course
    where cid=300002
    and score>=60
))
minus
(
    select sid
    from pub.student_course
    where cid=300001
    and score>=60
)
)

6-5
create or replace view test6_05 as
select s.sid,c.cid,c.name,sc.score
from pub.student_course sc join pub.course c on sc.cid=c.cid
join pub.student s on sc.sid=s.sid 
where s.name='李龙'

6-6
create or replace view test6_06 as
select sid,name
from pub.student s
where not exists(
    (select cid
    from pub.course)
    minus
    (select cid
    from pub.student_course sc
    where sc.sid=s.sid)
)

6-7
create or replace view test6_07 as
select s.sid,name
from pub.student s join pub.student_course sc on s.sid=sc.sid
where not exists(
    (select cid
    from pub.course)
    minus
    (select cid
    from pub.student_course sc
    where sc.sid=s.sid)
)
group by s.sid,name
having min(score)>=60

6-8
create or replace view test6_08 as
select distinct s.sid,name
from pub.student s join pub.student_course sc on s.sid=sc.sid
where not exists(
    (select cid
    from pub.course)
    minus
    (select cid
    from pub.student_course sc
    where sc.sid=s.sid)
)
and s.sid not in
(
    select s.sid
    from pub.student s join pub.student_course sc on s.sid=sc.sid
    where not exists(
    (select cid
    from pub.course)
    minus
    (select cid
    from pub.student_course sc
    where sc.sid=s.sid)
    )
    group by s.sid,name,cid
    having max(score)<60
)

6-9
create or replace view test6_09 as
select s.sid,s.name,sum(credit) sum_credit
from pub.student s join pub.student_course sc on s.sid=sc.sid
join pub.course c on sc.cid=c.cid
where s.class=2010
and s.dname='化学与化工学院'
and score>=60
group by s.sid,s.name

6-10
create or replace view test6_10 as
select cid,name
from pub.course c
where fcid in(
    select cid
    from pub.course
    where fcid is not null 
)