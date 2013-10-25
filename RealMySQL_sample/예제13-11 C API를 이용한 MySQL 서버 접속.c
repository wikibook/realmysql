// --------------------------------------------------------------------------
// connect to mysql server
// gcc server_connect.c -o server_connect `mysql_config --cflags --libs`
// --------------------------------------------------------------------------

#include <my_global.h>
#include <mysql.h>
#include <my_sys.h>

int main(int argc, char **argv){
  char* host_name="localhost";
  char* user_name="root";
  char* user_password="";
  char* socket_file="/tmp/mysql.sock";
  unsigned int port_no=3306;
  unsigned int flags=0;

  MYSQL *conn;

  MY_INIT(argv[0]);
  if(mysql_library_init(0, NULL, NULL)){
    fprintf(stderr, "Can't load mysql library");
    return;
  }

  conn = mysql_init(NULL);
  if(conn == NULL){
    printf("Error %u (%s): %s\n", mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    return;
  }

  if(mysql_real_connect(conn, host_name, user_name, user_password, NULL, port_no, socket_file, flags) == NULL){
    printf("Can't connect to mysql server\n");
    printf("Error %u (%s): %s\n", mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_close(conn);
    return;
  }

  fprintf(stdout, "MySQL connected to %s:%d\n", host_name, port_no);
  fprintf(stdout, "Close the connection\n");
  mysql_close(conn);
  mysql_library_end();
}
