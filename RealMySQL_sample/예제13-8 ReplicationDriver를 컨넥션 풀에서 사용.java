import java.sql.*; 
import javax.sql.DataSource; 
import org.apache.commons.dbcp.BasicDataSource;
 
public class ReplicationDriverTester {
  public static void main(String[] args) throws Exception{
    DataSource ds = prepareDatasource();
    String query = "SELECT NOW()";
    
    Connection conn = ds.getConnection();     // ConnectionPool로부터 Connection을 가져옴
    Statement stmt = conn.createStatement();
    ResultSet rs = stmt.executeQuery(query);
    while(rs.next()){
      System.out.println("  >> Current datetime : "+ rs.getString(idx));
    }
  
    rs.close();
    stmt.close();
    conn.close();
    closeDatasource(ds); 
  }
      
  /* ConnectionPool을 초기화 */
  public static DataSource prepareDatasource() throws Exception{
    /* com.mysql.jdbc.ReplicationDriver 를 사용해도 무방 */
    String driver = "com.mysql.jdbc.Driver";
    /* master_host와 slave_host1, slave_host2 로 구성된 복제된 MySQL 서버의 연결을 위한 URL */
    String url = 
      "jdbc:mysql:replication://master_host:3306,slave_host1:3306,slave_host2:3306/db_name";

    BasicDataSource ds = new BasicDataSource();
    ds.setMaxActive(2);
    ds.setMaxIdle(2);
    ds.setDriverClassName(driver);
    ds.setUsername("account");
    ds.setPassword("password");
    ds.addConnectionProperty("autoReconnect", "true");
    ds.addConnectionProperty("roundRobinLoadBalance", "true");
    ds.setUrl(url);
    
    return ds;
  }
  
  /* ConnectionPool을 종료 */
  public static void closeDatasource(DataSource ds) throws SQLException {
    BasicDataSource bds = (BasicDataSource) ds;
    bds.close();
  }
}
