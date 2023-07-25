#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class bankAccount
{
private:
    // -- DECLARE VARIBLES -- //
    string firstName;
    string lastName;
    int numAccount;
    double balance;

public:
    // -- FUNCTION PROTOTYPES -- //
    void setAccount(string& fName, string& lName, int& numAcct, double& bal);
    //Function to set the bank account data
    //Account is set according to parameters
    void printAcct() const;
    //Function to print the member data as a string
    //The format is firstName lastName accountNumber balance
    int getAcctNum() const;
    //Function to return numAccount data
    double getBalance() const;
    //Function to return balance data
    string getFName() const;
    //Function to return fist name data
    string getLName() const;
    //Function to return last name data
    double withdrawFunds();
    //Function to withdraw money from account
    double depositFunds();
    //Function to deposit money to account

    // -- CONSTRUCTORS/DESTRUCTORS -- //
    bankAccount(string, string, int, double); // constructor with parameters
    bankAccount(); // default constructor
    ~bankAccount();// destructor
};
