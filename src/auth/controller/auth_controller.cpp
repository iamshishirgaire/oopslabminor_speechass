#include "string"
#include "../model/auth_model.cpp"
#include "../repository/auth_repo.cpp"
class AuthController
{
public:
    AuthRepo _authRepo;
    void signUp(string email, string password, string username)
    {
        _authRepo.signUp(email, password, username);
    };

    void signIn(string email, string password)
    {

        _authRepo.signIn(email, password);
    };

    void logOut()
    {
        _authRepo.logOut();
    };

    void getCurrentUser()
    {
        _authRepo.getCurrentUser();
    };
};