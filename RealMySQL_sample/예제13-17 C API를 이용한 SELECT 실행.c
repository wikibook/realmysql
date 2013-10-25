// --------------------------------------------------------------------------
// connect to mysql server and execute SELECT query
// gcc query_select.c -o query_select `mysql_config --cflags --libs`
// --------------------------------------------------------------------------

#include <my_global.h>
#include <mysql.h>
#include <my_sys.h>

int main(int argc, char **argv){
  char* host_name="localhost";  // 접속할 MySQL 서버가 설치된 호스트의 이름이나 IP
  char* user_name="root";       // MySQL 사용자 계정
  char* user_password="";       // MySQL 사용자 비밀번호
  char* database="test";        // 접속 후, 사용할 DB 명
  char* socket_file="/tmp/mysql.sock"; // MySQL 소켓 파일의 경로
  unsigned int port_no=3306;           // MySQL 서버 접속 포트
  unsigned int flags=0;                // MySQL 접속시 사용할 옵션. 기본적으로 특별히 설정 없음

  MYSQL *conn;               // MySQL 컨넥션 핸들러 (포인터)
  MYSQL_RES* res;            // SELECT 쿼리 결과 셋의 핸들러 (포인터)
  MYSQL_ROW record;          // 결과 셋의 레코드를 임시로 담아 둘 레코드 핸들러 (포인터)

  // mysql_query() 함수를 이용해서 실행할 쿼리 문장
  char* query = "SELECT article_id, article_title, write_ts, modify_ts FROM tb_article";
  int row_count=0; // 결과 셋의 레코드 건수를 저장할 변수
  int col_count=0; // 결과 셋의 컬럼 건수를 저장할 변수

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

  if(mysql_real_connect(conn, host_name, user_name, user_password, 
                                 database, port_no, socket_file, flags) == NULL){
    fprintf(stderr, "Can't connect to mysql server\n");
    fprintf(stderr, "Error %u (%s): %s\n", 
          mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    mysql_close(conn);
    return;
  }
  fprintf(stdout, "MySQL connected to %s:%d\n", host_name, port_no);

  if(mysql_query(conn, query)){
    fprintf(stderr, "Can't execute query : %s\n", query);
    fprintf(stderr, "Error %u (%s): %s\n", 
          mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
  }else{
    res = mysql_store_result(conn);
    if(res==NULL){
      fprintf(stderr, "Can't get resultset\n");
      fprintf(stderr, "Error %u (%s): %s\n", 
          mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
    }else{
      col_count = mysql_num_fields(res);
      fprintf(stdout, "\n\n>> Query results\n");
      while((record=mysql_fetch_row(res))!=NULL){
        int cidx=0;
        for(cidx=0; cidx<col_count; cidx++){
          fprintf(stdout, "%s\t", (record[cidx]==NULL) ? "<NULL>" : record[cidx]);
        }
        fprintf(stdout, "\n");
      }

      if(mysql_errno(conn) != 0){
        fprintf(stderr, "Can't fetch record\n");
        fprintf(stderr, "Error %u (%s): %s\n", 
            mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
      }else{
        row_count = mysql_num_rows(res);
        fprintf(stdout, "\n%lu row(s) in set", (unsigned long)row_count);
      }
    }

    mysql_free_result(res);
  }

  fprintf(stdout, "Close the connection\n");
  mysql_close(conn);
  mysql_library_end();
}
