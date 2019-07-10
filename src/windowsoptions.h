#ifndef WINDOWSOPTIONS_H
#define WINDOWSOPTIONS_H

#include <Windows.h>
#include <string>

namespace WindowsOptions
{
    // Operating system
    std::string getComputerName();
    std::string getUserName(); // не реализована
    std::string getWindowsFolder();
    std::string getSystemFolder();
    std::string getLocalTimeAndDate();
    std::string isUserAnAdministrator();

    // User Locale Settings
    unsigned int getCodePage();

    // Hardware
    int getNumberOfProcessors();
}

#endif // WINDOWSOPTIONS_H
