import java.sql.*; 
import javax.sql.DataSource; 
import org.apache.commons.dbcp.BasicDataSource;
 
public class ReplicationDriverTester {
  public static void main(String[] args) throws Exception{
    DataSource ds = prepareDatasource();
    String query = "SELECT NOW()";
    
    Connection conn = ds.getConnection();
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
      
  public static DataSource prepareDatasource() throws Exception{
    String driver = "com.mysql.jdbc.Driver"; // com.mysql.jdbc.ReplicationDriver 를 사용해도 무방
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
    ds.setValidationQuery("/* ping */ SELECT 1");
    ds.setUrl(url);
    
    return ds;
  }
  
  public static void closeDatasource(DataSource ds) throws SQLException {
    BasicDataSource bds = (BasicDataSource) ds;
    bds.close();
  }
}
