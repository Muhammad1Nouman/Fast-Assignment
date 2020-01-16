/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classes;

import java.sql.*;
import javax.swing.*;
import swing.*;
import java.util.*;
import javax.swing.table.*;

/**
 *
 * @author PC
 */
public class login {
    
    //lists of person, item, loan nad reserve
    public List <person> B_list = new ArrayList <person> ();
    public List <item> I_list = new ArrayList <item> ();
    public List<Loan> l_Loan =new ArrayList<Loan>();
    public List<reserve> l_reseve=new ArrayList<reserve>();
    public String username;
    
    //function to signin
    public void signin (String username , String password , int type , Home h)
    {
        connect c = new connect();
        c.connection();

        //if borrower is pressed
        if(type==0){
            String result = "select * from login l join users u on l.user_id = u.user_id where l.username='"+username+"'and l.password='" +password +"'and u.user_type="+0;
            ResultSet rs;
            try{
                rs = c.st.executeQuery(result);
                rs.next();
                if(rs.getRow()==1){       
                    Borrower b = new Borrower();
                    b.br.name=rs.getString("name");
                    b.br.cnic=rs.getString("cnic");
                    b.br.email=rs.getString("email");
                    b.br.address=rs.getString("address");
                    b.br.phone=rs.getString("phone");
                    b.Login.I_list = getItem ();
                    b.Login.B_list = getPerson();
                    b.Login.l_Loan=getLoan();
                    b.Login.l_reseve=getResevedBooks();
                    b.username=username;
                    b.setprofile();
                    b.setVisible(true);
                    h.dispose();
                }
                else{
                    JOptionPane.showMessageDialog(null, "wrong credentials");
                    
                }
            }
            catch(Exception e){ 
                System.out.println(e);
                c.close();
            }
        }
        //if clerk is pressed
        else if (type==1){
            String result = "select * from login l join users u on l.user_id = u.user_id where l.username='"+username+"'and l.password='" +password +"'and u.user_type="+1;
            ResultSet rs;
            try{
                rs = c.st.executeQuery(result);
                rs.next();
                if(rs.getRow()==1){       
                    Clerk b = new Clerk();
                    b.cl.name=rs.getString("name");
                    b.cl.cnic=rs.getString("cnic");
                    b.cl.email=rs.getString("email");
                    b.cl.address=rs.getString("address");
                    b.cl.phone=rs.getString("phone");
                    b.Login.I_list = getItem();
                    b.Login.B_list = getPerson();
                    b.Login.l_Loan=getLoan();
                    b.Login.l_reseve=getResevedBooks();
                    b.username=username;
                    b.setprofile();                    
                    b.setVisible(true);
                    h.dispose();
                }
                else{
                    JOptionPane.showMessageDialog(null, "wrong credentials");
                    
                }
            }
            catch(Exception e){ 
                System.out.println(e);
                c.close();
            }
        }
        //if librarian is pressed
        else{
            String result = "select * from login l join users u on l.user_id = u.user_id where l.username='"+username+"'and l.password='" +password +"'and u.user_type="+2;
            ResultSet rs;
            try{
                rs = c.st.executeQuery(result);
                rs.next();
                if(rs.getRow()==1){       
                    Librarian b = new Librarian();
                    b.lb.name=rs.getString("name");
                    b.lb.cnic=rs.getString("cnic");
                    b.lb.email=rs.getString("email");
                    b.lb.address=rs.getString("address");
                    b.lb.phone=rs.getString("phone");
                    b.Login.I_list = getItem();
                    b.Login.B_list = getPerson();
                    b.Login.l_Loan=getLoan();
                    b.Login.l_reseve=getResevedBooks();
                    b.username=username;
                    b.setprofile();
                    b.setVisible(true);
                    h.dispose();
                }
                else{
                    JOptionPane.showMessageDialog(null, "wrong credentials");
                    
                }
            }
            catch(Exception e){ 
                System.out.println(e);
                c.close();
            }
        }
    }
    
    //function to display data in grid
    public static DefaultTableModel buildTableModel(ResultSet rs) throws SQLException {

        ResultSetMetaData metaData = rs.getMetaData();

        // names of columns
        Vector<String> columnNames = new Vector<String>();
        int columnCount = metaData.getColumnCount();
        for (int column = 1; column <= columnCount; column++) {
            columnNames.add(metaData.getColumnName(column));
        }

        // data of the table
        Vector<Vector<Object>> data = new Vector<Vector<Object>>();
        while (rs.next()) {
            Vector<Object> vector = new Vector<Object>();
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                vector.add(rs.getObject(columnIndex));
            }
            data.add(vector);
        }

