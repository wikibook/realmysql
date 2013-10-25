SELECT 'Start schema modification' as status;

SELECT 'Create full text index test table' as status;
CREATE TABLE employee_name (
  emp_no int NOT NULL, 
  first_name varchar(14) NOT NULL, 
  last_name varchar(16) NOT NULL, 
  PRIMARY KEY (emp_no), 
  FULLTEXT INDEX fx_name (first_name, last_name)
) ENGINE=MyISAM 
AS SELECT emp_no, first_name, last_name 
FROM employees;


SELECT 'Create query test table' as status;
CREATE TABLE tb_dual (
  fd1 TINYINT NOT NULL, 
  PRIMARY KEY (fd1)
);
INSERT INTO tb_dual VALUES (1);


SELECT 'Delete not used FK and INDEX from salaries table' as status;
ALTER TABLE salaries 
    DROP FOREIGN KEY salaries_ibfk_1, 
    DROP INDEX emp_no, 
    ADD INDEX ix_salary (salary);


SELECT 'Delete not used FK and INDEX from dept_emp table' as status;
ALTER TABLE dept_emp 
    DROP FOREIGN KEY dept_emp_ibfk_1, 
    DROP FOREIGN KEY dept_emp_ibfk_2,
    DROP PRIMARY KEY, 
    DROP INDEX emp_no, 
    DROP INDEX dept_no,
    ADD PRIMARY KEY (dept_no, emp_no),
    ADD INDEX ix_fromdate(from_date),
    ADD INDEX ix_empno_fromdate (emp_no, from_date);


SELECT 'Delete not used FK and INDEX from dept_manager table' as status;
ALTER TABLE dept_manager 
   DROP FOREIGN KEY dept_manager_ibfk_1, 
   DROP FOREIGN KEY dept_manager_ibfk_2,
   DROP INDEX emp_no, 
   DROP INDEX dept_no,
   DROP PRIMARY KEY, 
   ADD PRIMARY KEY (dept_no, emp_no);


SELECT 'Delete not used FK and INDEX from titles table' as status;
ALTER TABLE titles 
   DROP FOREIGN KEY titles_ibfk_1, 
   DROP INDEX emp_no,
   DROP PRIMARY KEY, 
   ADD PRIMARY KEY (emp_no, from_date, title),
   ADD INDEX ix_todate(to_date);


SELECT 'Delete not used FK and INDEX from departments table' as status;
ALTER TABLE departments
  DROP INDEX dept_name,
  ADD INDEX ux_deptname (dept_name); 


-- SELECT 'Create new index to dept_emp table' as status;
-- ALTER TABLE dept_emp 
--   ADD INDEX ix_fromdate(from_date),
--   ADD INDEX ix_empno_fromdate (emp_no, from_date);


-- SELECT 'Create new index to dept_manager table' as status;
-- ALTER TABLE dept_manager 
--   DROP PRIMARY KEY, 
--   ADD PRIMARY KEY (dept_no, emp_no);

-- ALTER TABLE dept_emp 
--   DROP PRIMARY KEY, 
--   ADD PRIMARY KEY (dept_no, emp_no);


SELECT 'Delete not used FK and INDEX from employees table' as status;
ALTER TABLE employees 
  ADD INDEX ix_firstname (first_name), 
  ADD INDEX ix_hiredate(hire_date);

-- ALTER TABLE salaries 
--   ADD INDEX ix_salary (salary);

SELECT 'All schema modification completed' as message;
SHOW TABLES;