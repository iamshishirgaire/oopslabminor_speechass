using "string" using namespace std;
#include "regex"
class CredentialValidator
{
public:
    bool isValidEmail(const std::string &email)
    {
        const std::regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
        return std::regex_match(email, pattern);
    }

    bool isPassword(const string &password)
    {
        return password.length() >= 7;
    };
}