#include "string"
#include "../model/auth_model.cpp"
#include "../repository/auth_repo.cpp"
class AuthController
{

    AuthRepo _authRepo;
    void signUp(string email, string password, string username)
    {
        _authRepo.signUp(email, password, username);
    }

    void signIn(string email, string password)
    {

        _authRepo.signIn(email, password);
    }

    void logOut()
    {
        _authRepo.logOut();
    }

    AuthModel getCurrentUser()
    {
        _authRepo.getCurrentUser();
    }
}