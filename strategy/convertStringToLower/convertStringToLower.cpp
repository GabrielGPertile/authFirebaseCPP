#include "convertStringToLower.hpp"

std::string stringToLower(std::string email)
{
    boost::locale::generator gen;

    std::locale loc = gen("pt_BR.UTF-8"); // força regras do português
    
    return boost::locale::to_lower(email, loc); 
}
