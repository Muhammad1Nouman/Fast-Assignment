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
public class reserve {
    public int id;
    public int userid;
    public int itemid;
    
    //constructor
    public reserve(int id,int itemid,int userid)
    {
       this.id=id;
       this.userid=userid;
       this.itemid=itemid;
    }
}
