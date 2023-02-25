#include "iostream"
#include "string"

#include "assm_result/controller/assm_controller.cpp"
#include "auth/controller/auth_controller.cpp"
#include "core/utils/ass_view.cpp"

using namespace std;
class AssessmentProgram
{
    bool isLogged = true;

public:
    void runProgram()
    {
        if (isLogged)
        {
            string referenceText;
            cout << "Please Enter the refrence text : ";
            cin >> referenceText;
            auto res = AssessmentController::getAssessmentRes(referenceText);
            AssessmentView::viewAssessmentResult(TranscriptionResult(res));
        }
        else if (!isLogged)
        {
            AuthModel user;

            cout << "Please enter your name : ";
            cin >> user.name;
            cout << "Please enter your email : ";
            cin >> user.email;
            cout << "Please enter your password : ";
            cin >> user.password;
            AuthController().signup(user);
        }
    };
};