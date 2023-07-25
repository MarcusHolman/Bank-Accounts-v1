// Creator Name: Marcus Holman
// Date: 10/30/22
// Purpose: Add a partial search option (by Id, first and last names).
//          a sort menu option with a submenu to sort by any field (first and last names, 
//          account Id, and balance) using array of pointers.
//          sort options with submenu to sort by any field (last name, first name, account 
//          id, and balance) in ascending order
//          search option to search by  partial account ID, first, or last names(no submenu)
//////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "bankAccounts.h"
#include <iomanip>
#include <algorithm>

using namespace std;

// -- PROTOTYPES --
void menu(bankAccount xArray[], bankAccount* pArray[], const size_t size); //prints menu and allows user to make a selection
void exit(); // may not need
void readFile(bankAccount accts[], bankAccount* ptr[]); //reads accoount data from file
void printAccts(bankAccount* pArray[], const size_t size); //prints list of current accounts with valid  account data
void deposit(bankAccount xArray[], const size_t size); //deposits money into a selected account
void withdraw(bankAccount xArray[], const size_t size); //withdraw money from a selected account
void bubbleSort(bankAccount* pArray[], const size_t size, int sort); // sort the list by chosen field 
void sortAccountsMenu(bankAccount* pArray[], const size_t size); //sort accounts the order you choose
void findRecords(bankAccount* pArray[], const size_t size); //search the records by name or account #
bool searchAccts(const bankAccount xArray[], const int acctNum, const size_t size, int& it); // used in deposit/withdraw
int seqSearch(bankAccount* pArray[], size_t size, const string& item);
void returnToMain();
void invalidTryAgain();

// -- VARIABLES --
const int MAX_SIZE = 10;

// -- MAIN -- 
int main()
{
    // -- DECLARE VARIBLES -- //
    bankAccount accounts[MAX_SIZE];
    bankAccount* pBankAccts[MAX_SIZE] = { nullptr };

    cout << "This program handles bank accounts.\n";
    readFile(accounts, pBankAccts); // load file
    size_t lenAccounts = sizeof(accounts) / sizeof(accounts[0]); // length of accounts array. used in multiple functions
    cout << "File loaded successfully.\n"; //prints if readfile is succeful

    menu(accounts, pBankAccts, lenAccounts);
    exit();
    return 0;
}

// -- FUNCTION DEFINITIONS -- //
// read file function
void readFile(bankAccount accts[], bankAccount* ptr[])
{
    // -- DECLARE VARIBLES -- //
    ifstream inputFile;
    string tempFName = "";
    string tempLName = "";
    int tempAcct = 0;
    double tempBal = 0.0;
    int count = 0;


    inputFile.open("accounts1.txt");
    if (!inputFile)
    {
        cout << "\n**Error** - Input file not found! Quitting the program." << endl;
        system("pause");
        exit();
    }

    while (!inputFile.eof() && inputFile)
    {
        for (count; count < MAX_SIZE; count++)
        {
            inputFile >> tempFName >> tempLName >> tempAcct >> tempBal; //read into temp variables
            transform(tempFName.begin(), tempFName.end(), tempFName.begin(), ::tolower);
            transform(tempLName.begin(), tempLName.end(), tempLName.begin(), ::tolower);

            if (tempFName == "")
            {
                cout << "\n**Error** - The input file is empty. Quitting the program." << endl;
                system("pause");
                exit(EXIT_FAILURE);
            }

            accts[count].setAccount(tempFName, tempLName, tempAcct, tempBal);
            ptr[count] = &accts[count];
            tempFName = "N/A";
            tempLName = "N/A";
            tempAcct = 0000000000;
            tempBal = 0;
        }
    }

    if (count == MAX_SIZE && !inputFile.eof())
    {
        cout << "**WARNING!**\nNot all accounts have been stored; only first "
            << MAX_SIZE << " will be processed." << endl;
    }
    inputFile.close();
}

