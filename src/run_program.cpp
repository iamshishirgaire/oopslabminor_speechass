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
            int answer;
            cout << "Select one of the options..............\n";
            cout << "1. Assessment\n";
            cout << "2. History\n";
            cout << "3. Logout\n";
            cout << "4. Exit\n";
            cout << "Select your option [1-4] : ";
            cin >> answer;
            if (answer == 1)
            {
                AssessmentView::viewAssessmentResult(TranscriptionResult(AssessmentController::getAssessmentRes()));
            }
            else if (answer == 2)
            {
                cout << "Your history : \n";

                json user = _ac.getcurrentUser();
                string name = user["name"];
                cout << _hr.getHistory(name);
            }
            else if (answer == 3)
            {
                _ac.logout();
                exit(0);
            }
            else if (answer == 4)
            {
                exit(0);
            }

            else
            {
                cout << "Invalid input\n";
            }
        }
        else if (!isLogged)
        {
            bool isAlreadyAUser;
            cout << "Already a user ?[Y/N]";
            string res;
            cin >> res;
            isAlreadyAUser = res == "Y" || "y" ? true : false;
            if (!isAlreadyAUser)
            {
                cout << "Signing in ......... \n";

                AuthModel user;
                cout << "Please enter your email : \n";
                getline(cin, user.email);
                cout << "\n";

                cout << "Please enter your password : \n";
                getline(cin, user.password);
                cout << "\n Signing up .................";

                _ac.signin(user);
            }

            else
            {
                cout << "Signing up ......... \n";
                AuthModel user;

                cout << "Please enter your name : ";
                getline(cin, user.name);
                cout << "\n";
                cout << "Please enter your email : ";
                getline(cin, user.email);
                cout << "\n";

                cout << "Please enter your password : ";
                getline(cin, user.password);
                cout << "\n Signing in .................";

                AuthController().signup(user);
            }
        }
    };
};