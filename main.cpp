#include <iostream>
#include <string>

int main()
{
    std::string email;
    std::string password;

    std::cout << "Digite o seu email:\n";
    std::cin >> email;
    std::cout << "\n";

    std::cout << "Digite a sua senha:\n";
    std::cin >> password;
    std::cout << "\n";

    std::cout<<"Email: " << email << "\n";
    std::cout<<"Senha: " << password << "\n";

    std::cout<<"Tudo certo!\n";

return 0;
}