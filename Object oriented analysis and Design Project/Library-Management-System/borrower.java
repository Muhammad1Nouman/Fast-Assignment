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
public class borrower extends person {

    public String user_type;
    
    // constructor
    public borrower(int id, String name, String cnic, String address, String email, String phone, String t) {
        super(id, name, cnic, address, email, phone);
        user_type=t;
    }

    //default constructor
    public borrower()
    { 
        super();
    }
    
    //return 0(user_type)
    @Override
    public int userType ()
    {
        return 0;
    }
}
