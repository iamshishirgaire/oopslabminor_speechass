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
    const string usersFile = "../../../database/users/users.csv";
    const string currentAuthStatusFile = "../../../database/current_auth/current_auth.csv";

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
            cout << "email can't be accepted";
            return;
        }
        else if (!cv.isValidPassword(password))
        {
            cout << "email already in record";
            return;
        }
        else if (isUserExists(email, username))
        {
            cout << "User already exist";
            return;
        }
        else
        {
            auto logInFile = FileOperations::openFileForWriting(usersFile, true);
            json jsonData;
            jsonData["username"] = username;
            jsonData["password"] = password;
            jsonData["email"] = email;
            FileOperations::writeFile(logInFile, jsonData);
            FileOperations::closeFile(logInFile);
        }
    }
    void signIn(const string &email, const string &password, const string &userName)
    {
        auto readFile = FileOperations::openFileForReading(usersFile);
        string line;
        while (getline(readFile, line))
        {
            json jsonData = json::parse(line);
            if (jsonData[email] == email && jsonData[password] == password)
            {
                json loggedInData;
                loggedInData["loggedInStatus"] = true;
                loggedInData["email"] = email;
                loggedInData["username"] = jsonData[userName];
                loggedInData["password"] = password;
                auto file = FileOperations::openFileForWriting(currentAuthStatusFile, false);
                FileOperations::writeFile(file, loggedInData);
                FileOperations::closeFile(file);
            }
        }
    };
    void logOut(bool openForWriting)
    {
        json jsonData;

        auto file = FileOperations::openFileForWriting(currentAuthStatusFile, openForWriting);
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
};