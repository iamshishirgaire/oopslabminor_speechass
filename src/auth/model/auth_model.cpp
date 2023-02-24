

#include "string"
#include "../../../ext_lib/json.hpp"
using namespace std;

using json = nlohmann::json;

class AuthModel
{
public:
    string name;
    string email;
    string password;

    AuthModel(string Name, string Password, string Email)
    {
        name = Name;
        email = Email;
        password = Password;
    };
    AuthModel(){};
    json toJson(AuthModel &authModel)
    {
        json jsonAuth;
        jsonAuth["name"] = name;
        jsonAuth["email"] = email;
        jsonAuth["password"] = password;
        return jsonAuth;
    };

    AuthModel(json &authJson)
    {
        name = authJson["name"];
        email = authJson["email"];
        password = authJson["password"];
    };
};