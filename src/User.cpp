#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User
{
public:
    string username;
    string password;
    bool isAdmin;

    User() {}

    User(string user, string pass, bool admin = false)
    {
        username = user;
        password = pass;
        isAdmin = admin;
    }

    // Authenticate user from credentials file
    bool login(const string &inputUser, const string &inputPass)
    {
        ifstream infile("users.txt");
        string fileUser, filePass, type;

        while (infile >> fileUser >> filePass >> type)
        {
            if (fileUser == inputUser && filePass == inputPass)
            {
                username = fileUser;
                password = filePass;
                isAdmin = (type == "admin");
                infile.close();
                return true;
            }
        }

        infile.close();
        return false;
    }

    void displayRole()
    {
        cout << "Logged in as " << (isAdmin ? "Admin" : "User") << endl;
    }
};
