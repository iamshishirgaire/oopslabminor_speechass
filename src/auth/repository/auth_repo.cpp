#include "string"
using json = nlohmann::json;
#include "../../core/utils/file_operations.cpp"
#include "../../core/validators/credentials_validator.cpp"

class AuthRepo
{

    FileOperations fos;
    CredentialValidator cv;

public:
    const string usersFile = "../../../database/users/users.csv";
    const string currentAuthStatusFile = "../../../database/current_auth/current_auth.csv";

    bool isUserExists(static const std::string email, static const std::string username)
    {
        ifstream file(usersFile);
        string line;
        while (getline(file, line))
        {
            json jsonData = json::parse(line);
            if (jsonData[username] == username && jsonData[email] == email)
                return true;
        }
        fos.closeFile(file);
        return false;
    }
    bool signUp(string email, string password, string username)
    {

        if (!c)
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

// json jsonData;
//         jsonData["username"] = username;
//         jsonData["password"] = password;
//         jsonData["email"] = email;