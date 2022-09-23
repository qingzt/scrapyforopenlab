3-1
delete from test3_01
where sid not in 
( select sid
from test3_01
where regexp_like(sid,'^[0-9]*$')
)