#include "windowsoptions.h"
#include "ShlObj.h"

std::string WindowsOptions::getComputerName()
{
    DWORD nameLength   = 64;
    LPSTR computerName = new CHAR[nameLength];
    GetComputerNameA(computerName, &nameLength);

    std::string name(computerName);
    delete[] computerName;

    return name;
}

std::string WindowsOptions::getUserName() // пока что не работает
{
//    DWORD nameLength   = 64;
//    LPSTR computerName = new CHAR[nameLength];
//    GetUserNameA(computerName, &nameLength);

//    std::string name(computerName);
//    delete[] computerName;

//    return name;

    return std::string("[UNKNOWN]");
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

std::string WindowsOptions::getLocalTimeAndDate()
{
    SYSTEMTIME localTime;
    GetLocalTime(&localTime);

    std::string time;
    time.reserve(19);

    time += (localTime.wDay < 10)? "0" : "";
    time += std::to_string(localTime.wDay);
    time += ".";
    time += (localTime.wMonth < 10)? "0" : "";
    time += std::to_string(localTime.wMonth);
    time += '.';
    time += std::to_string(localTime.wYear);
    time += " ";

    time += std::to_string(localTime.wHour);
    time += ":";
    time += (localTime.wMinute < 10)? "0" : "";
    time += std::to_string(localTime.wMinute);
    time += ":";
    time += (localTime.wSecond < 10)? "0" : "";
    time += std::to_string(localTime.wSecond);

    return time;
}

std::string WindowsOptions::isUserAnAdministrator()
{
    return (IsUserAnAdmin())? "Yes" : "No";
}

unsigned int WindowsOptions::getCodePage()
{
    return GetACP();
}

int WindowsOptions::getNumberOfProcessors()
{
    SYSTEM_INFO systemInformation;
    GetSystemInfo(&systemInformation);

    return static_cast<int>(systemInformation.dwNumberOfProcessors);
}
