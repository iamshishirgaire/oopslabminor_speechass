#include <iostream>
#include <termios.h>
#include <unistd.h>
// string getPassword() {
//     string password;
//     struct termios oldSettings, newSettings;

//     // Disable terminal echo
//     tcgetattr(STDIN_FILENO, &oldSettings);
//     newSettings = oldSettings;
//     newSettings.c_lflag &= ~(ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

//     // Read password
//     cin>>password;

//     // Enable terminal echo
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

//     return password;
// }

// write a function to accept password as input and make the text buffer filled with *  and returns the password as string
std::string getPassword()
{
    std::string password;
    char ch;

    std::cout << "Enter your password: ";

    while (true)
    {

        if (ch == '\r')
        {
            std::cout << std::endl;
            break;
        }

        password += ch;
        std::cout << "*";
    }

    return password;
}