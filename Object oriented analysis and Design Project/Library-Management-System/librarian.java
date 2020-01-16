/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classes;

import java.sql.ResultSet;
import java.sql.Statement;
import java.util.*;
import javax.swing.JOptionPane;

/**
 *
 * @author PC
 */

public class librarian extends person{
    public String user_type;
    
    //object of connect class
    connect c=new connect();
    
    //constructor
    public librarian(int id, String name, String cnic, String address, String email, String phone, String t) {
        super(id, name, cnic, address, email, phone);
        user_type=t;
    }
    
    //default constructor
    public librarian()
    {
        super();
    }
    
    //function to add item
    @Override
    public boolean addItem(String isbn, String title, String author, String subject, int type)
    {
        String qry="INSERT INTO BOOKS VALUES("+isbn+",'"+title+"','"+author+"','"+subject+"',"+type+")";
        c.connection();
        try
        {
            c.st.execute(qry);
            JOptionPane.showMessageDialog(null, "The item has been added");
            c.close();
            return true;
        }
        catch(Exception ex)
        {
            JOptionPane.showMessageDialog(null, "The ISBN already exists");
            c.close();
            return false;
        }
    }
    
    //function to delete item
    @Override
    public void deleteItem(int ISBN)
    {
        c.connection();
        try
        {
            c.st.execute("delete from reserve where book=" +ISBN);
            c.st.execute("delete from books where ISBN=" +ISBN);
            JOptionPane.showMessageDialog(null, "The item has been deleted");
        }
        catch(Exception ex)
        {
             System.out.println(ex);
        }
        c.close();
    }
    
    //function to update item
    @Override
    public void updateItem (String isbn, String title, String author, String subject)
    {
        String qry="update books set title = '"+title+"', author = '"+author+"', subject = '"+subject+"' where isbn ="+isbn;
        c.connection();
        try
        {
         c.st.execute(qry);
         JOptionPane.showMessageDialog(null, "The item has been updated");
        }
        catch(Exception ex)
        {
             System.out.println(ex);
        }
    }
    
    //return 2(user_type)
    @Override
    public int userType ()
    {
        return 2;
    }
}
