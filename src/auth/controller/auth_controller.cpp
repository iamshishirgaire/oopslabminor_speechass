#include "string"
#include "../repository/auth_repo.cpp"
#include "../model/auth_model.cpp"
class AuthController
{
    AuthRepo _authRepo;

public:
    void signup(AuthModel &user)
    {
        _authRepo.signUp(user.email, user.password, user.name);
    };
    void signin(AuthModel &user)
    {
        _authRepo.signIn(user.email, user.password, user.name);
    };
    void logout()
    {
        _authRepo.logOut();
    };

    json getcurrentUser()
    {
        return _authRepo.getCurrentUser();
    };
    string getcurrentusername(){
        return _authRepo.getCurrentUsername();
    }

    bool isLoggedin()
    {
        return _authRepo.isLoggedIn();
    }
};