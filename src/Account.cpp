#include <iostream>
#include <string>

using namespace std;

class Account
{
public:
    string accountHolderName;
    string accountNumber;
    double balance;

    // Constructor for initializing the account
    Account(string name, string accNum, double initialBalance)
        : accountHolderName(name), accountNumber(accNum), balance(initialBalance) {}

    // Display account details
    virtual void displayAccountDetails()
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    // Deposit amount to account
    virtual void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited: " << amount << endl;
    }

    // Withdraw amount from account
    virtual void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        }
        else
        {
            cout << "Insufficient balance!" << endl;
        }
    }

    // Virtual destructor to allow for proper cleanup of derived objects if needed
    virtual ~Account() {}
};
