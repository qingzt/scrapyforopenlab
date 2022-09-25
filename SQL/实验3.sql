3-1
delete from test3_01
where sid not in 
( select sid
from test3_01
where regexp_like(sid,'^[0-9]*$')
)

3-2
delete from test3_02
where 2012-extract(year from birthday)<>age

3-3
delete from test3_03
where sex<>'男'
and sex<>'女'
and sex is not null

3-4
delete from test3_04
where dname is null
or regexp_like(dname,'[ ]')
or dname in( select substr(dname,0,2)
from test3_04)

3-5
delete from test3_05
where class in(
    select class
    from test3_05
    where class not in(select class
        from test3_05
        where regexp_like(class,'^[0-9]{4}$')
    )
)

3-6
delete
from test3_06
where  sid not in 
    (select sid
    from test3_01
    where regexp_like(sid,'^[0-9]*$')
    )
or 2012-extract(year from birthday)<>age
or dname is null
or regexp_like(dname,'[ ]')
or dname in( 
    select substr(dname,0,2)
    from test3_04)
or class not in(select class
        from test3_05
        where regexp_like(class,'^[0-9]{4}$')
)
or sex in (
    select sex 
    from test3_06
    where sex<>'男'
    and sex<>'女'
    and sex is not null
)
or regexp_like(name,'[ ]')
or length(name)<2

3-7
delete
from test3_07
where sid not in(
    select sid
    from pub.student
)

3-8
delete
from test3_08
where tid not in(
    select tid
    from pub.teacher_course
    where pub.teacher_course.tid=test3_08.tid
    and pub.teacher_course.cid=test3_08.cid
)
or cid not in(
    select cid
    from pub.teacher_course
    where pub.teacher_course.tid=test3_08.tid
    and pub.teacher_course.cid=test3_08.cid
)
or tid not in(
    select tid
    from pub.teacher_course
)
or cid not in (
    select cid
    from pub.teacher_course
)