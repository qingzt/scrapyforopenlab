2-1
Create or replace view test2_01 as
(select pub.student.sid,pub.student.name
from pub.student)
minus
(select pub.student.sid,pub.student.name
from pub.student,pub.student_course
where pub.student.sid=pub.student_course.sid)

2-2
Create or replace view test2_02 as  select sid,name
from pub.student
where sid<>'200900130417'
and sid in(
    select sid
    from pub.student_course
    where cid=some(
        select cid
        from pub.student_course
        where sid='200900130417'
    )
)

2-3
Create or replace view test2_03 as
select sid,name
from pub.student
where sid in(
    select sid
    from pub.student_course
    where cid=some(
        select cid
        from pub.course
        where fcid='300002'
    )
)

2-4
Create or replace view test2_04 as
select sid,name
from pub.student
where sid in(
    (
        (
            select sid
            from pub.student_course
            where cid='300005'
        )
        intersect
        (
            select sid
            from pub.student_course
            where cid='300002'
        )
    )
    minus
    (
        select sid
        from pub.student_course
        where cid='300001'
    )
)

2-5
Create or replace view test2_05 as
select sid,name,round(avg(score),0) as avg_score,sum(score) as sum_score
from pub.student natural join pub.student_course
where age=20
group by sid,name

2-6
Create or replace view test2_06 as
select cid,name,max(score) as max_score,
(
    select count(distinct sid)
    from pub.student_course c
    where c.cid=a.cid
    and c.score=(
        select max(score)
        from pub.student_course d
        where d.cid=c.cid
    )
) as max_score_count
from 
(select * from pub.student_course natural join pub.course) a
group by cid,name

2-7
Create or replace view test2_07 as
select sid,name
from pub.student
where name not like '王%'
and name not like '张%'
and name not like '李%'

2-8
Create or replace view test2_08 as
select substr(name,0,1) as second_name,count(*) as p_count
from pub.student
group by substr(name,0,1)

2-9
Create or replace view test2_09 as
select sid,name,score
from pub.student natural join pub.student_course
where cid=300003

2-10
Create or replace view test2_10 as
select distinct sid,name
from pub.student
where sid in
(
    select sid
    from pub.student_course
    where score<60
    group by sid,cid
    having count(*)>1
)