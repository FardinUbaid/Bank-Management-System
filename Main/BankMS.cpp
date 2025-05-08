#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Print Functions
void showInfo(int id, std::string name, double accBalance, std::string type, std::string usertype, std::string status);
void showInfo(int id, std::string name, double accBalance, std::string type, std::string pass, std::string usertype, std::string status);

// CRUD Operations
void CreateAccount(std::string name, double accBalance, std::string pass, std::string type, std::string usertype);
void UpdateAccountStatus();

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
            std::cout << "Enter new status (e.g., Locked): ";
            std::string newStatus;
            std::getline(std::cin, newStatus);

            tempFile << idStr << "|" << name << "|" << balanceStr << "|" << pass << "|" << type << "|" << usertype << "|" << newStatus << std::endl;
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
