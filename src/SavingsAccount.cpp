#include <iostream>
#include <string>
#include "Account.cpp"

using namespace std;

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
