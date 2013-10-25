import java.sql.*;

public class JDBCTester {
  public static void main(String[] args) {
    Connection conn = null;
    PreparedStatement pstmt = null;
    ResultSet rs = null;
    try {
      conn = (new JDBCTester()).getConnection();
      pstmt = conn.prepareStatement("SELECT * FROM employees WHERE emp_no=?");
      pstmt.setInt(1, 10001);
      rs = pstmt.executeQuery();
      System.out.println("First name : " + rs.getString("first_name"));
      rs.close();

      pstmt.setInt(1, 10002);
      rs = pstmt.executeQuery();
      System.out.println("First name : " + rs.getString("first_name"));
      rs.close();
      rs = null;
    }catch(SQLException ex){
      System.out.println("Error : " + ex.getMessage());
    }finally{
      try{if(rs!=null){rs.close();}}catch(SQLException ignore){}
      try{if(pstmt!=null){pstmt.close();}}catch(SQLException ignore){}
      try{if(conn!=null){conn.close();})}catch(SQLException ignore){}
    }
  }

  public Connection getConnection() throws SQLException{
   …
  }
}
