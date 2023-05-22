#include "string"
#include "../../../ext_lib/json.hpp"
#include "iostream"
#include "../../core/utils/file_operations.cpp"
#include "../../core/validators/credentials_validator.cpp"
using namespace std;
using json = nlohmann::json;

class AuthRepo
{
    CredentialValidator cv;
    const string usersFile = "/home/sudipthakur/oopslabminor_speechass/database/users/users.csv";
    const string currentAuthStatusFile = "/home/sudipthakur/oopslabminor_speechass/database/current_auth/current_auth.csv";

public:
    bool isUserExists(const std::string &email, const std::string &username)
    {
        ifstream file(usersFile);
        string line;
        while (getline(file, line))
        {
            json jsonData = json::parse(line);
            if (jsonData[username] == username && jsonData[email] == email)
                return true;
        }
        FileOperations::closeFile(file);
        return false;
    }
    void signUp(const string &email, const string &password, const string &username)
    {
        if (!cv.isValidEmail(email))
        {
            cout << "Email can't be accepted";
            return;
        }
        else if (!cv.isValidPassword(password))
        {
            cout << "Minimum password should be of 8 characters.";
            return;
        }
        else if (isUserExists(email, username))
        {
            cout << "User already exist";
        }
        else
        {

            auto logInFile = FileOperations::openFileForWriting(usersFile, true);
            auto AuthFile = FileOperations::openFileForWriting(currentAuthStatusFile, false);

            json jsonData;
            jsonData["username"] = username;
            jsonData["password"] = password;
            jsonData["email"] = email;

            FileOperations::writeFile(logInFile, jsonData);
            json AuthStatus;
            AuthStatus["email"] = email;
            AuthStatus["username"] = username;
            AuthStatus["password"] = password;
            FileOperations::writeFile(AuthFile, AuthStatus);

            FileOperations::closeFile(logInFile);
            FileOperations::closeFile(AuthFile);
        }
    }
    void signIn(const string &email, const string &password, const string &userName)
    {

        // TODO :  refactor the signup logic
        auto readFile = FileOperations::openFileForReading(usersFile);
        string line;
        while (getline(readFile, line))
        {
            json jsonData = json::parse(line);
            if (jsonData["email"] == email && jsonData["password"] == password)
            {
                
                json loggedInData;
                loggedInData["email"] = email;
                loggedInData["username"] = jsonData["username"];
                loggedInData["password"] = password;
                auto file = FileOperations::openFileForWriting(currentAuthStatusFile, false);
                FileOperations::writeFile(file, loggedInData);
                FileOperations::closeFile(file);
            }
        }
    };
    void logOut()
    {
        json jsonData;
        jsonData["email"] = " ";
        jsonData["username"] = " ";
        jsonData["password"] = " ";

        auto file = FileOperations::openFileForWriting(currentAuthStatusFile, false);

        FileOperations::writeFile(file, jsonData);

        FileOperations::closeFile(file);
    };

    json getCurrentUser()
    {
        auto res = FileOperations::openFileForReading(currentAuthStatusFile);
        string line = FileOperations::readOneLine(res);
        json jsonData = json::parse(line);
        return jsonData;
    };

    bool isLoggedIn()
    {
        json data = getCurrentUser();
        string username = data["username"];
        auto res = username.length() == 1 ? false : true;
        return res;
    }
    string getCurrentUsername(){
        auto res = FileOperations::openFileForReading(currentAuthStatusFile);
        string line = FileOperations::readOneLine(res);
        json jsonData = json::parse(line);
        string name =  jsonData["username"];
        return name;
    }
};