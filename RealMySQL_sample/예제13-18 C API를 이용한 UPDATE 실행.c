// --------------------------------------------------------------------------
// connect to mysql server and execute SELECT query
// gcc query_update1.c -o query_update1 `mysql_config --cflags --libs`
// --------------------------------------------------------------------------

#include <my_global.h>
#include <mysql.h>
#include <my_sys.h>

int main(int argc, char **argv){
  char* host_name="localhost";
  char* user_name="root";
  char* user_password="";
  char* database="test";
  char* socket_file="/mysql/MyHome/tmp/mysql.sock";
  unsigned int port_no=3306;
  unsigned int flags=0;

  MYSQL *conn;
  int affected_row_count=0;

  char* query = "update tb_article set article_title='new article' where article_id=1";

  MY_INIT(argv[0]);
  if(mysql_library_init(0, NULL, NULL)){
    fprintf(stderr, "Can't load mysql library");
    return;
  }

  conn = mysql_init(NULL);
  if(conn == NULL){
    fprintf(stderr, "Error %u (%s): %s\n", mysql_errno(conn), mysql_sqlstate(conn), 
                                           mysql_error(conn));
    return;
  }

  if(mysql_real_connect(conn, host_name, user_name, user_password, database, port_no, socket_file, flags) == NULL){
    fprintf(stderr, "Can't connect to mysql server\n");
    fprintf(stderr, "Error %u (%s): %s\n", mysql_errno(conn), mysql_sqlstate(conn),
                                           mysql_error(conn));
    mysql_close(conn);
    return;
  }
  fprintf(stdout, "MySQL connected to %s:%d\n", host_name, port_no);

  if(mysql_query(conn, query)){
    fprintf(stderr, "Can't execute query : %s\n", query);
    fprintf(stderr, "Error %u (%s): %s\n", mysql_errno(conn), mysql_sqlstate(conn),
                                           mysql_error(conn));
  }else{
    affected_row_count = mysql_affected_rows(conn);
    fprintf(stdout, "%lu row(s) affected\n", (unsigned long)affected_row_count);
  }

  fprintf(stdout, "Close the connection\n");
  mysql_close(conn);
  mysql_library_end();
}
