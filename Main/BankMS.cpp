#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

// Print Functions
void showInfo(int id, std::string name, double accBalance, std::string type, std::string usertype, std::string status);
void showInfo(int id, std::string name, double accBalance, std::string type, std::string pass, std::string usertype, std::string status);

// CRUD Operations
void CreateAccount(std::string name, double accBalance, std::string pass, std::string type, std::string usertype);
void SearchAccountAdmin(const std::string &storedName);
void SearchAccount(const std::string &storedName);
void UpdateUserDetails(int id, const std::string &storedName);
// Admin Features
// void UpdateAccountStatus();
void UpdateAccountStatus(const std::string &storedName);
void DeleteAccount(const std::string &storedName);
// Login Feature
bool SearchByNameAndPassword(const std::string &name, const std::string &password, int &id, std::string &storedName, double &balance, std::string &type, std::string &usertype, std::string &status);
// Core Features
void Deposit(const std::string &input);
void Withdraw(const std::string &input);
// Activity Log Functions
void LogDeposit(int id, const std::string &name, double depositAmount, double newBalance);
void LogWithdraw(int id, const std::string &name, double withdrawAmount, double newBalance);

// Class for creating accounts
class Account
{
private:
    std::string name;
    std::string password;
    std::string type;
    std::string usertype;
    double balance;

public:
    Account() : balance(500.00) {}
    void Usertype()
    {
        std::cout << "______________________[User Type]____________________\n";
        std::cout << "Select User Type:\n";
        std::cout << "      1. Admin\n";
        std::cout << "      2. Regular\n\n";
        std::cout << "_____________________________________________________\n";
        std::cout << "Enter your choice: ";
    }
    void AccountType()
    {
        std::cout << "____________________[Account Type]___________________\n";
        std::cout << "Select Account Type:\n";
        std::cout << "      1. Savings\n";
        std::cout << "      2. Current\n\n";
        std::cout << "_____________________________________________________\n";
        std::cout << "Enter your choice: ";
    }
    void createAccount()
    {
        Usertype();
        int userTypeChoice;
        std::cin >> userTypeChoice;
        std::cin.ignore();

        if (userTypeChoice == 1)
        {
            usertype = "Admin";
        }
        else if (userTypeChoice == 2)
        {
            usertype = "Regular";
        }
        else
        {
            std::cout << "Invalid choice. Defaulting to Regular user.\n";
            usertype = "Regular";
            std::cout << "__________________________________________________________\n";
        }

        AccountType();
        int accountTypeChoice;
        std::cin >> accountTypeChoice;
        std::cin.ignore();

        if (accountTypeChoice == 1)
        {
            type = "Savings";
        }
        else if (accountTypeChoice == 2)
        {
            type = "Current";
        }
        else
        {
            std::cout << "Invalid choice. Defaulting to Savings account.\n";
            type = "Savings";
            std::cout << "__________________________________________________________\n";
        }

        std::cout << "Enter your name: ";
        std::getline(std::cin, name);

        std::cout << "Enter your password: ";
        std::getline(std::cin, password);

        CreateAccount(name, balance, password, type, usertype);
    }
};

void showAdminMenu()
{
    std::cout << "_____________________[Admin Menu]_____________________\n\n";
    std::cout << "      1. View Profile\n";
    std::cout << "      2. Deposit\n";
    std::cout << "      3. Withdraw\n";
    std::cout << "      4. Update Account Details\n";
    std::cout << "_____________________[Admin Options]__________________\n";
    std::cout << "      5. Update Account Status of Users\n";
    std::cout << "      6. Delete Account of Users\n";
    std::cout << "      7. Search Account of Users\n";
    std::cout << "      8.. Logout\n";
    std::cout << "_____________________________________________________\n";
}

void showUserMenu()
{
    std::cout << "_____________________[User Menu]_____________________\n\n";
    std::cout << "      1. View Profile\n";
    std::cout << "      2. Deposit\n";
    std::cout << "      3. Withdraw\n";
    std::cout << "      4. Update Account Details\n";
    std::cout << "      5. Logout\n";
    std::cout << "_____________________________________________________\n";
}

