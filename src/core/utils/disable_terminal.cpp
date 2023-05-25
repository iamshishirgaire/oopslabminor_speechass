#include <iostream>
#include <termios.h>
#include <unistd.h>

string getPassword()
{

    string password;
    struct termios oldSettings, newSettings;
    // Disable terminal echo
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    //     // Read password
    cin >> password;

    //     // Enable terminal echo
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

    return password;
}

// function to clear the console screen in linux
void clear()
{
    cout << "\033[2J\033[1;1H";
}