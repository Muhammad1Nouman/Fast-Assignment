/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classes;

import javax.swing.JOptionPane;

/**
 *
 * @author PC
 */
public class clerk extends person{

    public String user_type;
    
    //default constructor
    public clerk(int id, String name, String cnic, String address, String email, String phone, String t) {
        super(id, name, cnic, address, email, phone);
        user_type=t;
    }
     
    //default constructor
    public clerk()
    {
        super();
    }
    
    @Override
    public int userType ()
    {
        return 1;
    }
}
