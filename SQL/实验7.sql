7-1
CREATE INDEX firstnameindex
ON test7_01(substr(name,1,1))

7-2
CREATE INDEX nameandbirthay
on test7_02(birthay,name)

7-3
select * from
(select sid,name,birthday,
    (select count(*) from pub.student
    where name like concat(substr(t1.name,1,1),'%')
    ) samefirstname 
    from pub.student_testindex t1)
where samefirstname=7

7-4
select * from 
(select sid,name,birthday,
(select count(*) from pub.student 
where birthday between(trunc(t1.birthday,'mm'))and last_day(t1.birthday)
) sameyearmonth,
(select count(*) from pub.student 
where birthday between(trunc(t1.birthday,'yyyy'))and add_months(trunc(t1.birthday,'yyyy'),12)-1
) sameyear
 from pub.student_testindex t1) where sameyearmonth=35

7-5
select * from 
(select sid,name,birthday,
(select count(*) from pub.student 
where birthday=t1.birthday+1
) nextbirthday
from pub.student_testindex t1) where nextbirthday=7