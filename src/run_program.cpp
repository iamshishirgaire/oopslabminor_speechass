#include "iostream"
#include "string"
#include "assm_result/controller/assm_controller.cpp"
#include "auth/controller/auth_controller.cpp"
#include "core/utils/ass_view.cpp"
#include "history/controller/history_controller.cpp"
#include "../ext_lib/json.hpp"
#include "core/utils/disable_terminal.cpp"
#include "core/utils/colors.cpp"

using json = nlohmann::json;

using namespace std;
class AssessmentProgram
{
    AssessmentController _asc;
    AuthController _ac;
    HistoryController _hr;
    ColorPalette _cp;

public:
    void runProgram()
    {
    start:
        clear();

        cout << _cp.Red << "\n\n...........Welcome to Assessment Program.............." << _cp.Reset << endl;
        bool isLogged = _ac.isLoggedin();

        if (isLogged == true)
        {

            int answer;
            cout << "\nSelect one of the options:\n";
            cout << "1. Assessment\n";
            cout << "2. History\n";
            cout << "3. Logout\n";
            cout << "4. Exit\n";
            cout << "Select your option [1-4] : ";
            cin >> answer;
            cin.ignore();

            if (answer == 1)
            {
                auto res = _asc.getAssessmentRes();
                AssessmentView().viewAssessmentResult(TranscriptionResult(res));
                char ans;
                cout << "Are you sure you want to store this result in history?[Y/N]";
                cin >> ans;
                if (ans == 'Y' || ans == 'y')
                {
                    _hr.postHistory(res);
                    goto start;
                }
                else
                {
                    goto start;
                }
            }
            else if (answer == 2)
            {

                json user = _ac.getcurrentUser();
                string username = user["username"];
                cout << "\nYour history................\n";
                auto res = _hr.getHistory(username);

                if (res.empty())
                {
                    cout << "\nNo history found.\n";
                    cout << "\nPress a key to continue: ";
                    cin.get();
                    goto start;
                }
                else
                {
                    for (int i = 0; i < res.size(); i++)
                    {

                        cout << "\n"
                             << i + 1 << ".\n ";
                        AssessmentView().viewAssessmentResult(TranscriptionResult(res[i]["result"]));
                    }
                }

                cin.get();
                goto start;
            }
            else if (answer == 3)
            {
                char ans;
                cout << "\nAre you sure you want to log out?[Y/N]:";
                cin >> ans;
                if (ans == 'Y' || ans == 'y')
                {
                    _ac.logout();
                    goto start;
                }
                else
                {
                    goto start;
                }
            }
            else if (answer == 4)
            {
                exit(0);
            }

            else
            {
                cout << "Invalid input\n";
                goto start;
            }
        }

        else
        {
            bool isAlreadyAUser;
            cout << "\n Already a user ?[Y/N]:";
            char res;
            cin >> res;
            isAlreadyAUser = (res == 'Y' || res == 'y') ? true : false;
            if (isAlreadyAUser)
            {
                cout << "......................................................... ";
                cout << "\nSigning In ......... ";

            signin:
                AuthModel user;
                cout << "\n\nPlease enter your email :";
                cin >> user.email;
                cout << "\nPlease enter your password :";
                user.password = getPassword();
                cout << " ......................................................... ";
                cout << "\nSigning up .................";
                bool res = _ac.signin(user);
                if (res)
                {

                    cout << "Sign in Successful!\n";
                    goto start;
                }

                else
                {
                    goto signin;
                }
            }

            else
            {
                cout << "\nSigning up";
                AuthModel user;
                string password1, password2;

                cout << "\nPlease enter your Username : ";
                cin >> user.name;

                cout << "\nPlease enter your email : ";
                cin >> user.email;

            again:
                cout << "\nPlease enter your password :";
                password1 = getPassword();

                cout << "\nEnter your password again : ";
                password2 = getPassword();

                if (password1 == password2)
                {
                    user.password = password1;
                    cout << "\nSigning in:";
                    AuthController().signup(user);
                }
                else
                {
                    cout << "\nPasswords do not match. Please re-enter:";
                    goto again;
                }

                goto start;
            }
        }
    };
};