int main()
{
    while (true)
    {
        std::cout << "______________________[Bank Management System]_______________________";
        std::cout << "\n           Welcome to the Bank Management System\n\n";
        std::cout << "      1. Login\n";
        std::cout << "      2. Create New Account\n";
        std::cout << "      3. Exit\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1)
        {
            std::string name, password;
            std::cout << "Enter your name: ";
            std::getline(std::cin, name);
            std::cout << "Enter your password: ";
            std::getline(std::cin, password);

            int id;
            std::string storedName, type, usertype, status, statusUpdate, AccDel, SrcName;
            double balance;

            if (SearchByNameAndPassword(name, password, id, storedName, balance, type, usertype, status))
            {
                std::cout << "_______________________________________________________________________\n";
                std::cout << "Login successful!\nWelcome, [" << storedName << "]\n\n";

                if (usertype == "Admin")
                {
                    while (true)
                    {
                        showAdminMenu();
                        std::cout << "Enter your choice: ";
                        int adminChoice;
                        std::cin >> adminChoice;
                        std::cin.ignore();

                        switch (adminChoice)
                        {
                        case 1:
                            SearchAccount(storedName);
                            break;
                        case 2:
                            Deposit(storedName);
                            break;
                        case 3:
                            Withdraw(storedName);
                            break;
                        case 4:
                            UpdateUserDetails(id, storedName);
                            break;
                        case 5:
                            std::cout << "Name of the user to update status: \n";
                            std::getline(std::cin, statusUpdate);

                            UpdateAccountStatus(statusUpdate);
                            break;
                        case 6:
                            std::cout << "Enter ID or Name to delete account: ";
                            std::getline(std::cin, AccDel);

                            DeleteAccount(AccDel);
                            break;
                        case 7:
                            std::cout << "Enter Name to search account: ";
                            std::getline(std::cin, SrcName);
                            SearchAccountAdmin(SrcName);
                            break;
                        case 8:
                            std::cout << "Logging out...\n";
                            std::cout << "_______________________________________________________________________\n";
                            goto mainMenu;
                        default:
                            std::cout << "Invalid choice. Try again.\n";
                        }
                    }
                }
                else if (usertype == "Regular")
                {
                    while (true)
                    {
                        showUserMenu();
                        std::cout << "Enter your choice: ";
                        int userChoice;
                        std::cin >> userChoice;
                        std::cin.ignore();

                        switch (userChoice)
                        {
                        case 1:
                            SearchAccount(storedName);
                            break;
                        case 2:
                            Deposit(storedName);
                            break;
                        case 3:
                            Withdraw(storedName);
                            break;
                        case 4:
                            UpdateUserDetails(id, storedName);
                            break;
                        case 5:
                            std::cout << "Logging out...\n";
                            std::cout << "_______________________________________________________________________\n";
                            goto mainMenu;
                        default:
                            std::cout << "Invalid choice. Try again.\n";
                        }
                    }
                }
            }
            else
            {
                std::cout << "Invalid name or password. Try again.\n";
            }
        }
        else if (choice == 2)
        {
            Account newAccount;
            newAccount.createAccount();
        }
        else if (choice == 3)
        {
            std::cout << "Exiting the system. Goodbye!\n";
            break;
        }
        else
        {
            std::cout << "Invalid choice. Try again.\n";
        }

    mainMenu:
        continue;
    }

    return 0;
}

// Printing account information
// Regular
void showInfo(int id, std::string name, double accBalance, std::string type, std::string usertype, std::string status)
{
    std::cout << "=================[Account Information]=================\n";
    std::cout << "ID                : " << id << std::endl;
    std::cout << "Name              : " << name << std::endl;
    std::cout << "Account Balance   : " << accBalance << std::endl;
    std::cout << "Account Type      : " << type << std::endl;
    std::cout << "User Type         : " << usertype << std::endl;
    std::cout << "Status            : " << status << std::endl;
    std::cout << "=======================================================\n";
}

