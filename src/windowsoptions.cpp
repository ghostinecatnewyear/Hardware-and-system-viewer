#include "windowsoptions.h"
#include <cmath>
#include <cstdint>
#include <Windows.h>
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
#include <ShlObj.h>

double WindowsOptions::fromBytesToGigabytes(const int64_t bytes)
{
    return bytes / pow(1024, 3);
}

std::string WindowsOptions::getComputerName()
{
    DWORD nameLength   = 64;
    auto  computerName = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), 0, sizeof(CHAR) * nameLength));

    if (!GetComputerNameA(computerName, &nameLength))
        return "Unknown";

    std::string name(computerName);
    HeapFree(GetProcessHeap(), 0, computerName);

    return name;
}

std::string WindowsOptions::getUserName()
{
    DWORD nameLength = 64;
    auto  userName   = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), 0, sizeof(CHAR) * nameLength));

    if (!GetUserNameA(userName, &nameLength))
        return "Unknown";

    std::string name(userName);
    HeapFree(GetProcessHeap(), 0, userName);

    return name;
}

std::string WindowsOptions::getWindowsFolder()
{
    UINT  pathLength = 512;
    auto  folderPath = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), 0, sizeof(CHAR) * pathLength));

    if (GetWindowsDirectoryA(folderPath, pathLength) == 0)
        return "Unknown";

    std::string path(folderPath);
    HeapFree(GetProcessHeap(), 0, folderPath);

    return path;
}

std::string WindowsOptions::getSystemFolder()
{
    UINT  pathLength = 512;
    auto  folderPath = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), 0, sizeof(CHAR) * pathLength));

    if (GetSystemDirectoryA(folderPath, pathLength) == 0)
        return "Unknown";

    std::string path(folderPath);
    HeapFree(GetProcessHeap(), 0, folderPath);

    return path;
}

std::string WindowsOptions::getLocalTime()
{
    SYSTEMTIME localTime;
    GetLocalTime(&localTime);

    std::string time;
    time.reserve(WindowsOptions::timeStringLength);

    time += std::to_string(localTime.wHour);
    time += ":";
    time += (localTime.wMinute < 10)? "0" : "";
    time += std::to_string(localTime.wMinute);
    time += ":";
    time += (localTime.wSecond < 10)? "0" : "";
    time += std::to_string(localTime.wSecond);

    return time;
}

std::string WindowsOptions::getLocalDate()
{
    SYSTEMTIME localTime;
    GetLocalTime(&localTime);

    std::string date;
    date.reserve(WindowsOptions::dateStringLength);

    date += (localTime.wDay < 10)? "0" : "";
    date += std::to_string(localTime.wDay);
    date += ".";
    date += (localTime.wMonth < 10)? "0" : "";
    date += std::to_string(localTime.wMonth);
    date += ".";
    date += std::to_string(localTime.wYear);

    return date;
}

bool WindowsOptions::isUserAnAdministrator()
{
    return (IsUserAnAdmin())? true : false;
}

unsigned int WindowsOptions::getCodePage()
{
    return GetACP();
}

unsigned long WindowsOptions::getNumberOfProcessors()
{
    SYSTEM_INFO systemInformation;
    GetSystemInfo(&systemInformation);

    return systemInformation.dwNumberOfProcessors;
}

void WindowsOptions::getPhysicalMemorySize(int64_t &totalSize, int64_t &availableSize)
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (!GlobalMemoryStatusEx(&memoryStatus))
    {
        totalSize     = 0;
        availableSize = 0;

        return;
    }

    totalSize     = static_cast<int64_t>(memoryStatus.ullTotalPhys);
    availableSize = static_cast<int64_t>(memoryStatus.ullAvailPhys);
}

void WindowsOptions::getVirtualMemorySize(int64_t &totalSize, int64_t &availableSize)
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (!GlobalMemoryStatusEx(&memoryStatus))
    {
        totalSize     = 0;
        availableSize = 0;

        return;
    }

    totalSize     = static_cast<int64_t>(memoryStatus.ullTotalVirtual);
    availableSize = static_cast<int64_t>(memoryStatus.ullAvailVirtual);
}

void WindowsOptions::getPageFileSize(int64_t &totalSize, int64_t &availableSize)
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (!GlobalMemoryStatusEx(&memoryStatus))
    {
        totalSize     = 0;
        availableSize = 0;

        return;
    }

    totalSize     = static_cast<int64_t>(memoryStatus.ullTotalPageFile);
    availableSize = static_cast<int64_t>(memoryStatus.ullAvailPageFile);
}

void WindowsOptions::getFullScreenSize(int &width, int &height)
{
    width  = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
}

int WindowsOptions::getBitsPerPixel()
{
    HDC screenContext = GetDC(NULL);

    if (!screenContext)
        return 0;

    return GetDeviceCaps(screenContext, BITSPIXEL);
}

int WindowsOptions::getNumberOfMonitors()
{
    return GetSystemMetrics(SM_CMONITORS);
}

std::vector<std::string> WindowsOptions::getDisks()
{
    DWORD diskMask = GetLogicalDrives();
    const int maskSize = sizeof(DWORD) * 8;
    constexpr int characterACode = 65;
    std::string diskName = "X:\\";
    std::vector<std::string> diskList;
    diskList.reserve(8);

    for (int i = 0; i < maskSize; ++i)
    {
        if (diskMask & 1)
        {
            diskName[0] = static_cast<char>(characterACode + i);
            diskList.push_back(diskName);
        }
        diskMask >>= 1;
    }

    return diskList;
}

std::string WindowsOptions::getDiskType(const std::string &diskName)
{
    UINT driveType = GetDriveTypeA(diskName.c_str());

    switch (driveType)
    {
    case 2:
        return "REMOVABLE";
    case 3:
        return "FIXED";
    case 4:
        return "REMOTE";
    case 5:
        return "CD-ROM";
    case 6:
        return "RAM";
    case 0:
    case 1:
    default:
        return "UNKNOWN";
    }
}

void WindowsOptions::getDiskSize(const std::string &diskName,
                                 int64_t &totalSize,
                                 int64_t &freeSize)
{
    DWORD totalClusters;
    DWORD freeClusters;
    DWORD sectorsPerCluster;
    DWORD bytesPerSector;

    BOOL result = GetDiskFreeSpaceA(diskName.c_str(),
                                    &sectorsPerCluster,
                                    &bytesPerSector,
                                    &freeClusters,
                                    &totalClusters);
    if (!result)
    {
        totalSize = 0;
        freeSize  = 0;

        return;
    }

    totalSize = static_cast<int64_t>(totalClusters) * sectorsPerCluster * bytesPerSector;
    freeSize  = static_cast<int64_t>(freeClusters ) * sectorsPerCluster * bytesPerSector;
}

std::string WindowsOptions::getDiskFileSystem(const std::string &diskName)
{
    DWORD fileSystemNameLength = 64;
    auto  fileSystemName = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), 0, sizeof(CHAR) * fileSystemNameLength));

    BOOL result = GetVolumeInformationA(diskName.c_str(),
                                        NULL,
                                        0,
                                        NULL,
                                        NULL,
                                        NULL,
                                        fileSystemName,
                                        fileSystemNameLength);
    if (!result)
        return "Unknown";

    std::string name(fileSystemName);
    HeapFree(GetProcessHeap(), 0, fileSystemName);

    return name;
}
