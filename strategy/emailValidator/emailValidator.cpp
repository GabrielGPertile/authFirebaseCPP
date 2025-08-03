#include "emailValidator.hpp"

bool isEmailValid(std::string email)
{
    static const std::regex padraoEmail(
        R"(^[a-zA-Z0-9_.+-]+@(gmail\.com|outlook\.com)$)"
    );

    return std::regex_match(email, padraoEmail);
}