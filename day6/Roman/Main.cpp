#include <iostream>
#include "NumeralClasses.hpp"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdio>

int main()
{
    #ifdef _WIN32 // Set Console Output to UTF8 (Only on Windows) for the bomb-emote
    // Source: https://stackoverflow.com/a/45622802/14379859
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
    Arabic a;
    std::cout << "Enter a Arabic Number (between 1-399999): \n> ", std::cin >> a, std::cout << (Roman) a << std::endl;
}


