import java.sql.*;

public class JDBCTester {
  public static void main(String[] args) {
    Connection conn = null;
    Statement stmt = null;
    int affectedRowCount = 0;
    try {
      conn = (new JDBCTester()).getConnection();
      conn.setAutoCommit(false);
      stmt = conn.createStatement();
      affectedRowCount = stmt.executeQuery(
        "UPDATE employees SET first_name='Lee' WHERE emp_no=10001");

      if(affectedRowCount=1){
        System.out.println("사원명이 변경되었습니다.");
        conn.commit();
      }else{
        System.out.println("사원을 찾을 수 없습니다.");
        conn.rollback();
      }
    }catch(SQLException ex){
      System.out.println("처리 중 오류 발생 : " + ex.getMessage());
      try{if(conn!=null){conn.rollback();}}catch(SQLException ignore){}

    }finally{
      try{if(stmt!=null){stmt.close();}}catch(SQLException ignore){}
      try{if(conn!=null){conn.close();})}catch(SQLException ignore){}
    }
  }

  public Connection getConnection() throws SQLException{
   …
  }
}
