import java.sql.*;

public class JDBCTester {
  public static void main(String[] args) {
    Connection conn = null;
    try {
      conn = (new JDBCTester()).getConnection();
      System.out.println("Connection is ready");

      conn.close();
    }catch(SQLException ex){
      System.out.println("Can't open connection, because " + ex.getMessage());
    }
  }

  public Connection getConnection() throws SQLException {
    String driver = "com.mysql.jdbc.Driver";
    String url = "jdbc:mysql://localhost:3306/test_db";
    String uid = "userid";
    String pwd = "password";
    
    Class.forName(driver).newInstance();
    Connection conn = DriverManager.getConnection(url, uid, pwd);
    
    return conn;
  }
}
