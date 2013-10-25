SELECT
  emp_no, first_name, last_name,
  IF(@prev_firstname=first_name, 
       @rank:=@rank +1, @rank:=1+LEAST(0,@prev_firstname:=first_name)) rank
FROM employees, (SELECT @rank:=0) x1, (SELECT @prev_firstname:='') x2
WHERE first_name IN ('Georgi','Bezalel')
ORDER BY first_name, last_name;