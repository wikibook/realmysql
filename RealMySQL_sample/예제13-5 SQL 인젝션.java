import java.sql.*;

public class LoginAction {
  public void processLogin(String userid, String password) throws Exception{
    String checkQuery = 
    "SELECT * FROM user WHERE userid='"+userid+"' AND password='"+password+"'";
    
    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;
    try{
      conn = getConnection();
      stmt = conn.createStatement();
      rs = stmt.executeQuery(checkQuery);

      // 실행된 쿼리의 결과를 기준으로 로그인 성공 및 실패 여부 판정
    }catch(SQLException ex){
      // 쿼리 실행 실패에 대한 예외 핸들링
    }finally{
      // ResultSet, Statement, Connection 등의 자원 해제
    }
  }
  
  public Connection getConnection() throws SQLException{
    …
   }
}
