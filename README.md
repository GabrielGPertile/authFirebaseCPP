
# FirebaseAuthCPP

Este projeto é um implementação simples no terminal, sobre as principais funcionalidade do serviço de autenticação do firebase, utilizando o provedor de email/senha.


## Demonstração

![Inicial](imagemProjeto/imagem1.jpeg)
![Cadastro](imagemProjeto/imagem2.jpeg)
![Entrar](imagemProjeto/imagem3.jpeg)
![TelaLogado](imagemProjeto/imagem4.jpeg)


## Funcionalidades

- Cadastro de Usuário no firebase utilizando o provedor email/senha
- Login de usuários
- Trocar senha
- Logon

## Stack utilizada

**Linguagem:** C++17

**Build:** CMake, utilizando o tipo de compilação **Release** com todas as bibliotecas linkadas **estaticamente**

**Libs:** Firebase_cpp_sdk, Boost, Dotenv-cpp

O executável gerado é **estático**, ou seja, não depende de DLLs externas para rodar.

## Variáveis de Ambiente

Para rodar esse projeto, você vai precisar adicionar as seguintes variáveis de ambiente no seu .env

`FIREBASE_API_KEY`

`FIREBASE_PROJECT_ID`

`FIREBASE_APP_ID`

