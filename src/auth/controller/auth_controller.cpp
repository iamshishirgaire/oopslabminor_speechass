#include "string"
#include "../model/auth_model.cpp"
#include "../repository/auth_repo.cpp"
#include "../model/auth_model.cpp"
class AuthController
{
public:
    AuthRepo _authRepo;
    void signUp(AuthModel &user)
    {
        _authRepo.signUp(user.email, user.password, user.name);
    };
    void signIn(AuthModel &user)
    {
        _authRepo.signIn(user.email, user.password, user.name);
    };
    void logOut()
    {
        _authRepo.logOut(true);
    };

    void getCurrentUser()
    {
        _authRepo.getCurrentUser();
    };
};