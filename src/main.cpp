#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Account base class
class Account
{
public:
    string accountHolderName;
    string accountNumber;
    double balance;

    Account(string name, string accNum, double initialBalance)
        : accountHolderName(name), accountNumber(accNum), balance(initialBalance) {}

    virtual void displayAccountDetails()
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    virtual void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited: " << amount << endl;
    }

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
};

// SavingsAccount class (derived from Account)
class SavingsAccount : public Account
{
public:
    SavingsAccount(string name, string accNum, double initialBalance)
        : Account(name, accNum, initialBalance) {}

    void displayAccountDetails() override
    {
        Account::displayAccountDetails();
        cout << "Account Type: Savings" << endl;
    }
};

// CurrentAccount class (derived from Account)
class CurrentAccount : public Account
{
public:
    CurrentAccount(string name, string accNum, double initialBalance)
        : Account(name, accNum, initialBalance) {}

    void displayAccountDetails() override
    {
        Account::displayAccountDetails();
        cout << "Account Type: Current" << endl;
    }
};

// User class for login
class User
{
public:
    string username;
    string password;
    bool isAdmin;

    User(string user, string pass, bool admin = false)
        : username(user), password(pass), isAdmin(admin) {}

    bool login(string enteredUsername, string enteredPassword)
    {
        return enteredUsername == username && enteredPassword == password;
    }
};

// Transaction class for handling deposits and withdrawals
class Transaction
{
public:
    void createTransaction(Account &account, double amount, string type)
    {
        if (type == "deposit")
        {
            account.deposit(amount);
        }
        else if (type == "withdraw")
        {
            account.withdraw(amount);
        }
    }
};

int main()
{
    // Create users
    User admin("admin", "adminpass", true);
    User user("user1", "userpass");

    // Bank accounts
    vector<Account *> accounts;

    int choice;
    string username, password;
    bool loggedIn = false;
    bool isAdmin = false;

    // Login process
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (admin.login(username, password))
    {
        loggedIn = true;
        isAdmin = true;
        cout << "Admin logged in successfully!" << endl;
    }
    else if (user.login(username, password))
    {
        loggedIn = true;
        cout << "User logged in successfully!" << endl;
    }
    else
    {
        cout << "Invalid login credentials!" << endl;
    }

    // Main loop
    while (loggedIn)
    {
        cout << "\n1. Create Account\n2. View Account\n3. Deposit\n4. Withdraw\n5. Logout\n";
        if (isAdmin)
        {
            cout << "6. Admin Options\n";
        }
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name, accNum;
            double balance;
            cout << "Enter account holder's name: ";
            cin >> name;
            cout << "Enter account number: ";
            cin >> accNum;
            cout << "Enter initial balance: ";
            cin >> balance;

            int accType;
            cout << "Select account type:\n1. Savings\n2. Current\n";
            cin >> accType;

            if (accType == 1)
            {
                accounts.push_back(new SavingsAccount(name, accNum, balance));
                cout << "Savings Account created!" << endl;
            }
            else
            {
                accounts.push_back(new CurrentAccount(name, accNum, balance));
                cout << "Current Account created!" << endl;
            }
        }
        else if (choice == 2)
        {
            string accNum;
            cout << "Enter account number: ";
            cin >> accNum;

            bool found = false;
            for (auto &acc : accounts)
            {
                if (acc->accountNumber == accNum)
                {
                    acc->displayAccountDetails();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Account not found!" << endl;
            }
        }
        else if (choice == 3)
        {
            string accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;
            cout << "Enter deposit amount: ";
            cin >> amount;

            bool found = false;
            for (auto &acc : accounts)
            {
                if (acc->accountNumber == accNum)
                {
                    Transaction transaction;
                    transaction.createTransaction(*acc, amount, "deposit");
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Account not found!" << endl;
            }
        }
        else if (choice == 4)
        {
            string accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;
            cout << "Enter withdrawal amount: ";
            cin >> amount;

            bool found = false;
            for (auto &acc : accounts)
            {
                if (acc->accountNumber == accNum)
                {
                    Transaction transaction;
                    transaction.createTransaction(*acc, amount, "withdraw");
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Account not found!" << endl;
            }
        }
        else if (choice == 5)
        {
            cout << "Logging out..." << endl;
            loggedIn = false;
        }
        else if (choice == 6 && isAdmin)
        {
            // Admin specific options
            cout << "Admin options (not implemented in this version)." << endl;
        }
    }

    return 0;
}
