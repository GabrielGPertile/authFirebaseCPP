#include <iostream>
#include <string>
#include <limits>

#include "strategy/passwordMasked/passwordCinMasked.hpp"
#include "strategy/convertStringToLower/convertStringToLower.hpp"
#include "strategy/emailValidator/emailValidator.hpp"
#include "main.hpp"

int main()
{
    char ch;

    bool conectado = 0;

    std::string email;
    std::string password;

    do{
        mostrarInicialMenu();
        std::cout << "Digite um opcao:\n";

        inserirOpcao(&opcao);

        switch (opcao)
        {
            case 1:
                /* code */
            break;
            
            case 0:
                return 1;
            break;

            default:
            break;
        }

    }while(opcao != 0);

    std::cout << "Digite o seu email:\n";
    std::cin >> email;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    email = stringToLower(email);

    if(!isEmailValid(email))
    {
        std::cout << "Email inválido.\n";

        return 1;
    }


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

void mostrarInicialMenu()
{
    std::cout << "";
    std::cout << "1 - Cadastrar-se\n";
    std::cout << "2 - Entrar\n";
    std::cout << "0 - Sair\n";
}