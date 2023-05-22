#include "iostream"
#include "string"
#include "assm_result/controller/assm_controller.cpp"
#include "auth/controller/auth_controller.cpp"
#include "core/utils/ass_view.cpp"
#include "history/controller/history_controller.cpp"
#include "../ext_lib/json.hpp"

using json = nlohmann::json;

using namespace std;
class AssessmentProgram
{
    AssessmentController _asc;
    AuthController _ac;
    HistoryController _hr;

public:
    void runProgram()
    {
    start:
        bool isLogged = _ac.isLoggedin();

        if (isLogged == true)
        {

            int answer;
            cout << "Select one of the options..............\n";
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
                AssessmentView::viewAssessmentResult(TranscriptionResult(res));

                char ans;
                cout << "Are you sure you want to store this result in history?[Y/N]";
                cin >> ans;
                cin.ignore();

                if (ans == 'Y' || ans == 'y')
                {

                    json user = _ac.getcurrentUser();
                    string name = user["username"];

                    _hr.postHistory(name, res);

                    goto start;
                }
                else
                {
                    cout << "not ans";
                    goto start;
                }
            }
            else if (answer == 2)
            {
                cout << "Your history : \n";

                json user = _ac.getcurrentUser();
                string username = user["username"];
                // cout<<username;
                cout << "\nYour history................\n";
                // cout<<name;
                auto res = _hr.getHistory(username);
                for (int i = 0; i < res.size(); i++)
                {
                    if (res[i]["username"] == username)
                    {
                        AssessmentView::viewAssessmentResult(TranscriptionResult(res[i]["result"]));
                    }
                }

                // cout<<res ;
                // cout << _hr.getHistory(name);
                goto start;
            }
            else if (answer == 3)
            {
                char ans;
                cout << "Are you sure you want to log out?[Y/N]";
                cin >> ans;
                cin.ignore();
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
            cout << "Already a user ?[Y/N]";
            char res;
            cin >> res;
            cin.ignore();
            isAlreadyAUser = (res == 'Y' || res == 'y') ? true : false;
            if (isAlreadyAUser == true)
            {
                cout << "Signing in ......... \n";

                AuthModel user;
                cout << "Please enter your email : \n";
                getline(cin, user.email);
                cin.ignore();

                cout << "\n";

                cout << "Please enter your password : \n";
                getline(cin, user.password);
                cin.ignore();

                cout << "\n Signing up .................";

                _ac.signin(user);
                goto start;
            }

            else
            {
                cout << "Signing up ......... \n";
                AuthModel user;

                cout << "Please enter your name : ";
                getline(cin, user.name);
                cin.ignore();

                cout << "\n";
                cout << "Please enter your email : ";
                getline(cin, user.email);
                cin.ignore();

                cout << "\n";

                cout << "Please enter your password : ";
                getline(cin, user.password);
                cin.ignore();

                cout << "\n Signing in .................";

                AuthController().signup(user);
                goto start;
            }
        }
    };
};