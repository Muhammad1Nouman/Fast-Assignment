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
public class book extends item {
  public String itemType;
  
    //default constructor
    book()
    {
        super();
        itemType="";
    }

    //function to store item_type
    public book(String itemType) {
        this.itemType = itemType;
    }

    // constructor
    public book(String itemType, String title, String Author, String subject, int ISBN) {
        super(title, Author, subject, ISBN);
        this.itemType = itemType;
    }
    
    //returns the item_type
    public String getItemType()
    {
        return itemType;
    }
    
    //returns 1(item_type)
    @Override
    public int item_type(){
        return 1;
    }
}
