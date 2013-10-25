// --------------------------------------------------------------------------
// connect to mysql server and execute SELECT query
// gcc query_select_multi.c -o query_select_multi `mysql_config --cflags --libs`
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
  unsigned int flags=CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS;

  MYSQL *conn;
  MYSQL_RES* res;
  MYSQL_ROW record;
  int has_more_resultset = -1;
  int resultset_idx=1;

  char* multi_query = "select count(*) as cnt from tb_article;\
        select article_id, article_title, write_ts, modify_ts from tb_article;";

  MY_INIT(argv[0]);
  if(mysql_library_init(0, NULL, NULL)){
    fprintf(stderr, "Can't load mysql library");
    return;
  }

  conn = mysql_init(NULL);
  if(conn == NULL){
    fprintf(stderr, "Error %u (%s): %s\n", 
    		mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    return;
  }

  if(mysql_real_connect(conn, host_name, user_name, user_password, 
  		                 database, port_no, socket_file, flags) == NULL){
    fprintf(stderr, "Can't connect to mysql server\n");
    fprintf(stderr, "Error %u (%s): %s\n", 
    		mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_close(conn);
    return;
  }
  fprintf(stdout, "MySQL connected to %s:%d\n", host_name, port_no);

  if(mysql_query(conn, multi_query)){
    fprintf(stderr, "Can't execute query : %s\n", multi_query);
    fprintf(stderr, "Error %u (%s): %s\n", 
    		mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
  }else{
    do {
      res = mysql_store_result(conn);
      if(res==NULL){
        if(mysql_field_count(conn) == 0){
          fprintf(stdout, "%lld row(s) affected\n", mysql_affected_rows(conn));
        }else{
          fprintf(stderr, "Can't get resultset\n");
          fprintf(stderr, "Error %u (%s): %s\n", 
          		mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
        }
      }else{
          fprintf(stdout, "\n\n>> Query results (index:%d)\n", resultset_idx++);
          while((record=mysql_fetch_row(res))!=NULL){
            fprintf(stdout, "%s\n", (record[0]==NULL) ? "<NULL>" : record[0]);
          }
          mysql_free_result(res);
      }

      if((has_more_resultset = mysql_next_result(conn)) > 0){
        fprintf(stderr, "Can't get resultset\n");
        fprintf(stderr, "Error %u (%s): %s\n", 
        		mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
      }
    }while(has_more_resultset==0);
  }

  fprintf(stdout, "Close the connection\n");
  mysql_close(conn);
  mysql_library_end();
}
