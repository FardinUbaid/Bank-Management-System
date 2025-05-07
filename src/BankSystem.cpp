#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "User.cpp"
#include "Account.cpp"
#include "SavingsAccount.cpp"
#include "CurrentAccount.cpp"

using namespace std;

class BankSystem
{
private:
    User currentUser;

public:
    BankSystem() {}

    // Prompt user to log in
    bool loginPrompt()
    {
        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (currentUser.login(username, password))
        {
            currentUser.displayRole();
            return true;
        }
        else
        {
            cout << "Invalid login credentials." << endl;
            return false;
        }
    }

    // Create a new account
    void createAccount()
    {
        string name, accNum, type;
        double initialBalance;

        cout << "Enter account holder name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter account number: ";
        cin >> accNum;

        cout << "Enter initial balance: ";
        cin >> initialBalance;

        cout << "Select account type (savings/current): ";
        cin >> type;

        Account *acc = nullptr;
        if (type == "savings")
        {
            acc = new SavingsAccount(name, accNum, initialBalance);
        }
        else if (type == "current")
        {
            acc = new CurrentAccount(name, accNum, initialBalance);
        }
        else
        {
            cout << "Invalid account type!" << endl;
            return;
        }

        // Save account to file
        ofstream outfile("accounts.txt", ios::app);
        outfile << name << "," << accNum << "," << initialBalance << "," << type << endl;
        outfile.close();

        cout << "Account created successfully.\n";
        delete acc;
    }

    // View all accounts (admin only)
    void viewAllAccounts()
    {
        if (!currentUser.isAdmin)
        {
            cout << "Access denied. Admin only.\n";
            return;
        }

        ifstream infile("accounts.txt");
        string line;

        while (getline(infile, line))
        {
            stringstream ss(line);
            string name, accNum, balance, type;

            getline(ss, name, ',');
            getline(ss, accNum, ',');
            getline(ss, balance, ',');
            getline(ss, type);

            cout << "\nName: " << name
                 << "\nAccount Number: " << accNum
                 << "\nBalance: " << balance
                 << "\nType: " << type << "\n";
        }

        infile.close();
    }

    // Entry menu
    void run()
    {
        if (!loginPrompt())
            return;

        int choice;
        do
        {
            cout << "\n--- Menu ---\n";
            cout << "1. Create Account\n";
            if (currentUser.isAdmin)
            {
                cout << "2. View All Accounts\n";
            }
            cout << "0. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                createAccount();
                break;
            case 2:
                if (currentUser.isAdmin)
                    viewAllAccounts();
                else
                    cout << "Invalid option.\n";
                break;
            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
            }

        } while (choice != 0);
    }
};
