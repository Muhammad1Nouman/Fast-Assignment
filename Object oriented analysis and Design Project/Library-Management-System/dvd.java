/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classes;

/**
 *
 * @author PC
 */
public class dvd extends item{
    public String itemType;
    
    //default constructor
    dvd()
    {
        super();
        itemType="";
    }

    //function to store item_type
    public dvd(String itemType) {
        this.itemType = itemType;
    }

    //constructor
    public dvd(String itemType, String title, String Author, String subject, int ISBN) {
        super(title, Author, subject, ISBN);
        this.itemType = itemType;
    }
    
    //function to get item_type
    public String getItemType()
    {
        return itemType;
    }
    
    //returns 0(item_type)
    @Override
    public int item_type(){
        return 0;
    }
}