        return new DefaultTableModel(data, columnNames);

    }

    //this function returns the items the user has searched
    public ResultSet searchBook(String st , String text , int type) {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        connect c = new connect();
        c.connection();
        String query = "select * from books where " +st+ " like '%" +text+ "%' and type =" +type;
        try {
            return  c.st.executeQuery(query);
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        return null;
    }
    
    //function for counting number of books availed by a particualr borrower
    public int getNumberOfBorrowedBooks(String user)
    {
        String qry="SELECT COUNT(BOOK) as TotalBorrowedBooks from borrow where user_id="+user+ " and status = true";
        connect c = new connect();
        c.connection();  
        try
        {
            ResultSet rs=c.st.executeQuery(qry);
            rs.next();
            int numberOfBorrowedbooks= rs.getInt("TotalBorrowedBooks");
            return numberOfBorrowedbooks;
        
        }
        catch(Exception ex)
        {
          System.out.println(ex);
        }
           return 0;
    }
    
    //this function returns the items the user has borrowed
    public ResultSet searchBorrowedBooks(String query) {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        connect c = new connect();
        c.connection();
        try {
            return  c.st.executeQuery(query);
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        return null;
    }
    
    //function to fill the list by the data of loan table
    public List<Loan> getLoan()
    {
        List<Loan> loan=new ArrayList<Loan>();
        connect c = new connect();
        c.connection();
     
        String qry=" Select * from BoRROW where status = true";
        try
        {
            ResultSet rs=c.st.executeQuery(qry);
            while(rs.next())
            {
               Loan l=new Loan(rs.getInt(3),rs.getInt(2),rs.getString(4),rs.getString(5));
               loan.add(l);
            }
        
       }
        catch(Exception ex)
        {
            System.out.println(ex);
            ex.printStackTrace();
        
        }
        return loan;
    }
    
    //function to fill the list by the data of reserve table
    public List<reserve> getResevedBooks()
    {
        List<reserve> lreserve=new ArrayList<reserve>();
        connect c = new connect();
        c.connection();
     
        String qry=" Select * from Reserve where status = true";
        try
        {
            ResultSet rs=c.st.executeQuery(qry);
            while(rs.next())
            {
               reserve r=new reserve(rs.getInt(1),rs.getInt(2),rs.getInt(3));
               lreserve.add(r);
            }
        
       }
        catch(Exception ex)
        {
            System.out.println(ex);
            ex.printStackTrace();
        
        }
        return lreserve;
    }
   
    //function to fill the list by the data of the item table
    public List<item> getItem()
    {
        List<item> lsItem=new ArrayList<item>();
        connect c = new connect();
        c.connection();
     
        String qry=" Select * from Books";
        try{
        ResultSet rs=c.st.executeQuery(qry);
        while(rs.next())
        {
          
           String type= rs.getString("TYPE");
           if(type.equals("1"))
           {
               book b = new book("book",rs.getString("title"),rs.getString("author"),rs.getString("subject"),Integer.parseInt(rs.getString("isbn")));
               lsItem.add(b);
           }
           else
           {
               dvd d = new dvd("dvd",rs.getString("title"),rs.getString("author"),rs.getString("subject"),Integer.parseInt(rs.getString("isbn")));
               lsItem.add(d);  
           }
        }
        
        }
        catch(Exception ex)
        {
            System.out.println(ex);
            ex.printStackTrace();
        }
        return lsItem;
    }
    
    //function to fill the list by the data of the person table
    public List<person> getPerson()
    {
        List<person> lsPerson=new ArrayList<person>();
        connect c = new connect();
        c.connection();
     
        String qry=" Select * from users order by user_id asc";
        try{
        ResultSet rs=c.st.executeQuery(qry);
        while(rs.next())
        {
           String type= rs.getString("user_type");
           if(type.equals("0"))
           {
               borrower b = new borrower(Integer.parseInt(rs.getString("user_id")),rs.getString("name"),rs.getString("cnic"),rs.getString("address"),rs.getString("email"),rs.getString("phone"),"borrower");
               lsPerson.add(b);
           }
           else if (type.equals("1"))
           {
                clerk cl = new clerk(Integer.parseInt(rs.getString("user_id")),rs.getString("name"),rs.getString("cnic"),rs.getString("address"),rs.getString("email"),rs.getString("phone"),"clerk");               
                lsPerson.add(cl);  
           }
           else
           {
                librarian l = new librarian(Integer.parseInt(rs.getString("user_id")),rs.getString("name"),rs.getString("cnic"),rs.getString("address"),rs.getString("email"),rs.getString("phone"),"librarian");               
                lsPerson.add(l);  
           }
        }
        
        }
        catch(Exception ex)
        {
            System.out.println(ex);
            ex.printStackTrace();
        
        }
        return lsPerson;
    }
    
    //function to return history of user
    public ResultSet userHistory (int id)
    {
        connect c = new connect();
        c.connection();
        String qry="SELECT * from borrow where user_id = " + id ;
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            return rs;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return null;
    }
    
    //function to return history of item
    public ResultSet itemHistory (int id)
    {
        connect c = new connect();
        c.connection();
        String qry="SELECT * from borrow where book = " + id ;
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            return rs;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return null;
    }
}