// User View
void showInfo(int id, std::string name, double accBalance, std::string type, std::string pass, std::string usertype, std::string status)
{
    std::cout << "=================[Account Information]=================\n";
    std::cout << "ID                : " << id << std::endl;
    std::cout << "Name              : " << name << std::endl;
    std::cout << "Account Balance   : " << accBalance << std::endl;
    std::cout << "Account Type      : " << type << std::endl;
    std::cout << "Password          : " << pass << std::endl;
    std::cout << "User Type         : " << usertype << std::endl;
    std::cout << "Status            : " << status << std::endl;
    std::cout << "=======================================================\n";
}

// CRUD OPERATIONS
// Create Account
void CreateAccount(std::string name, double accBalance, std::string pass, std::string type, std::string usertype)
{
    std::ifstream file("Accounts.txt");
    std::string line;
    int maxId = 0;

    // Finding the highest existing ID
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr;
        std::getline(ss, idStr, '|');
        int id = std::stoi(idStr);
        if (id > maxId)
        {
            maxId = id;
        }
    }
    file.close();

    // Assigning new ID
    int newId = maxId + 1;

    // Writing to file in append mode
    std::ofstream outFile("Accounts.txt", std::ios::app);
    outFile << newId << "|" << name << "|" << accBalance << "|" << pass << "|" << type << "|" << usertype << "|Normal" << std::endl;
    outFile.close();

    std::cout << "Account created! \n ";
    showInfo(newId, name, accBalance, type, usertype, "Normal");
}

