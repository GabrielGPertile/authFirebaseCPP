#pragma once

#include <string>
#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <termios.h>
    #include <unistd.h>
#endif

std::string getHiddenPassword();