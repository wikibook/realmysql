import java.sql.*;
import java.util.*;
import com.mysql.jdbc.ReplicationDriver;

public class ReplicationDriverTester{
  public static void main(String[] args) throws Exception {
    ReplicationDriver driver = new ReplicationDriver();

    Properties props = new Properties();

    // 만약 연결이 끊어진 경우에는 자동으로 재 접속하도록 설정
    props.put("autoReconnect", "true");

    // loadBalanceStrategy 옵션에는 "bestResponseTime"이나 "random" 을 사용 가능한데,
    // "bestResponseTime"는 이전 트랜잭션에서 처리가 가장 빨랐던 MySQL Cluster 서버로 연결을 유도
    // "random" 은 각 요청별로 임의의 MySQL Cluster로 연결을 유도
    props.put("loadBalanceStrategy", "bestResponseTime");

    props.put("user", "mysql_account");
    props.put("password", "mysql_password");

    // Cluster를 위한 ReplicationDriver를 위해서는 컨넥션 스트링의 제일 앞쪽 프로토콜 부분을 
    //     "jdbc:mysql::loadbalance//" 로 설정한다.
    // 프로토콜 뒤에 첫번째 호스트명이나 IP는 마스터 MySQL을 반드시 기재하고,
    //     그 뒤에는 Cluster에 소속된 MySQL의 호스트명이나 IP 주소를 기재해주면 된다.
    // 나머지 부분은 일반적인 MySQL JDBC Driver와 동일하다.
    Connection conn = driver.connect(
      "jdbc:mysql:loadbalance://cluster_host1:port,cluster_host2:port/test", props);

    conn.setAutoCommit(false);
    conn.createStatement().executeUpdate("DELETE FROM master_table WHERE ...");
    conn.commit();

    // 나머지 처리 코드 ...
  }
}
