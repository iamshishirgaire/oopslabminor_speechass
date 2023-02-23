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
    }

    void logOut()
    {
    }

    AuthModel getCurrentUser()
    {
    }
}