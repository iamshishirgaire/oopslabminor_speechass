#include "string"

class AuthRepo
{
public:
    string loginFile = "";
    string currentStatusFile = "";

public:
    bool is(const std::string email, const std::string username)
    {
        ifstream file("logins.csv");
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find(',');
            string user = line.substr(0, pos);
            size_t pos2 = line.find(',', pos + 1);
            string pass = line.substr(pos + 1, pos2 - pos - 1);
            string mail = line.substr(pos2 + 1);
            if (mail == email || user == this->username)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    bool signUp(string email, string password, string username)
    {
        string fileName;
        bool emailValid = false;
        bool userEmailExists = false;
        emailValid = emailValidation(this->email);
        userEmailExists = checkExistingRecord();
        if (!emailValid)
        {
            cout << "email can't be accepted";
            return;
        }
        if (userEmailExists)
        {
            cout << "email already in record";
            return;
        }
        if (emailValid && !userEmailExists)
        {
            ofstream outFile("logins.csv", ios::app);
            if (outFile.is_open())
            {
                outFile << this->username << "," << this->password << "," << this->email << endl;
                fileName = "userFolder/" + this->username + ".csv";
                ofstream user(fileName);
                user.close();
                cout << "User created successfully." << endl;
                outFile.close();
            }
            else
            {
                cerr << "Error opening file." << endl;
            }
        }
    }

    void signIn(string email, string password)
    {
    }

    void logOut()
    {
    }

    void getCurrentUser()
    {
    }
};