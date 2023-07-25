#include "bankAccounts.h"

// -- ACCESSOR FUNCTIONS -- //
void bankAccount::printAcct() const
{
    cout << setprecision(2) << fixed << setw(12) << left << firstName << " "
        << setw(12) << left << lastName << "  " << right << setw(11) << numAccount
        << "  " << right << setw(12) << balance << endl;
}

string bankAccount::getFName() const
{
    return firstName;
}

string bankAccount::getLName() const
{
    return lastName;
}

int bankAccount::getAcctNum() const
{
    return numAccount;
}

double bankAccount::getBalance() const
{
    return balance;
}

// -- MUTATOR FUNTIONS -- //
void bankAccount::setAccount(string& fName, string& lName, int& numAcct, double& bal)
{
    firstName = fName;
    lastName = lName;
    numAccount = numAcct;
    balance = bal;
}

double bankAccount::withdrawFunds()
{
    // -- DECLARE VARIBLES -- //
    double min = 0.01;
    double wdValue = 0.0;

    if (balance < min)
    {
        cout << "\n**Error** There are no funds available to withdraw.\n";
    }
    else
    {
        while (balance >= min)
        {
            bool quit = 0;
            cout << "\nEnter the amount you would like to withdraw: ";
            cin >> wdValue;

            if (!cin)
            {
                cout << "\n**Error** - Please enter a valid amount to withdraw (numbers only).\n";
                cin.clear();
                cin.seekg(0);
            }
            else
            {
                while (wdValue > min && quit != 1)
                {
                    if (wdValue > balance && wdValue > 0.0)
                    {
                        cout << "\n**WITHDRAW REQUEST DENIED!** "
                            "\nThe withdraw amount requested excedes the account balance of $" << balance << "."
                            "\nEnter a value below $" << balance << ".\n";
                        cin.clear();
                        cin.seekg(0);
                        quit = 1;
                    }
                    else if (wdValue > 0.0)
                    {
                        balance = balance - wdValue;
                        cout << "\nWithdraw request approved."
                            "\n$" << wdValue << " was withdrawn from account " << numAccount << ".";
                        quit = 1;
                        wdValue = 0;
                        return balance;
                    }
                }
                if (wdValue < min)
                    cout << "\nPlease enter a value greater than $0.0.";
            }
        }
    }
    return balance;
}

double bankAccount::depositFunds()
{
    // -- DECLARE VARIBLES -- //
    double min = 0.01;
    bool quit = 0;
    double dpValue = 0.0;
    string userInput = "";

    while (quit != 1)
    {
        cout << "\nEnter the amount you would like to deposit: ";
        cin >> dpValue; // user input

        if (!cin)
        {
            cout << "\n**Error** - Please enter a valid amount to deposit (numbers only).\n";
            cin.clear(); // clear invalid enrty
            cin.seekg(0);
        }
        else
        {
            while (dpValue > min)
            {
                if (dpValue < min)
                {
                    cout << "\n**DEPOSIT REQUEST DENIED!** "
                        "\nThe deposit amount must be more than $0.00.";
                }
                else if (dpValue >= min)
                {
                    balance = balance + dpValue;
                    cout << "\nDeposit approved."
                        "\n$" << dpValue << " was deposited to the account " << numAccount << ".";

                    quit = 1;
                    dpValue = 0;
                    return balance;
                }
            }
            if (dpValue < min)
                cout << "\nPlease enter a value greater than $0.0.";
        }
    }
    return balance;
}

// -- CONSTRUCTORS/DESTRUCTORS -- //
bankAccount::bankAccount(string fName, string lName, int numAcct, double bal)
{
    firstName = fName;
    lastName = lName;
    numAccount = numAcct;
    balance = bal;
}

bankAccount::bankAccount()
{
    firstName = "N/A";
    lastName = "N/A";
    numAccount = 0000000000;
    balance = 0;
}
bankAccount::~bankAccount()
{
    firstName = "N/A";
    lastName = "N/A";
    numAccount = 0000000000;
    balance = 0;
}