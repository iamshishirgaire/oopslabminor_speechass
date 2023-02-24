
#include "string"
#include "auth/controller/auth_controller.cpp"
#include "auth/model/auth_model.cpp"
#include "core/utils/ass_view.cpp"
#include "assm_result/model/ass_model.cpp
#include "assm_result/controller/assm_controller.cpp"
#include "iostream"
using namespace std;

class AssessmentProgram
{
    bool isLogged false;

public:
    void runProgram()
    {
        if (isLogged)
        {
            string referenceText;
            cin << "Please Enter the refrence text : " << referenceText;
            AssessmentController::getAssessmentRes(TranscriptionResult(getRes()));
        }
        else if (!isLogged)
        {
            AuthModel user;
            cin << "Please enter your name : " << user.name;
            cin << "Please enter your email : " << user.email;
            cin << "Please enter your password :  " << user.password;
            AuthController().signUp(user);
        }
    }
}