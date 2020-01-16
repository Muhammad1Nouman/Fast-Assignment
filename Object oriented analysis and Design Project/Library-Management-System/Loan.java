/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classes;

import java.time.LocalDateTime;
import java.time.Period;
import java.time.format.DateTimeFormatter;

/**
 *
 * @author PC
 */
public class Loan {
    
    public int PersonId;
    public int ItemIsbn;
    public LocalDateTime returnDate;
    public LocalDateTime issueDate;
    
    //constructor
    public Loan(int Person,int Item)
    {
        this.PersonId=Person;
        this.ItemIsbn=Item;
        issueDate=LocalDateTime.now();
        returnDate=LocalDateTime.now().plusDays(12);    
    }
    
    //constructor
    public Loan(int Person,int Item,String issueDate,String returnDate)
    {
        this.PersonId=Person;
        this.ItemIsbn=Item;
        issueDate=issueDate+ " 00:00:00";
        returnDate=returnDate+" 00:00:00";
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        this.issueDate = LocalDateTime.parse(issueDate, formatter);
        this.returnDate= LocalDateTime.parse(returnDate, formatter);
       
    }
    
    //default constructor
    public Loan()
    {
    }
}