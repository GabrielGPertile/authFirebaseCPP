#include <iostream>
#include <string>
#define NOMINMAX
#include <limits>
#include <thread>
#include <chrono>

#include "dotenv.h"

#include "strategy/passwordMasked/passwordCinMasked.hpp"
#include "strategy/convertStringToLower/convertStringToLower.hpp"
#include "strategy/emailValidator/emailValidator.hpp"
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

    int opcaoPrincipal = 0;
    bool conectado = false;

    std::string email;
    std::string password;

    // Verifique se as variáveis estão definidas
    if(!apiKey || !projectID || !appID)
    {
        std::cerr << "Variáveis de ambiente Firebase não definidas!" << std::endl;
        return 1;
    }

    FirebaseObject firebaseObject(
        apiKey,
        projectID,
        appID);


    firebase::AppOptions app_options;
    app_options.set_api_key(firebaseObject.getApiKey().c_str());
    app_options.set_project_id(firebaseObject.getProjectID().c_str());
    app_options.set_app_id(firebaseObject.getAppID().c_str());

    firebase::App* app = firebase::App::Create(app_options);
    firebase::auth::Auth* auth = firebase::auth::Auth::GetAuth(app);

    do{
        mostrarMenuPrincipal();
        std::cout << "Digite um opcao:\n";

        inserirOpcao(&opcaoPrincipal);
        limparTela();

        switch (opcaoPrincipal)
        {
            case 1:
            {
                cadastrarUsuario(auth, email, password);

                std::this_thread::sleep_for(std::chrono::seconds(2));

                limparTela();
                
                break;
            }

            case 2:
            {   
                conectado = loginUsuario(auth, email, password);

                std::this_thread::sleep_for(std::chrono::seconds(2));

                limparTela();

                break;
            }
            
            case 0:
                return 1;
            break;

            default:
            break;
        }

    }while(opcaoPrincipal != 0);

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

void mostrarMenuPrincipal()
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

void cadastrarUsuario(firebase::auth::Auth *auth, std::string email, std::string password)
{
    std::cout << "\t\tCadastro!\n";
                
    std::cout << "Email:";
    std::cin >> email;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    email = stringToLower(email);


    if (!isEmailValid(email))
    {
        std::cout << "Email inválido.\n";
        return;
    }

    std::cout << "Senha:";
    password = getHiddenPassword();
    std::cout << "\n";

    // Cria usuário no Firebase
    auto result = auth->CreateUserWithEmailAndPassword(email.c_str(), password.c_str());

    while(result.status() == firebase::kFutureStatusPending)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if(result.error() == 0)
    {
        std::cout << "Usuário criado com sucesso!\n";
    }
    else 
    {
        std::cout << "Erro ao criar usuário: " << result.error_message() << "\n";
    }

}

bool loginUsuario(firebase::auth::Auth *auth, std::string email, std::string password)
{
    std::cout << "\t\tEntrar!\n";
                
    std::cout << "Email:";
    std::cin >> email;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    email = stringToLower(email);

    if (!isEmailValid(email))
    {
        std::cout << "Email inválido.\n";
        return false;
    }

    std::cout << "Senha:";
    password = getHiddenPassword();
    std::cout << "\n";

    firebase::Future<firebase::auth::AuthResult> login = auth->SignInWithEmailAndPassword(email.c_str(), password.c_str());

    // Aguarda o login
    while(login.status() == firebase::kFutureStatusPending) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (login.status() == firebase::kFutureStatusComplete && login.error() == firebase::auth::kAuthErrorNone) {
        std::cout << "Conectado com sucesso!\n";
        auto* auth_result = login.result();
        if (auth_result != nullptr) {
            std::cout << "Usuário autenticado: " << auth_result->user.email() << "\n";
        }
        return true;
    } else {
        std::cerr << "Falha na autenticação: " << login.error_message() << "\n";
        return false;
    }
}
