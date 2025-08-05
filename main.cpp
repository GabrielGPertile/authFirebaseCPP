#include <iostream>
#include <string>
#define NOMINMAX
#include <limits>

#include "dotenv.h"

#include "strategy/passwordMasked/passwordCinMasked.hpp"
#include "strategy/convertStringToLower/convertStringToLower.hpp"
#include "strategy/emailValidator/emailValidator.hpp"
#include "firebase/app.h"
#include "firebase/auth.h"
#include "firebaseobject.hpp"
#include "main.hpp"

int main()
{  
    // Inicializa o dotenv para carregar as variáveis do arquivo .env
    dotenv::init();

    //variaveis do projeto do firebase
    const char* apiKey = std::getenv("FIREBASE_API_KEY");
    const char* projectID = std::getenv("FIREBASE_PROJECT_ID");
    const char* appID = std::getenv("FIREBASE_APP_ID");

    int opcao = 0;
    bool conectado = 0;

    std::string email;
    std::string password;

    // Verifique se as variáveis estão definidas
    if(!apiKey || !projectID || !appID)
    {
        std::cerr << "Variáveis de ambiente Firebase não definidas!" << std::endl;
        return 1;
    }

    FirebaseObject firebaseObject(
        "apiKey",
        "projectID",
        "appID");

    do{
        mostrarInicialMenu();
        std::cout << "Digite um opcao:\n";

        inserirOpcao(&opcao);
        limparTela();

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

void inserirOpcao(int *opcao)
{
    while(!(std::cin >> *opcao) || *opcao <= -1 || *opcao >= 4){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"Entrada invalida. Digite um valor inteiro maior que -1 e menor que 4:"<<std::endl;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void limparTela()
{
    #ifdef _WIN32
        system("cls");
    #elif defined __APPLE__
        system("clear");
    #elif defined __unix__ || defined __linux__
        system("clear");
    #endif
}