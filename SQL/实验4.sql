4-1
alter table test4_01 add sum_score int

update test4_01 a
set sum_score=
(
    select sum(score)
    from pub.student_course,test4_01
    where pub.student_course.sid=test4_01.sid
    and a.sid=test4_01.sid
    group by test4_01.sid
)

4-2
alter table test4_02 add avg_score numeric(3,1)

update test4_02 a
set avg_score=
(
    select avg(score)
    from pub.student_course,test4_02
    where pub.student_course.sid=test4_02.sid
    and a.sid=test4_02.sid
)

4-3
alter table test4_03 add sum_credit int

update test4_03 a
set sum_credit=
(
    select sum(credit)
    from (
        select sid,cid,max(score) as score
        from pub.student_course
        group by sid,cid
    ) b,test4_03,pub.course
    where b.sid=test4_03.sid
    and b.cid=pub.course.cid
    and b.score>=60
    and a.sid=test4_03.sid
)

4-4
update test4_04 a
set dname=
(
    select did
    from  (
        select distinct did,test4_04.dname
        from pub.department,test4_04
        where test4_04.dname=pub.department.dname) b
    where a.dname=b.dname
)
where a.dname in(
    select dname
    from (
        select distinct did,test4_04.dname
        from pub.department,test4_04
        where test4_04.dname=pub.department.dname)
)

4-5
alter table test4_01 add sum_score int

alter table test4_05 add avg_score numeric(3,1)

alter table test4_05 add sum_credit real

alter table test4_05 add did varchar(2)

update test4_05 a
set sum_score=
(
    select sum(score)
    from pub.student_course,test4_05
    where pub.student_course.sid=test4_05.sid
    and a.sid=test4_05.sid
    group by test4_05.sid
)

update test4_05 a
set avg_score=
(
    select avg(score)
    from pub.student_course,test4_05
    where pub.student_course.sid=test4_05.sid
    and a.sid=test4_05.sid
)

update test4_05 a
set sum_credit=
(
    select sum(credit)
    from (
       select sid,cid,max(score) as score
        from pub.student_course
        group by sid,cid
    ) b,test4_05,pub.course
    where b.sid=test4_05.sid
    and b.cid=pub.course.cid
    and b.score>=60
    and a.sid=test4_05.sid
)

update test4_05 a
set did='00'

update test4_05 a
set did=
(
    select did
    from  (
        select distinct depart.did,test4_05.dname
        from test4_05,((select *
            from pub.department_41)
            union
            (select *
            from pub.department)) depart
        where test4_05.dname=depart.dname) b
    where a.dname=b.dname
)
where a.dname in(
    select dname
    from (
        select distinct depart.did,test4_05.dname
        from test4_05,((select *
            from pub.department_41)
            union
            (select *
            from pub.department)) depart
        where test4_05.dname=depart.dname)
)

4-6
update test4_06
set name=replace(name,' ','')

4-7
update test4_07
set sex='男'
where regexp_like(sex,'男+')

update test4_07
set sex='女'
where regexp_like(sex,'女+')

4-8
update test4_08
set class=replace(class,'级','')

4-9
update test4_09
set age=2012-extract(year from birthday)
where age is null

4-10
update test4_10
set name=replace(name,' ','')

update test4_10
set dname=replace(dname,' ','')

update test4_10
set sex='男'
where regexp_like(sex,'男+')

update test4_10
set sex='女'
where regexp_like(sex,'女+')

update test4_10
set class=replace(class,'级','')

update test4_10
set age=2012-extract(year from birthday)
where age is null