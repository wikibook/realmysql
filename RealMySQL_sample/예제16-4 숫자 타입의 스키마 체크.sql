SELECT table_schema, table_name, column_name, column_type
       FROM information_schema.columns
       WHERE table_schema='employees' AND column_name='%emp_no%';
