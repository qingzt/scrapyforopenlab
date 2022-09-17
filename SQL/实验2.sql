2-1
Create or replace view test2_01 as
(select pub.student.sid,pub.student.name
from pub.student)
minus
(select pub.student.sid,pub.student.name
from pub.student,pub.student_course
where pub.student.sid=pub.student_course.sid)

2-2
测试？