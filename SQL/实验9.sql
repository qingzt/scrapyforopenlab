9-1
create table test9_01 as select * from pub.student_11_1 where sid<0

insert into test9_01
    select *
    from pub.student
    where sex='女'

insert into test9_01
    select *
    from pub.student_11_1
    where sex='女'
    and sid not in (
        select sid
        from test9_01
    )

insert into test9_01
    select *
    from pub.student_11_2
    where sex='女'
    and sid not in (
        select sid
        from test9_01
    )

create index sidindex on test9_01(sid)

9-2
create table test9_02 as select * from pub.student_11_1 where sid<0

insert into test9_02
    select sid,name,sex,age,birthday,dname,class
    from pub.student natural join pub.student_course
    where sex='女'
    and score<60

insert into test9_02
    select sid,name,sex,age,birthday,dname,class
    from pub.student_11_1 natural join pub.student_course
    where sex='女'
    and score<60
    and sid not in(
        select sid
        from test9_02
    )

insert into test9_02
    select sid,name,sex,age,birthday,dname,class
    from pub.student_11_2 natural join pub.student_course
    where sex='女'
    and score<60
    and sid not in(
        select sid
        from test9_02
    )

create index sidindex2 on test9_02(sid)
    