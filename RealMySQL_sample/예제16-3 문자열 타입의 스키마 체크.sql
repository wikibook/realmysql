SELECT table_schema, table_name, column_name, column_type, 
              character_set_name, collation_name
       FROM information_schema.columns
       WHERE table_schema='employees' AND column_name='%dept_no%';
