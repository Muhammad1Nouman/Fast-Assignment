/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classes;

import java.sql.*;
import java.sql.DriverManager;

/**
 *
 * @author PC
 */
public class connect {
   public Connection con;
   public Statement st;
    
    //function to make connection with database
    public void connection ()
    {
        String driver = "org.apache.derby.jdbc.ClientDriver";
        String connection = "jdbc:derby://localhost:1527/lms";
        String user = "anas";
        String password = "123";
        try{
            Class.forName(driver);
            con = DriverManager.getConnection(connection, user, password);
            st = con.createStatement();
        }
        catch (Exception e){
             System.out.println(e);
        }
    }
    
    //function to close connection with database
    public void close()
    {
        try{
            con.close();
        }
        catch(Exception e)
        {
             System.out.println(e);
        }
    }

    
}
