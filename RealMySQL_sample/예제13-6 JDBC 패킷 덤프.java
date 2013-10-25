import java.io.*;
import java.util.*;
import java.sql.*;
import org.apache.log4j.PropertyConfigurator;

public class ConnectorProtocolTracer {
  public static void main(String[] args) throws Exception {
    initializeLogger();
    for (int idx = 0; idx < 1; idx++) {
      System.out.println("Connection trying .. ");
      Connection conn = getConnection();
      System.out.println("Connection established ..");
      conn.close();
    }
  }
  
  protected static void initializeLogger() {
    String log4jConfig = "log4j.rootCategory=DEBUG,console\n"
        + "log4j.appender.console=org.apache.log4j.ConsoleAppender\n"
        + "log4j.appender.console.layout=org.apache.log4j.PatternLayout\n"
        + "log4j.appender.console.layout.ConversionPattern=[%d TH:%t LV:%5p CL:%c] %m%n\n";
    InputStream is = null;
    try {
      is = new ByteArrayInputStream(log4jConfig.getBytes("UTF-8"));
      Properties prop = new Properties();
      prop.load(is);
      PropertyConfigurator.configure(prop);
    } catch (Exception ex) {
      throw new IllegalArgumentException("Logger configuration parse failed : " + ex.toString());
    } finally {
      try {is.close();} catch (Exception ignore) {}
    }
    
    System.out.println(">> Logger initialized");
  }

  protected static Connection getConnection() throws Exception {
    String driver = "com.mysql.jdbc.Driver";
    String url = "jdbc:mysql://localhost:3306/db_name?logger=Log4JLogger&traceProtocol=true";
    String uid = "userid";
    String pwd = "password";

    Class.forName(driver).newInstance();
    Connection conn = DriverManager.getConnection(url, uid, pwd);

    return conn;
  }
}
