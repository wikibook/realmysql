import java.sql.*;

public class JDBCTester {
  public static void main(String[] args) {
    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;
    try {
      conn = (new JDBCTester()).getConnection();
      stmt = conn.createStatement();
      rs = stmt.executeQuery("SELECT * FROM employees LIMIT 2");

      while(rs.next()){
        System.out.println("[" + rs.getString(1) + "][" + rs.getString("first_name") + "]");
      }
    }catch(SQLException ex){
      System.out.println("Can't open connection, because " + ex.getMessage());
    }finally{
      try{if(rs!=null){rs.close();}}catch(SQLException ignore){}
      try{if(stmt!=null){stmt.close();}}catch(SQLException ignore){}
      try{if(conn!=null){conn.close();}}catch(SQLException ignore){}
    }
  }

  public Connection getConnection() throws SQLException{
   …
  }
}
