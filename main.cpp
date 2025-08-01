#include <iostream>
#include <string>
#include <conio.h>  // getch()
#include <algorithm>

int main()
{
    char ch;

    bool conectado = 0;

    std::string email;
    std::string password;

    std::cout << "Digite o seu email:\n";
    std::cin >> email;
    std::cout << "\n";

    std::cout << "Digite a sua senha:\n";
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