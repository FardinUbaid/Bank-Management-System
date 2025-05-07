#include <iostream>
#include <string>
#include "Account.cpp"

using namespace std;

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
