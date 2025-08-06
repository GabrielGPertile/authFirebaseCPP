#pragma once

#include "firebase/app.h"
#include "firebase/auth.h"

void mostrarMenuPrincipal();
void mostrarMenuSecundario();
void inserirOpcao(int *opcao);
void limparTela();

void cadastrarUsuario(firebase::auth::Auth* auth, std::string email, std::string password);
bool loginUsuario(firebase::auth::Auth* auth, std::string email, std::string password);

void mostrarInformacoesProjeto();