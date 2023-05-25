#include <iostream>
#include <termios.h>
#include <unistd.h>

string getPassword()
{
    string password;
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    cin >> password;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    return password;
}

void clear()
{
    cout << "\033[2J\033[1;1H";
}