// Search Account
void SearchAccount()
{
    std::ifstream file("Accounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    std::string input;
    std::cout << "Enter ID or Name to search: ";
    std::cin.ignore();
    std::getline(std::cin, input);

    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, name, balanceStr, pass, type, usertype, status;

        std::getline(ss, idStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, balanceStr, '|');
        std::getline(ss, pass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

        int id = std::stoi(idStr);
        double accBalance = std::stod(balanceStr);

        // Comparing inputs with either ID or name (case-sensitive)
        if (input == idStr || input == name)
        {
            showInfo(id, name, accBalance, type, pass, usertype, status);
            found = true;
            break;
        }
    }

    if (!found)
    {
        std::cout << "No such user found.\n";
    }

    file.close();
}

void SearchAccount(const std::string &storedName)
{
    std::ifstream file("Accounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, name, balanceStr, pass, type, usertype, status;

        std::getline(ss, idStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, balanceStr, '|');
        std::getline(ss, pass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

        // Check if the current line matches the logged-in user's ID or name
        if (storedName == name)
        {
            int userId = std::stoi(idStr);
            double accBalance = std::stod(balanceStr);
            showInfo(userId, name, accBalance, type, pass, usertype, status);
            found = true;
            break;
        }
    }

    if (!found)
    {
        std::cout << "No such user found.\n";
    }

    file.close();
}
void SearchAccountAdmin(const std::string &storedName)
{
    std::ifstream file("Accounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, name, balanceStr, pass, type, usertype, status;

        std::getline(ss, idStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, balanceStr, '|');
        std::getline(ss, pass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

        // Check if the current line matches the logged-in user's name
        if (storedName == name)
        {
            int userId = std::stoi(idStr);
            double accBalance = std::stod(balanceStr);
            showInfo(userId, name, accBalance, type, usertype, status);
            found = true;
            break;
        }
    }

    if (!found)
    {
        std::cout << "No such user found.\n";
    }

    file.close();
}

// User Update Name or password
void UpdateUserDetails(int id, const std::string &storedName)
{
    std::ifstream file("Accounts.txt");
    std::ofstream tempFile("TempAccounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, name, balanceStr, pass, type, usertype, status;

        std::getline(ss, idStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, balanceStr, '|');
        std::getline(ss, pass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

        // Check if the current line matches the logged-in user's ID or name
        if (std::to_string(id) == idStr && storedName == name)
        {
            std::cout << "Account found. What would you like to update?\n";
            std::cout << "1. Name\n2. Password\nEnter your choice: ";
            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
            case 1:
                std::cout << "Enter new name: ";
                std::getline(std::cin, name);
                break;
            case 2:
                std::cout << "Enter new password: ";
                std::getline(std::cin, pass);
                break;
            default:
                std::cout << "Invalid choice. No changes made.\n";
                break;
            }

            // Write updated user information to the temp file
            tempFile << idStr << "|" << name << "|" << balanceStr << "|" << pass << "|"
                     << type << "|" << usertype << "|" << status << std::endl;
            found = true;
        }
        else
        {
            // Write the original line back for accounts that don't match
            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();

    if (found)
    {
        std::remove("Accounts.txt");
        std::rename("TempAccounts.txt", "Accounts.txt");
        std::cout << "Account details updated successfully.\n";
    }
    else
    {
        std::remove("TempAccounts.txt");
        std::cout << "No such user found.\n";
    }
}

//[Admin Feature]
// Update Account Status
void UpdateAccountStatus(const std::string &storedName)
{
    std::ifstream file("Accounts.txt");
    std::ofstream tempFile("TempAccounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, name, balanceStr, pass, type, usertype, status;

        std::getline(ss, idStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, balanceStr, '|');
        std::getline(ss, pass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

        // Check if the current line matches the logged-in user's ID or name
        if (storedName == name)
        {
            std::cout << "Current Status: " << status << "\n";
            std::cout << "Choose new status:\n";
            std::cout << "1. Normal\n2. Blocked\n3. Suspended\n4. Closed\nEnter: ";

            int choice;
            std::cin >> choice;

            std::string newStatus;
            switch (choice)
            {
            case 1:
                newStatus = "Normal";
                break;
            case 2:
                newStatus = "Blocked";
                break;
            case 3:
                newStatus = "Suspended";
                break;
            case 4:
                newStatus = "Closed";
                break;
            default:
                std::cout << "Invalid input. Status unchanged.\n";
                newStatus = status;
                break;
            }

            tempFile << idStr << "|" << name << "|" << balanceStr << "|" << pass << "|"
                     << type << "|" << usertype << "|" << newStatus << std::endl;

            found = true;
        }
        else
        {
            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();

    if (found)
    {
        std::remove("Accounts.txt");
        std::rename("TempAccounts.txt", "Accounts.txt");
        std::cout << "Account status updated successfully.\n";
    }
    else
    {
        std::remove("TempAccounts.txt");
        std::cout << "No such user found.\n";
    }
}

void DeleteAccount(const std::string &storedName)
{
    std::ifstream file("Accounts.txt");
    std::ofstream tempFile("TempAccounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }
    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, name, balanceStr, pass, type, usertype, status;

        std::getline(ss, idStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, balanceStr, '|');
        std::getline(ss, pass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

        if (storedName == name)
        {
            std::cout << "Account with ID: " << idStr << " and Name: " << name << " will be deleted.\n";
            found = true;
            continue;
        }

        tempFile << line << std::endl;
    }

    file.close();
    tempFile.close();

    if (found)
    {
        std::remove("Accounts.txt");
        std::rename("TempAccounts.txt", "Accounts.txt");
        std::cout << "Account deleted successfully.\n";
    }
    else
    {
        std::remove("TempAccounts.txt");
        std::cout << "No such user found.\n";
    }
}
// Login Feature
bool SearchByNameAndPassword(const std::string &name, const std::string &password, int &id, std::string &storedName, double &balance, std::string &type, std::string &usertype, std::string &status)
{
    std::ifstream file("Accounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return false;
    }

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, storedPass;

        std::getline(ss, idStr, '|');
        std::getline(ss, storedName, '|');
        std::string balanceStr;
        std::getline(ss, balanceStr, '|');
        balance = std::stod(balanceStr);
        std::getline(ss, storedPass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

        id = std::stoi(idStr);

        // Checking if both name and password match
        if (storedName == name && storedPass == password)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
// Activity Logs
void LogDeposit(int id, const std::string &name, double depositAmount, double newBalance)
{
    std::ofstream logFile("Deposits.txt", std::ios::app);

    if (!logFile)
    {
        std::cout << "Failed to open Deposits.txt for logging.\n";
        return;
    }

    // Get current date and time
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);

    logFile << "ID: " << id
            << ", Name: " << name
            << ", Deposit Amount: " << depositAmount
            << ", New Balance: " << newBalance
            << ", Date: " << (localTime->tm_year + 1900) << "-" << (localTime->tm_mon + 1) << "-" << localTime->tm_mday
            << ", Time: " << localTime->tm_hour << ":" << localTime->tm_min
            << std::endl;

    logFile.close();
}

void LogWithdraw(int id, const std::string &name, double withdrawAmount, double newBalance)
{
    std::ofstream logFile("Withdrawals.txt", std::ios::app);

    if (!logFile)
    {
        std::cout << "Failed to open Withdrawals.txt for logging.\n";
        return;
    }

    // Getting current date and time
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);

    logFile << "ID: " << id
            << ", Name: " << name
            << ", Withdrawal Amount: " << withdrawAmount
            << ", New Balance: " << newBalance
            << ", Date: " << (localTime->tm_year + 1900) << "-" << (localTime->tm_mon + 1) << "-" << localTime->tm_mday
            << ", Time: " << localTime->tm_hour << ":" << localTime->tm_min
            << std::endl;

    logFile.close();
}
// Core Features
void Deposit(const std::string &input)
{
    std::ifstream file("Accounts.txt");
    std::ofstream tempFile("TempAccounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, name, balanceStr, pass, type, usertype, status;

        std::getline(ss, idStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, balanceStr, '|');
        std::getline(ss, pass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

        int id = std::stoi(idStr);
        double balance = std::stod(balanceStr);

        // Check if the input matches the ID or name
        if (input == idStr || input == name)
        {
            found = true;

            // Checking if the account status is "Normal"
            if (status != "Normal")
            {
                std::cout << "Deposit not allowed. Account status is: " << status << "\n";
                tempFile << line << std::endl;
                continue;
            }

            double depositAmount;
            std::cout << "Enter deposit amount (max 500,000.00): ";
            std::cin >> depositAmount;

            if (depositAmount <= 50 || depositAmount > 500000.00)
            {
                std::cout << "Invalid deposit amount. Deposit must be between 50 and 500,000.00.\n";
                tempFile << line << std::endl;
                continue;
            }

            // Updating balance
            balance += depositAmount;
            std::cout << "Deposit successful! New balance: " << balance << "\n";

            // updated account information to the temp file
            tempFile << idStr << "|" << name << "|" << balance << "|" << pass << "|"
                     << type << "|" << usertype << "|" << status << std::endl;

            // Log the deposit
            LogDeposit(id, name, depositAmount, balance);
        }
        else
        {

            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();

    if (found)
    {
        std::remove("Accounts.txt");
        std::rename("TempAccounts.txt", "Accounts.txt");
    }
    else
    {
        std::remove("TempAccounts.txt");
        std::cout << "No such user found.\n";
    }
}

void Withdraw(const std::string &input)
{
    std::ifstream file("Accounts.txt");
    std::ofstream tempFile("TempAccounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, name, balanceStr, pass, type, usertype, status;

        std::getline(ss, idStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, balanceStr, '|');
        std::getline(ss, pass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

        int id = std::stoi(idStr);
        double balance = std::stod(balanceStr);

        // Checking if the input matches the ID or name
        if (input == idStr || input == name)
        {
            found = true;

            // Check if the account status is "Normal"
            if (status != "Normal")
            {
                std::cout << "Withdrawal not allowed. Account status is: " << status << "\n";
                tempFile << line << std::endl;
                continue;
            }

            double withdrawAmount;
            std::cout << "Enter withdrawal amount: ";
            std::cin >> withdrawAmount;

            if (withdrawAmount <= 10 || withdrawAmount > balance)
            {
                std::cout << "Invalid withdrawal amount. It must be greater than 10 and less than or equal to your current balance.\n";
                tempFile << line << std::endl;
                continue;
            }

            // Update balance
            balance -= withdrawAmount;
            std::cout << "Withdrawal successful! New balance: " << balance << "\n";

            // updated account information to the temp file
            tempFile << idStr << "|" << name << "|" << balance << "|" << pass << "|"
                     << type << "|" << usertype << "|" << status << std::endl;

            // Log the withdrawal
            LogWithdraw(id, name, withdrawAmount, balance);
        }
        else
        {

            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();

    if (found)
    {
        std::remove("Accounts.txt");
        std::rename("TempAccounts.txt", "Accounts.txt");
    }
    else
    {
        std::remove("TempAccounts.txt");
        std::cout << "No such user found.\n";
    }
}
