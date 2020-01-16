/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classes;

import java.sql.ResultSet;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import javax.swing.JOptionPane;
import java.time.LocalDateTime;
import java.time.Period;

/**
 *
 * @author PC
 */
public abstract class person {
    public int id;
    public String name;
    public String cnic;
    public String address;
    public String email;
    public String phone;
    
    //object of connect class
    connect c=new connect();

    //constructor
    public person(int id, String name, String cnic, String address, String email, String phone) {
        this.id = id;
        this.name = name;
        this.cnic = cnic;
        this.address = address;
        this.email = email;
        this.phone = phone;
    }
    
    //default constructor
    person ()
    {
    }
    
    //returns the max ISBN plus 1
    public int maxISBN (){
        c.connection();
        String qry="SELECT MAX(id) from borrow";
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            rs.next();
            int Id= rs.getInt(1)+1;
            return Id;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return 0;
    }
    
    //returns the type of the user
    public abstract int userType ();

    //function to return max id of a user
    public int maxId ()
    {
        c.connection();
        String qry="SELECT MAX(user_id) from users";
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            rs.next();
            int Id= rs.getInt(1)+1;
            return Id;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return 0;
    }
    
    //function to return the max id from reserve table
    public int maxReserveID ()
    {
        c.connection();
        String qry="SELECT MAX(id) from reserve";
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            rs.next();
            int Id= rs.getInt(1)+1;
            return Id;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return 0;
    }

    //function to add item
    public boolean addItem(String isbn, String title, String author, String subject, int type)
    {
        return false;
    }

    //function to delete an item
    public void deleteItem(int ISBN)
    {
    }

    //function to update an item
    public void updateItem(String isbn, String title, String author, String subject)
    {
    }

    //function to check if the currently being added borrower's credentials are fine
    public boolean checkBorrower (String username,String cnic,String email)
    {
        c.connection();
        String qry="SELECT * from users where cnic ='" +cnic+ "'" ;
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            rs.next();
            if (rs.getRow()!=0)
                return true;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        qry="SELECT * from users where email ='" +email+ "'" ;
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            rs.next();
            if (rs.getRow()!=0)
                return true;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        qry="SELECT * from login where username ='" +username+ "'" ;
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            rs.next();
            if (rs.getRow()!=0)
                return true;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return false;
    }

    //function to check if the currently being added borrower's credentials are fine
    public boolean checkBorrower (String email , String CNIC)
    {
        c.connection();
        String qry="SELECT * from users where email ='" +email+ "'" ;
        String qry2="SELECT * from users where email ='" +email+ "' and cnic = '" +CNIC+ "'";
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            rs.next();
            if (rs.getRow()!=0)
            {
                ResultSet rs2 = c.st.executeQuery(qry2);
                rs2.next();
                if(rs2.getRow()==0)
                    return true;
            }
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return false;
    }

    //function to add borrower
    public void addBorrower (int id , String name , String cnic ,String address , String email , String phone , String username , String password, int type)
    {
        String qry = "insert into users values (" +id+ ",'" +name+ "','" +cnic+ "','" +address+ "'," +type+ ",'" +email+ "'," +Long.parseLong(phone)+ ")";
        String querry = "insert into login values (" +id+ ",'" +username+ "','" +password+ "')"; 
        c.connection();
        try
        {
            c.st.execute(qry);
            c.st.execute(querry);
            JOptionPane.showMessageDialog(null, "The person has been added");
        }
        catch(Exception ex)
        {
             System.out.println(ex);
        }
        c.close();
    }

    //function to update borrower
    public void updateBorrower (String name,String CNIC,String address,String email,String phone)
    {
        String qry = "update users set name='" +name+ "', email='" +email+ "', phone=" +phone+ ", address='" +address+ "' where cnic='" + CNIC+ "'";
        c.connection();
        try
        {
            c.st.execute(qry);
            JOptionPane.showMessageDialog(null, "The person has been updated");
        }
        catch(Exception ex)
        {
             System.out.println(ex);
        }
        c.close();
    }

    //function to check if a book is currently borrowed
    public boolean checkForBorrow (String ISBN)
    {
        c.connection();
        String qry="SELECT * from borrow where book =" +Integer.parseInt(ISBN) ;
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            rs.next();
            if (rs.getRow()==0)
                return true;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return false;
    }

    //this function returns the user_id against the username
    public int getId (String username)
    {
        c.connection();
        String qry="SELECT * from login where username ='" +username+ "'" ;
        try
        {
            ResultSet rs = c.st.executeQuery(qry);
            rs.next();
            return Integer.parseInt(rs.getString("user_id"));
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return -1;
    }
    
    //function to check if the current user has already made reservation on the current book
    public boolean checkReservation(int ISBN,int user_ID)
    {
        String querry = "select * from reserve where book=" +ISBN+ "and user_id= "+user_ID;
        c.connection();
        try
        {
            ResultSet rs = c.st.executeQuery(querry);
            rs.next();
            if (rs.getRow()==0)
                return true;
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        c.close();
        return false;
    }
    
    //function to reserve an item
    public void addReservation (int ReserveID, int ISBN, int user_ID)
    {
        String qry = "insert into reserve values (" +ReserveID+ "," +ISBN+ "," +user_ID+ ", true)";
        c.connection();
        try
        {
            c.st.execute(qry);
            JOptionPane.showMessageDialog(null, "The reservation has been made");
        }
        catch(Exception ex)
        {
             System.out.println(ex);
        }
        c.close();
    }
    
    //function to checkout an item
    public  void addCheckoutItem(int item, int user, LocalDateTime issueDate , LocalDateTime returnDate)
    {
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        String querry="INSERT INTO BORROW VALUES(" +maxISBN()+ "," +item+","+user+",'"+dtf.format(issueDate)+"','"+dtf.format(returnDate)+"', true)";
        c.connection();
        try
        {
            c.st.execute(querry);
            JOptionPane.showMessageDialog(null, "The item is successfuly checked-out");
        }
        catch(Exception ex)
        {
             System.out.println(ex);
        }
        c.close();
    }
    
    //function to checkin an item
    public  void addCheckIn(int item , int user)
    {
        String qr="update BORROW set status = false WHERE USER_ID="+user+" AND Book="+item;
        c.connection();
        try
        {
            c.st.execute(qr);
        }
        catch(Exception ex)
        {
             System.out.println(ex);
        }
        c.close(); 
    }
    
    //function to delete reservation
    public void deleteReservation (int item , int user)
    {
        String qry = "update reserve set status = false where book=" +item+ " and user_id=" +user;
        c.connection();
        try
        {
            c.st.execute(qry);
        }
        catch(Exception ex)
        {
             System.out.println(ex);
        }
        c.close();
    }
    
    //to calculate the fine
    public int fineCalculator(LocalDateTime loc)
    {
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        LocalDateTime currDate=LocalDateTime.now();
        Period p = Period.between(loc.toLocalDate(),currDate.toLocalDate());
        int days=p.getDays();
        if (days>0)
            return days*20;
        return 0;
    }
    
}
