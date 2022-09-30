5-1
create table test5_01
(
    First_name varchar(4),
    frequency numeric(4)
)

insert into test5_01
    select substr(name,2,2),count(*)
    from pub.student
    group by substr(name,2,2)

5-2
create table test5_02
(letter varchar(2),
frequency numeric(4))

insert into test5_02
    select letter,count(*)
    from(
        (select substr(name,2,1) letter
        from pub.student)
        union
        (select substr(name,3,1) letter
        from pub.student)
    )
    where letter is not null
    group by letter

5-3
create table test5_03
(Dname varchar(30),
class varchar(10),
P_count1 Int,
P_count2 int,
P_count int)

select dname,class,count(*) p_count1,null as p_count2,( 
    select count(*) 
    from pub.student st 
    where st.dname=s.dname 
    and st.class=s.class ) as p_count 
from pub.student s 
where sid in( 
    select sid 
    from pub.student_course natural join pub.course 
    where score>=60 
    group by sid 
    having sum(credit)>=10 ) 
and dname is not null 
group by dname,class



5-4
create table test5_04
(Dname varchar(30),
class varchar(10),
P_count1 Int,
P_count2 int,
P_count int)

insert into test5_04
    select dname,class,count(*) as p_count
    from pub.student
    where dname is not null
    group by dname,class



update test5_04 set p_count1=(
    select count(*)
    from(
        select sid,dname,class
        from pub.student
        where sid in(
            select sc.sid
            from pub.student_course sc natural join pub.course,pub.student
            where score>=60 
            and class>2008
            and sc.sid=pub.student.sid
            group by sc.sid
            having sum(credit)>=10
        )
        and dname is not null
    ) d
    where d.dname=test5_04.dname
    and d.class=test5_04.class
    group by dname,class
)
where p_count1 is null


update test5_04 set p_count1=(
    select count(*)
    from(
        select sid,dname,class
        from pub.student
        where sid in(
            select sc.sid
            from pub.student_course sc natural join pub.course,pub.student
            where score>=60 
            and class<=2008
            and sc.sid=pub.student.sid
            group by sc.sid
            having sum(credit)>=8
        )
        and dname is not null
    ) d
    where d.dname=test5_04.dname
    and d.class=test5_04.class
    group by dname,class
)
where p_count1 is null

update test5_04 set p_count2=p_count-p_count1

5-5
create table test5_05
(Dname varchar(30),
avg_ds_score int,
avg_os_score int
)

insert into test5_05(dname)
    select dname
    from pub.student
    where dname is not null


update test5_05 set avg_ds_score=(
    select avg(score)
    from(
        select sid,(
            select max(score)
            from pub.student_course sc1
            where sc1.sid=sc.sid
            and sc1.cid=300002
        ) score
        from pub.student_course sc
        where cid=300002
    ) natural join pub.student st
    where dname is not null
    and st.dname = test5_05.dname
)

update test5_05 set avg_os_score=(
    select avg(score)
    from(
        select sid,(
            select max(score)
            from pub.student_course sc1
            where sc1.sid=sc.sid
            and sc1.cid=300005
        ) score
        from pub.student_course sc
        where cid=300005
    ) natural join pub.student st
    where dname is not null
    and st.dname = test5_05.dname
)

select dname,(
    select round(avg(score),0)
    from(
        select distinct sid,(
            select max(score)
            from pub.student_course sc1
            where sc1.sid=sc.sid
            and sc1.cid=300002
        ) score
        from pub.student_course sc
        where cid=300002
    ) natural join pub.student st
    where dname is not null
    and st.dname =s.dname
) as avg_ds_score
,(
    select round(avg(score),0)
    from(
        select distinct sid,(
            select max(score)
            from pub.student_course sc1
            where sc1.sid=sc.sid
            and sc1.cid=300005
        ) score
        from pub.student_course sc
        where cid=300005
    ) natural join pub.student st
    where dname is not null
    and st.dname = s.dname
)as avg_os_score
from pub.student s
where dname is not null

5-6
select sid,name,dname,(
    select max(score)
    from pub.student_course sc
    where sc.sid=s.sid
    and sc.cid=300002
) as ds_score,(
    select max(score)
    from pub.student_course sc
    where sc.sid=s.sid
    and sc.cid=300005
) as os_score
from (
    (select distinct sid,name,dname
    from pub.student_course natural join pub.student
    where cid=300002)
    intersect
    (
    select distinct sid,name,dname
    from pub.student_course natural join pub.student
    where cid=300005
    )
) s
where dname='计算机科学与技术学院'

5-7
Create or replace view test5_07 as
select sid,name,dname,(
    select max(score)
    from pub.student_course sc
    where sc.sid=s.sid
    and sc.cid=300002
) as ds_score,(
    select max(score)
    from pub.student_course sc
    where sc.sid=s.sid
    and sc.cid=300005
) as os_score
from (
    (select distinct sid,name,dname
    from pub.student_course natural join pub.student
    where cid=300002)
    union
    (
    select distinct sid,name,dname
    from pub.student_course natural join pub.student
    where cid=300005
    )
) s
where dname='计算机科学与技术学院'

5-8
Create or replace view test5_08 as
select sid,name,dname,(
    select max(score)
    from pub.student_course sc
    where sc.sid=s.sid
    and sc.cid=300002
) as ds_score,(
    select max(score)
    from pub.student_course sc
    where sc.sid=s.sid
    and sc.cid=300005
) as os_score
from pub.student s
where dname='计算机科学与技术学院'

5-9
select score,count(*) as count1,(
    select count(*)
    from pub.student_course
    where score>=60
) as count0,
round(count(*)*100/(
    select count(*)
    from pub.student_course
    where score>=60
),2) as percentage
from pub.student_course
where score>=60
group by score

5-10
Create or replace view test5_10 as
select c.cid,name cname,(
    case trunc(score,-1) 
        when 60 then '60-69'
        when 70 then '70-79'
        when 80 then '80-89'
        ELSE '90-99'
        END
)as score,count(*) as count1,(
    select count(*)
    from pub.student_course sc
    where sc.cid=c.cid
    and score>=60
    and score<=99
) as count0,round(count(*)*100/(select count(*)
    from pub.student_course sc
    where sc.cid=c.cid
    and score>=60
    and score<=99),2) as percentage 
from pub.student_course scc join pub.course c on scc.cid=c.cid 
where score>=60
and score<=99
group by trunc(score,-1),name,c.cid