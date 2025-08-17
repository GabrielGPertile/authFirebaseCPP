#include "passwordCinMasked.hpp"

std::string getHiddenPassword()
{
    std::string password;
    char ch;

    std::cout << "Digite a sua senha (mínimo 6 caracteres): ";

    do {
#if defined(_WIN32) || defined(_WIN64)
        password.clear();

        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    std::cout << "\b \b";
                }
            } else {
                password += ch;
                std::cout << '*';
            }
            std::cout.flush();
        }
        std::cout << "\n";

#elif defined(__linux__) || defined(__APPLE__)
        password.clear();
        termios oldt;
        termios newt;

        std::cout << "Digite a sua senha (mínimo 6 caracteres): ";
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        std::getline(std::cin, password);

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        std::cout << "\n";

#else
        std::cout << "Plataforma não suportada, digite a senha (visível, mínimo 6 caracteres): ";
        std::getline(std::cin, password);
#endif

        if (password.length() < 6) {
            std::cout << "Senha muito curta! Digite pelo menos 6 caracteres.\n";
        }

    } while(password.length() < 6);

    return password;
}