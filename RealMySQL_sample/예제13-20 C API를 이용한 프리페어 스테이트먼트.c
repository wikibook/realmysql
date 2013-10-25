// --------------------------------------------------------------------------
// connect to mysql server and execute SELECT query
// gcc query_prepare_select.c -o query_prepare_select `mysql_config --cflags --libs`
// --------------------------------------------------------------------------

#include <my_global.h>
#include <mysql.h>
#include <my_sys.h>
#include <m_string.h>

int main(int argc, char **argv){
  char* host_name="localhost";
  char* user_name="root";
  char* user_password="";
  char* database="test";
  char* socket_file="/mysql/MyHome/tmp/mysql.sock";
  unsigned int port_no=3306;
  unsigned int flags=0;

  MYSQL *conn;

  MYSQL_STMT* stmt;
  MYSQL_BIND in_param[1];
  MYSQL_BIND res_param[2];

  char* query = "select article_id, article_title from tb_article where article_id=?";
  int in_param_article_id = 1;
  int res_param_article_id;
  my_bool res_param_article_id_isnull;
  char res_param_article_title[200];
  unsigned long res_param_article_title_real_length;
  my_bool res_param_article_title_isnull;

  MY_INIT(argv[0]);
  if(mysql_library_init(0, NULL, NULL)){
    fprintf(stderr, "Can't load mysql library");
    return;
  }

  conn = mysql_init(NULL);
  if(conn == NULL){
    fprintf(stderr, "Error %u (%s): %s\n", mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    return;
  }

  if(mysql_real_connect(conn, host_name, user_name, user_password, database, 
           port_no, socket_file, flags) == NULL){
    fprintf(stderr, "Can't connect to mysql server\n");
    fprintf(stderr, "Error %u (%s): %s\n", 
        mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_close(conn);
    return;
  }
  fprintf(stdout, "MySQL connected to %s:%d\n", host_name, port_no);

  stmt = mysql_stmt_init(conn);
  if(stmt==NULL){
    fprintf(stderr, "Can't allocate statement handler\n");
    fprintf(stderr, "Error %u (%s): %s\n", 
        mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_close(conn);
    return;
  }

  if(mysql_stmt_prepare(stmt, query, strlen(query)) != 0){
    fprintf(stderr, "Can't prepare statement\n");
    fprintf(stderr, "Error %u (%s): %s\n", 
        mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return;
  }

  memset((void*)in_param, 0, sizeof(in_param));
  in_param[0].buffer_type=MYSQL_TYPE_LONG;
  in_param[0].buffer = (void*) &in_param_article_id;
  in_param[0].is_unsigned = 0;
  in_param[0].is_null = 0;

  if(mysql_stmt_bind_param(stmt, in_param) != 0){
    fprintf(stderr, "Can't bind parameter to prepare statement\n");
    fprintf(stderr, "Error %u (%s): %s\n", 
        mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return;
  }

  memset((void*)res_param, 0, sizeof(res_param));
  res_param[0].buffer_type=MYSQL_TYPE_LONG;
  res_param[0].buffer = (void*) &res_param_article_id;
  res_param[0].is_null = &res_param_article_id_isnull;

  res_param[1].buffer_type=MYSQL_TYPE_STRING;
  res_param[1].buffer = (void*) &res_param_article_title;
  res_param[1].buffer_length= sizeof(res_param_article_title);
  res_param[1].length = &res_param_article_title_real_length;
  res_param[1].is_null = &res_param_article_title_isnull;

  if(mysql_stmt_bind_result(stmt, res_param) != 0){
    fprintf(stderr, "Can't bind result parameter to prepare statement\n");
    fprintf(stderr, "Error %u (%s): %s\n", 
        mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return;
  }

  if(mysql_stmt_execute(stmt) != 0){
    fprintf(stderr, "Can't execute prepare statement\n");
    fprintf(stderr, "Error %u (%s): %s\n", 
        mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return;
  }

  if(mysql_stmt_store_result(stmt) != 0){
    fprintf(stderr, "Can't get prepare statement resultset\n");
    fprintf(stderr, "Error %u (%s): %s\n", 
        mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return;
  }

  fprintf(stdout, "\n\n>> Query result \n");
  while(mysql_stmt_fetch(stmt)==0){
    fprintf(stdout, "%d\t%*.*s\n", res_param_article_id, res_param_article_title_real_length, 
          res_param_article_title_real_length, res_param_article_title);
  }
  mysql_stmt_free_result(stmt);
  mysql_stmt_close(stmt);

  fprintf(stdout, "Close the connection\n");
  mysql_close(conn);
  mysql_library_end();
}
