#include "iostream"
#include "string"
#include "assm_result/controller/assm_controller.cpp"
#include "auth/controller/auth_controller.cpp"
#include "core/utils/ass_view.cpp"
#include "history/controller/history_controller.cpp"

using namespace std;
class AssessmentProgram
{
    AuthController _ac;
    HistoryController _hr;

public:
    void runProgram()
    {
        bool isLogged = _ac.isLoggedin();

        if (isLogged)
        {

            auto res = AssessmentController::getAssessmentRes();
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