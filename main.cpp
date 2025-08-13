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
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif


    // Inicializa o dotenv para carregar as variáveis do arquivo .env
    dotenv::init();

    //variaveis do projeto do firebase
    const char* apiKey = std::getenv("FIREBASE_API_KEY");
    const char* projectID = std::getenv("FIREBASE_PROJECT_ID");
    const char* appID = std::getenv("FIREBASE_APP_ID");

    int opcaoPrincipal = 0;
    int opcaoMenuLogado = 0;
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

                if(!conectado) {
                    std::cout << "Voce não esta conectado!";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    limparTela();
                    break;
                }

                do {
                    
                mostrarMenuSecundario();
                std::cout << "Digite um opção:\n";
                
                inserirOpcao(&opcaoMenuLogado);
                limparTela();

                switch (opcaoMenuLogado)
                {
                    case 1:
                        mostrarInformacoesProjeto();

                        std::cin.get();

                        limparTela();
                    break;

                    case 2 :
                    {
                        mostrarInformacoesPessoal(auth, &conectado);
                        std::cin.get();
                        limparTela();
                    }
                    break;

                    case 3 :
                        trocarSenha(auth);
                        std::cin.get();
                        limparTela();
                    break;

                    case 0:
                        auth->SignOut();
                    break;
                    
                    default:
                    break;
                }

                }while(opcaoMenuLogado != 0);

                break;
            }
            
            case 0:
                return 1;
            break;

            default:
            break;
        }

    }while(opcaoPrincipal != 0);

    std::cout << "Obrigado por usar nosso programa! Volte sempre!\n";
return 0;
}

void mostrarMenuPrincipal()
{
    std::cout << "";
    std::cout << "1 - Cadastrar-se\n";
    std::cout << "2 - Entrar\n";
    std::cout << "0 - Sair\n";
}

void mostrarMenuSecundario()
{
    std::cout << "1 - Informações do projeto\n";
    std::cout << "2 - Suas informações\n";
    std::cout << "3 - Trocar de senha\n";
    std::cout << "0 - Deslogar\n";
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

void mostrarInformacoesProjeto()
{
    std::cout << "Este projeto tem como finalidade criar, logar, trocar senha e deslogar,\n";
    std::cout << "usando o serviço de autenticação do Firebase com email e senha.\n";
    std::cout << "É um projeto simples, feito para aplicar o que foi aprendido\n";
    std::cout << "e depois criar um site web usando o Drogon.\n";
}

void mostrarInformacoesPessoal(firebase::auth::Auth* auth,  bool* conectado)
{
    if(auth->current_user().is_valid())
    {
        std::cout << "Seu email: " << auth->current_user().email() << "\n";
    }
    
    if(*conectado == true)
    {
        std::cout << "Você está conectado!\n";
    }
}

void trocarSenha(firebase::auth::Auth *auth)
{
    firebase::auth::User user = auth->current_user();

    std::string newPassword;
    std::string password;

    if(!user.is_valid())
    {
        std::cout << "Nenhum usuário logado. Faça login primeiro.\n";
        return;
    }

    std::cout << "Digite a sua senha atual: ";
    password = getHiddenPassword();
    std::cout << "\n";

    std::cout << "Digite a sua nova senha: ";
    newPassword = getHiddenPassword();
    std::cout << "\n";

    firebase::auth::Credential cred = firebase::auth::EmailAuthProvider::GetCredential(user.email().c_str(), password.c_str());

    std::cout << "Reautenticando...\n";
    firebase::Future<void> reauth = user.Reauthenticate(cred);

    while (reauth.status() == firebase::kFutureStatusPending) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (reauth.error() == firebase::auth::kAuthErrorNone)
    {
        std::cout << "Reautenticação bem-sucedida! Alterando senha...\n";

        firebase::Future<void> atualizarSenha = user.UpdatePassword(newPassword.c_str());

        while (atualizarSenha.status() == firebase::kFutureStatusPending) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (atualizarSenha.error() == firebase::auth::kAuthErrorNone)
        {
            std::cout << "Senha alterada com sucesso!\n";
        }
        else
        {
            std::cerr << "Erro ao alterar a senha: " << atualizarSenha.error_message()
                    << " (" << atualizarSenha.error() << ")\n";
        }
    }
    else
    {
        std::cerr << "Erro na reautenticação: " << reauth.error_message()
                << " (" << reauth.error() << ")\n";
    }
}