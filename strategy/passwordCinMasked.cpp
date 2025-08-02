#include "passwordCinMasked.hpp"

std::string getHiddenPassword();
{
    std::string password;

    #if defined(_WIN32) || defined(_WIN64)
        while((ch = _getch()) != '\r') {
        if(ch == '\b') {
            if(!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";  // apaga o '*' no console
            }
        } else {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << "\n";

    #elif defined(__linux__) || defined(__APPLE__)
        termios oldt;
        termios newt;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        std::getline(std::cin, *password);

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        std::cout << "\n";
    #endif
}