

#include "string"
#include "../../../ext_lib/json.hpp"
using json = nlohmann::json;

class AuthModel
{
public:
    string name;
    string email;
    string password;
    AuthModel(string Name, string Password, string Email)
    {
        this->name = Name;
        this->email = Email;
        this->password = Password;
    }
    void toJson(AuthModel authModel)
    {
        json jsonAuth;
        jsonAuth["name"] = name;
        jsonAuth["email"] = email;
        jsonAuth["password"] = password;
    }

    AuthModel(json authJson)
    {
        this->name = authJson["name"];
        this->email = authJson["email"];
        this->password = authJson["password"];
    }
};