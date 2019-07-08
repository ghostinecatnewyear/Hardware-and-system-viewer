#include "windowsoptions.h"

std::string WindowsOptions::getComputerName()
{
    DWORD nameLength   = 64;
    LPSTR computerName = new CHAR[nameLength];
    GetComputerNameA(computerName, &nameLength);
    std::string name(computerName);
    delete[] computerName;

    return name;
}

std::string WindowsOptions::getWindowsFolder()
{
    UINT  pathLength        = 512;
    LPSTR windowsFolderPath = new CHAR[pathLength];
    GetWindowsDirectoryA(windowsFolderPath, pathLength);
    std::string path(windowsFolderPath);
    delete[] windowsFolderPath;

    return path;
}

std::string WindowsOptions::getSystemFolder()
{
    UINT  pathLength       = 512;
    LPSTR systemFolderPath = new CHAR[pathLength];
    GetSystemDirectoryA(systemFolderPath, pathLength);
    std::string path(systemFolderPath);
    delete[] systemFolderPath;

    return path;
}

int WindowsOptions::getNumberOfProcessors()
{
    SYSTEM_INFO systemInformation;
    GetSystemInfo(&systemInformation);

    return static_cast<int>(systemInformation.dwNumberOfProcessors);
}
