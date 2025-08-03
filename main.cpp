#include <iostream>
#include <string>
#include <limits>

#include "strategy/passwordCinMasked.hpp"

int main()
{
    char ch;

    bool conectado = 0;

    std::string email;
    std::string password;

    std::cout << "Digite o seu email:\n";
    std::cin >> email;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    password = getHiddenPassword();
    std::cout << "\n";

    std::cout << "Email: " << email << "\n";
    std::cout << "Senha: " << password << "\n";

    if(conectado == 0) {
        std::cout << "Voce nao esta conectado ou nao se cadastrou!\n";
    }else {
        std::cout << "Voce esta conectado\n";
    }

    std::cout<<"Tudo certo!\n";

return 0;
}