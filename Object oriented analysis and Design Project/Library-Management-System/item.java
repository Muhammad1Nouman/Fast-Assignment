/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classes;
import java.util.*;
/**
 *
 * @author PC
 */
public abstract class item {
    public String Author;
    public String title;
    public String Subject;
    public int ISBN;
    
    //default constructor
    item()
    {
        Author="";
        title="";
        Subject="";
        ISBN=0;
    }
    
    //constructor
    public item(String title,String Author,String subject,int ISBN)
    {
        this.Author=Author;
        this.title=title;
        this.Subject=subject;
        this.ISBN=ISBN;
       
    }
    
    //return author
    public String getAuthor()
    {
        return this.Author;
    }
    
    //returns title
    public String gettitle()
    {
        return this.title;
    }
    
    //returns subject
    public String getSubject()
    {
        return this.Subject;
    }
    
    //returns ISBN
    public int getISBN()
    {
        return this.ISBN;
    }
    
    //returns item_type
    public abstract int item_type();
  }
