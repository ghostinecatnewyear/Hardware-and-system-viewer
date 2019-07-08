#ifndef WINDOWSOPTIONS_H
#define WINDOWSOPTIONS_H

#include <Windows.h>
#include <string>

/**
 * Библиотека, предоставляющая функции, позволяющие определять
 * характеристики системы.
 */

namespace WindowsOptions
{
    std::string getComputerName();
//    std::string getUserName(); // не реализована
    std::string getWindowsFolder();
    std::string getSystemFolder();
    int getNumberOfProcessors();
}

#endif // WINDOWSOPTIONS_H
