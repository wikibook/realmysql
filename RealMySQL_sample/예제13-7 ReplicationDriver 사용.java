import java.sql.*;
import java.util.*;

import com.mysql.jdbc.ReplicationDriver;

public class ReplicationDriverTester{
  public static void main(String[] args) throws Exception {
    ReplicationDriver driver = new ReplicationDriver();

    Properties props = new Properties();

    // 만약 연결이 끊어진 경우에는 자동으로 재 접속하도록 설정
    props.put("autoReconnect", "true");

    // 슬레이브가 여러 개인 경우에는 Round-robin으로 사용하도록 설정
    props.put("roundRobinLoadBalance", "true");

    props.put("user", "mysql_account");
    props.put("password", "mysql_password");

    // ReplicationDriver를 위해서는 컨넥션 스트링의 제일 앞쪽 프로토콜 부분을 
    //     "jdbc:mysql:replication://" 로 설정한다.
    // 프로토콜 뒤에 첫번째 호스트명이나 IP는 마스터 MySQL을 반드시 기재하고,
    //     그 뒤에는 슬레이브 MySQL의 호스트명이나 IP 주소를 기재하는데, 
    //     슬레이브가 여러개인 경우에는 콤마로 구분해서 기재한다.
    // 나머지 부분은 일반적인 MySQL JDBC Driver와 동일하다.
    Connection conn =
        driver.connect("jdbc:mysql:replication://master,slave1,slave2,slave3/test", props);

    // 컨넥션의 속성에서 읽기 전용을 해제하면 마스터 MySQL로 쿼리가 전송된다.
    conn.setReadOnly(false);
    conn.setAutoCommit(false);
    conn.createStatement().executeUpdate("DELETE FROM master_table WHERE ...");
    conn.commit();

    // 컨넥션의 속성을 읽기 전용(ReadOnly)로 설정하면 슬레이브 MySQL로 쿼리가 전송된다.
    conn.setReadOnly(true);
    ResultSet rs =
      conn.createStatement().executeQuery("SELECT fd1, fd2 FROM slave_table WHERE ...");

    // 나머지 처리 코드 ...
  }
}
