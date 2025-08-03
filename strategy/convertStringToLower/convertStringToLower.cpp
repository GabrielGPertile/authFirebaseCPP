#include "convertStringToLower.hpp"

std::string stringToLower(std::string email)
{
    std::transform(email.begin(), email.end(), email.begin(),
        [](unsigned char c) { return std::tolower(c); });

    return email;
}
