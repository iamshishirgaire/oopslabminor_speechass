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
            if(jsonData[username]== username &&jsonData[email] == email)
                return true;
        }
        fos.closeFile(file);
        return false;
    }
    void signUp(string email, string password, string username)
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
        else if(isUserExists(email, username)){
            cout<<"User already exist";
            return;
        }
        else
        {
            auto logInFile = fos.openFileForWriting(usersFile, true);
            json jsonData;
            jsonData["username"] = username;
            jsonData["password"] = password;        
            jsonData["email"] = email;
            fos.writeFile(usersFile, jsonData);
            fos.closeFile(logInFile);
        }
    }
    void signIn(string email, string password)
    {
        ifstream file(usersFile);
        string line;
        while (getline(file, line))
        {   
            json jsonData = json::parse(line);
            if(jsonData[email]== email &&jsonData[password] == password)
            {
                json loggedInData;
                loggedInData["loggedInStatus"] = true;
                loggedInData["email"] = email;
                loggedInData["username"] = jsonData[username];
                loggedInData["password"] = password;
                auto file = fos.openFileForWriting(currentAuthStatusFile, false);
                fos.writeFile(file, loggedInData);
                fos.closeFile(file);
            }
    }
    void logOut(bool true)
    {
        json jsonData;
        loggedInData["loggedInStatus"] = false;
        loggedInData["email"] = "";
        loggedInData["username"] = "";
        loggedInData["password"] = "";
        auto file = fos.openFileForWriting(currentAuthStatusFile, false);
        fos.writeFile(file,jsonData);
        fos.closeFile(file);
    }

    json getCurrentUser()
    {
        ifstream file(currentAuthStatusFile);
        string line;
        getline(file, line);
        json jsonData = json::parse(line);
        return jsonData;
    }
};