// Menu function
void menu(bankAccount xArray[], bankAccount* pArray[], const size_t size)
{
    // -- DECLARE VARIBLES -- //
    int selection = 0;

    // -- MAIN MENU LOOP --
    while (selection != 6)
    {
        cout << "\nMain Menu: \n"
            "(1) View the list of the bank accounts.\n"
            "(2) Deposit into an account.\n"
            "(3) Withdraw from an account.\n"
            "(4) Sort the list of bank accounts\n"
            "(5) Search the list of bank accounts\n"
            "(6) Quit.\n"
            "\nEnter the number for the option you wish to select: ";
        cin >> selection; // read user input

        // process menu selection using switch
        switch (selection)
        {
        case 1://printAccts()
            printAccts(pArray, size);
            returnToMain();
            break;
        case 2://deposit()
            deposit(xArray, size);
            returnToMain();
            break;
        case 3://withdraw()
            withdraw(xArray, size);
            returnToMain();
            break;
        case 4: //quit program
            sortAccountsMenu(pArray, size);
            returnToMain();
            break;
        case 5:
            findRecords(pArray, size);
            break;
        case 6:
            break;
        default:
            invalidTryAgain();
            returnToMain();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

void printAccts(bankAccount* pArray[], const size_t size)
{
    //print a formated/labeled list of accounts
    cout << "\nBank Account Records: \n"
        "=====================================================\n"
        << setw(12) << left << "First Name"
        << setw(12) << left << "| " "Last Name"
        << setw(12) << left << "| " "Account Number"
        << setw(12) << left << " | " "Balance\n"
        "=====================================================\n";

    for (int i = 0; i < size; i++)
    {
        if (pArray[i]->getAcctNum() == 0000000000)
        {
        }
        else
            pArray[i]->printAcct();
    }
}

void deposit(bankAccount xArray[], const size_t size)
{
    // -- DECLARE VARIBLES -- //
    int acctNum = 0000000000;
    bool dpComplete = 0;

    cout << "\nYou have chosen to deposit money.";

    while (dpComplete == 0)
    {
        // -- DECLARE VARIBLES -- //
        int userInput = 0;
        int it = 0; // iterator for search function

        cout << "\nEnter the 10 digit account number (enter '0' to return to Menu): ";
        cin >> acctNum;

        if (!cin)
        {
            cout << "\n**Error** - Please enter a 10 digit account number.\n";
            cin.clear(); //clear input errors
            cin.seekg(0);
        }
        else if (acctNum == 0)
        {
            dpComplete = 1;
        }
        else
        {
            if (searchAccts(xArray, acctNum, size, it))
            {
                cout << "\nThe current account balance for " << xArray[it].getFName() << " "
                    << xArray[it].getLName() << " is: " << xArray[it].getBalance();
                xArray[it].depositFunds();
                cout << "\nYour new balance is " << xArray[it].getBalance() << ".\n";

                while (userInput != 2 && userInput != 1)
                {
                    cout << "\nWould you like to make another deposit? \n"
                        "(1)Yes \n"
                        "(2) No. Retrun to Main Menu\n"
                        "\nEnter the number for the option you wish to select: ";
                    cin >> userInput;
                    switch (userInput)
                    {
                    case 1:
                        break;
                    case 2:
                        dpComplete = 1;
                        break;
                    default:
                        invalidTryAgain();
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                }
            }
            else // invalid entry action
                cout << "\n**Error** - Account number is invalid. Please try again.\n";
        }
    }
}

void withdraw(bankAccount xArray[], size_t size)
{
    // -- DECLARE VARIBLES -- //
    int acctNum = 0000000000;
    bool wdComplete = 0;

    cout << "\nYou have chosen to withdraw money.";

    while (wdComplete == 0)
    {
        int userInput = 0;
        int it = 0; // iterator for search function

        cout << "\nEnter the 10 digit account number (enter '0' to return to Main Menu): ";
        cin >> acctNum;

        if (!cin)
        {
            cout << "\n**Error** - Please enter a 10 digit account number.\n";
            cin.clear();
            cin.seekg(0);
        }
        else if (acctNum == 0)
        {
            wdComplete = 1;
        }
        else
        {
            if (searchAccts(xArray, acctNum, size, it))
            {
                cout << "\nThe current account balance for " << xArray[it].getFName() << " "
                    << xArray[it].getLName() << " is: " << xArray[it].getBalance();
                xArray[it].withdrawFunds();
                cout << "\nYour new balance is " << xArray[it].getBalance() << ".\n";

                while (userInput != 2 && userInput != 1)
                {
                    cout << "\nWould you like to make another withdrawal? \n" // Prompt for another withdraw
                        "(1)Yes \n"
                        "(2) No. Retrun to Main Menu\n"
                        "\nEnter the number for the option you wish to select: ";
                    cin >> userInput;
                    switch (userInput)
                    {
                    case 1:
                        break;
                    case 2:
                        wdComplete = 1;
                        break;
                    default:
                        invalidTryAgain();
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                }
            }
            else
                cout << "\n**Error** - Account number is invalid. Please try again.\n";
        }
    }
}

bool searchAccts(const bankAccount xArray[], const int acctNum, const size_t size, int& it)
{
    // Search bankAccount array for given account number. Return true if located.
    for (it; it < size; it++)
    {
        if (xArray[it].getAcctNum() == acctNum)
        {
            return true;
        }
    }
    return false;
}

void findRecords(bankAccount* pArray[], const size_t size)
{
    // -- DECLARE VARIBLES -- //
    string searchKey = "";
    bool searchMenu = true;
    int searchResult = 0;


    while (searchMenu == true)
    {
        cout << "\nSearch Menu: \n"
            "Enter the first name, last name, or accout ID: "; // ---- or partial name
        cin >> searchKey;
        transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

        cout << "\nReturning search results for '" << searchKey << "'...\n";
        searchResult = seqSearch(pArray, size, searchKey);
        if (searchResult == -1)
            cout << "\nNo accounts found.\n";

        returnToMain();
        searchMenu = false;
    }
}
// linear search function
int seqSearch(bankAccount* pArray[], size_t size, const string& item)
{
    // -- DECLARE VARIBLES -- //
    int loc;
    bool found = false;
    loc = 0;

    cout << "\nBank Account Records: \n"
        "=====================================================\n"
        << setw(12) << left << "First Name"
        << setw(12) << left << "| " "Last Name"
        << setw(12) << left << "| " "Account Number"
        << setw(12) << left << " | " "Balance\n"
        "=====================================================\n";
    while (loc < size)
    {
        // create filters using find()
        size_t search1 = pArray[loc]->getFName().find(item);
        size_t search2 = pArray[loc]->getLName().find(item);
        size_t search3 = to_string(pArray[loc]->getAcctNum()).find(item);

        if (pArray[loc]->getAcctNum() == 0) // filter empty records from array output
        {
        }
        else
        {
            if (search1 != string::npos || search2 != string::npos || search3 != string::npos)
            {
                pArray[loc]->printAcct(); // print selected record
                found = true;
            }
        }
        loc++;
    }
    if (found)
        return loc;
    else
        return -1;
}
// sort menu
void sortAccountsMenu(bankAccount* pArray[], const size_t size)
{
    // -- DECLARE VARIBLES -- //
    int sortOption = 0;
    bool sortMenu = true;

    // -- MENU LOOP -- //
    while (sortOption != 5)
    {
        cout << "\nSorting Menu: \n" // print sort menu
            "(1) Account Number\n"
            "(2) First Name\n"
            "(3) Last Name\n"
            "(4) Balance\n"
            "(5) Return to Main Menu\n"
            "\nEnter the number for the field you wish to sort by: ";
        cin >> sortOption;

        switch (sortOption) // switch for option selection
        {
        case 1:
        case 2:
        case 3:
        case 4:
            bubbleSort(pArray, size, sortOption);
            printAccts(pArray, size);
            cout << "\nReturning to Sorting Menu.\n";
            break;
        case 5:
            break;
        default:
            invalidTryAgain();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}
// bubble sort function
void bubbleSort(bankAccount* pArray[], const size_t size, int sortOption)
{
    for (int it = 1; it < size; it++) //iterator loop
    {
        for (int i = 0; i < size - it; i++) // index loop
        {
            switch (sortOption)
            {
            case 1: // Account Number
                if (pArray[i]->getAcctNum() > pArray[i + 1]->getAcctNum())
                {
                    bankAccount temp = *pArray[i];
                    *pArray[i] = *pArray[i + 1];
                    *pArray[i + 1] = temp;
                }
                break;
            case 2: // First Name
                if (pArray[i]->getFName() > pArray[i + 1]->getFName())
                {
                    bankAccount temp = *pArray[i];
                    *pArray[i] = *pArray[i + 1];
                    *pArray[i + 1] = temp;
                }
                break;
            case 3: // Last Name
                if (pArray[i]->getLName() > pArray[i + 1]->getLName())
                {
                    bankAccount temp = *pArray[i];
                    *pArray[i] = *pArray[i + 1];
                    *pArray[i + 1] = temp;
                }
                break;
            case 4: // Balance
                if (pArray[i]->getBalance() > pArray[i + 1]->getBalance())
                {
                    bankAccount temp = *pArray[i];
                    *pArray[i] = *pArray[i + 1];
                    *pArray[i + 1] = temp;
                }
                break;
            default:
                break;
            }
        }
    }
}
// print return to main message
void returnToMain()
{
    cout << "\nReturning to Main Menu.\n";
}
// print invalid entry message
void invalidTryAgain()
{
    cout << "\n**Error** - Invalid entry! Please try again.\n";
}
// Print Exit message
void exit()
{
    cout << "Exiting program.\n";
}
