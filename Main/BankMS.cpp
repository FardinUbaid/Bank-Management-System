#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime> // Required for date and time

// Print Functions
void showInfo(int id, std::string name, double accBalance, std::string type, std::string usertype, std::string status);
void showInfo(int id, std::string name, double accBalance, std::string type, std::string pass, std::string usertype, std::string status);

// CRUD Operations
void CreateAccount(std::string name, double accBalance, std::string pass, std::string type, std::string usertype);
void SearchAccount();
void UpdateUserDetails();
// Admin Features
void UpdateAccountStatus();
void DeleteAccount();
// Login Feature
bool SearchByNameAndPassword(const std::string &name, const std::string &password);
// Core Features
void Deposit(const std::string &input);
void Withdraw(const std::string &input);
// Activity Log Functions
void LogDeposit(int id, const std::string &name, double depositAmount, double newBalance);
void LogWithdraw(int id, const std::string &name, double withdrawAmount, double newBalance);

int main()
{
    // Example usage
    // CreateAccount("John Doe", 1000.0, "password123", "Savings", "Regular");
    // UpdateAccountStatus();

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
    std::cin.ignore(); // To flush newline from previous input
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
// User Update Name or password
void UpdateUserDetails()
{
    std::ifstream file("Accounts.txt");
    std::ofstream tempFile("TempAccounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    std::string input;
    std::cout << "Enter your ID or Name to update details: ";
    std::cin.ignore(); // To flush newline from previous input
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

        if (input == idStr || input == name)
        {
            std::cout << "Account found. What would you like to update?\n";
            std::cout << "1. Name\n2. Password\nEnter your choice: ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(); // To flush newline from input buffer

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

            tempFile << idStr << "|" << name << "|" << balanceStr << "|" << pass << "|"
                     << type << "|" << usertype << "|" << status << std::endl;
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
void UpdateAccountStatus()
{
    std::ifstream file("Accounts.txt");
    std::ofstream tempFile("TempAccounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    std::string input;
    std::cout << "Enter ID or Name to update status: ";
    std::cin.ignore(); // To flush newline from previous input
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

        if (input == idStr || input == name)
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

void DeleteAccount()
{
    std::ifstream file("Accounts.txt");
    std::ofstream tempFile("TempAccounts.txt");
    std::string line;

    if (!file)
    {
        std::cout << "Accounts.txt not found.\n";
        return;
    }

    std::string input;
    std::cout << "Enter ID or Name to delete account: ";
    std::cin.ignore(); // To flush newline from previous input
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

        if (input == idStr || input == name)
        {
            std::cout << "Account with ID: " << idStr << " and Name: " << name << " will be deleted.\n";
            found = true;
            continue; // Skip writing this line to the temp file
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
bool SearchByNameAndPassword(const std::string &name, const std::string &password)
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
        std::string idStr, storedName, balanceStr, storedPass, type, usertype, status;

        std::getline(ss, idStr, '|');
        std::getline(ss, storedName, '|');
        std::getline(ss, balanceStr, '|');
        std::getline(ss, storedPass, '|');
        std::getline(ss, type, '|');
        std::getline(ss, usertype, '|');
        std::getline(ss, status, '|');

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

void LogDeposit(int id, const std::string &name, double depositAmount, double newBalance)
{
    std::ofstream logFile("Deposits.txt", std::ios::app); // Open in append mode

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
    std::ofstream logFile("Withdrawals.txt", std::ios::app); // Open in append mode

    if (!logFile)
    {
        std::cout << "Failed to open Withdrawals.txt for logging.\n";
        return;
    }

    // Get current date and time
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

            // Check if the account status is "Normal"
            if (status != "Normal")
            {
                std::cout << "Deposit not allowed. Account status is: " << status << "\n";
                tempFile << line << std::endl; // Write the original line back
                continue;
            }

            // Prompt for deposit amount
            double depositAmount;
            std::cout << "Enter deposit amount (max 500,000.00): ";
            std::cin >> depositAmount;

            if (depositAmount <= 0 || depositAmount > 500000.00)
            {
                std::cout << "Invalid deposit amount. Deposit must be between 0.01 and 500,000.00.\n";
                tempFile << line << std::endl; // Write the original line back
                continue;
            }

            // Update balance
            balance += depositAmount;
            std::cout << "Deposit successful! New balance: " << balance << "\n";

            // Write updated account information to the temp file
            tempFile << idStr << "|" << name << "|" << balance << "|" << pass << "|"
                     << type << "|" << usertype << "|" << status << std::endl;

            // Log the deposit
            LogDeposit(id, name, depositAmount, balance);
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

        // Check if the input matches the ID or name
        if (input == idStr || input == name)
        {
            found = true;

            // Check if the account status is "Normal"
            if (status != "Normal")
            {
                std::cout << "Withdrawal not allowed. Account status is: " << status << "\n";
                tempFile << line << std::endl; // Write the original line back
                continue;
            }

            // Prompt for withdrawal amount
            double withdrawAmount;
            std::cout << "Enter withdrawal amount: ";
            std::cin >> withdrawAmount;

            if (withdrawAmount <= 500 || withdrawAmount > balance)
            {
                std::cout << "Invalid withdrawal amount. It must be greater than 500 and less than or equal to your current balance.\n";
                tempFile << line << std::endl; // Write the original line back
                continue;
            }

            // Update balance
            balance -= withdrawAmount;
            std::cout << "Withdrawal successful! New balance: " << balance << "\n";

            // Write updated account information to the temp file
            tempFile << idStr << "|" << name << "|" << balance << "|" << pass << "|"
                     << type << "|" << usertype << "|" << status << std::endl;

            // Log the withdrawal
            LogWithdraw(id, name, withdrawAmount, balance);
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
    }
    else
    {
        std::remove("TempAccounts.txt");
        std::cout << "No such user found.\n";
    }
}
