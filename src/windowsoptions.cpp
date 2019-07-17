#include "windowsoptions.h"
#include <Windows.h>
#include <VersionHelpers.h>
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
#include <ShlObj.h>
#include <cmath>
#include <cstdint>
#include <cstdio>

double WindowsOptions::fromBytesToGigabytes(const int64_t bytes)
{
    return bytes / pow(1024, 3);
}

std::string WindowsOptions::getWindowsVersion()
{
    int majorVersion;
    int minorVersion;
    getOSVersion(&majorVersion, &minorVersion, nullptr);

    bool isWindowsServer = IsWindowsServer();
    switch (majorVersion)
    {
    case 5:
        switch (minorVersion)
        {
        case 0:
            return "2000";
        case 1:
            return "XP";
        case 2:
            if (isWindowsServer)
                return "Server 2003/2003 R2";
            else
                return "XP 64-Bit Edition";
        default:
            return "Unknown";
        }
    case 6:
        switch (minorVersion)
        {
        case 0:
            if (isWindowsServer)
                return "Server 2008";
            else
                return "Vista";
        case 1:
            if (isWindowsServer)
                return "Server 2008 R2";
            else
                return "7";
        case 2:
            if (isWindowsServer)
                return "Server 2012";
            else
                return "8";
        case 3:
            if (isWindowsServer)
                return "Server 2012 R2";
            else
                return "8.1";
        default:
            return "Unknown";
        }
    case 10:
        if (isWindowsServer)
            return "Server 2016/2019";
        else
            return "10";
    default:
        return "Unknown";
    }
}

bool WindowsOptions::is64BitSystem()
{
    SYSTEM_INFO info;
    GetNativeSystemInfo(&info);

    return ((info.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_INTEL)? true : false);
}

std::string WindowsOptions::getOSName()
{
    std::string osName = "Microsoft Windows ";
    osName += getWindowsVersion();
    osName += is64BitSystem()? " 64-bit" : " 32-bit";

    return osName;
}

void WindowsOptions::getOSVersion(int *majorVersion, int *minorVersion, int *buildNumber)
{
    NTSTATUS(WINAPI *RtlGetVersion)(LPOSVERSIONINFO);
    *(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");
    if (RtlGetVersion == NULL)
    {
        if (majorVersion != nullptr)
            *majorVersion = 0;
        if (minorVersion != nullptr)
            *minorVersion = 0;
        if (buildNumber  != nullptr)
            *buildNumber  = 0;

        return;
    }

    OSVERSIONINFO osInfo;
    osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    RtlGetVersion(&osInfo);

    if (majorVersion != nullptr)
        *majorVersion = static_cast<int>(osInfo.dwMajorVersion);
    if (minorVersion != nullptr)
        *minorVersion = static_cast<int>(osInfo.dwMinorVersion);
    if (buildNumber  != nullptr)
        *buildNumber  = static_cast<int>(osInfo.dwBuildNumber );
}

std::string WindowsOptions::getComputerName()
{
    DWORD length = 64;
    auto computerName = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), 0, sizeof(CHAR) * length));

    if (!GetComputerNameA(computerName, &length))
        return "Unknown";

    std::string name(computerName);
    HeapFree(GetProcessHeap(), 0, computerName);

    return name;
}

std::string WindowsOptions::getUserName()
{
    DWORD length = 64;
    auto userName = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), 0, sizeof(CHAR) * length));

    if (!GetUserNameA(userName, &length))
        return "Unknown";

    std::string name(userName);
    HeapFree(GetProcessHeap(), 0, userName);

    return name;
}

std::string WindowsOptions::getWindowsFolder()
{
    UINT length = 512;
    auto folderPath = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), 0, sizeof(CHAR) * length));

    if (GetWindowsDirectoryA(folderPath, length) == 0)
        return "Unknown";

    std::string path(folderPath);
    HeapFree(GetProcessHeap(), 0, folderPath);

    return path;
}

std::string WindowsOptions::getSystemFolder()
{
    UINT length = 512;
    auto folderPath = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), 0, sizeof(CHAR) * length));

    if (GetSystemDirectoryA(folderPath, length) == 0)
        return "Unknown";

    std::string path(folderPath);
    HeapFree(GetProcessHeap(), 0, folderPath);

    return path;
}

std::string WindowsOptions::getLocalTime()
{
    SYSTEMTIME localTimeAndDate;
    GetLocalTime(&localTimeAndDate);

    char time[] = "hh:mm:ss";
    sprintf(time, "%d:%02d:%02d", localTimeAndDate.wHour, localTimeAndDate.wMinute, localTimeAndDate.wSecond);

    return time;
}

std::string WindowsOptions::getLocalDate()
{
    SYSTEMTIME localTimeAndDate;
    GetLocalTime(&localTimeAndDate);

    char date[] = "dd.mm.yyyy";
    sprintf(date, "%02d.%02d.%d", localTimeAndDate.wDay, localTimeAndDate.wMonth, localTimeAndDate.wYear);

    return date;
}

bool WindowsOptions::isUserAnAdministrator()
{
    return (IsUserAnAdmin())? true : false;
}

int WindowsOptions::getCodePage()
{
    return static_cast<int>(GetACP());
}

int WindowsOptions::getOEMCodePage()
{
    return static_cast<int>(GetOEMCP());
}

int WindowsOptions::getCountryCode()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];

    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) == 0)
        return 0;

    int countryCode;
    if (GetLocaleInfoEx(localeName,
                        LOCALE_RETURN_NUMBER | LOCALE_IDIALINGCODE,
                        reinterpret_cast<LPWSTR>(&countryCode),
                        sizeof(countryCode)) == 0)
    {
        return 0;
    }

    return static_cast<int>(countryCode);
}

std::wstring WindowsOptions::getCountry()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];

    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) == 0)
        return L"Unknown";

    constexpr int length = 64;
    WCHAR country[length];
    if (GetLocaleInfoEx(localeName, LOCALE_SLOCALIZEDCOUNTRYNAME, country, length) == 0)
        return L"Unknown";

    return country;
}

std::wstring WindowsOptions::getLanguage()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) == 0)
        return L"Unknown";

    constexpr int length = 64;
    WCHAR language[length];
    if (GetLocaleInfoEx(localeName, LOCALE_SLOCALIZEDLANGUAGENAME, language, length) == 0)
        return L"Unknown";

    return language;
}

std::wstring WindowsOptions::getTimeFormat()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) == 0)
        return L"Unknown";

    constexpr int length = 32;
    WCHAR timeFormat[length];
    if (GetLocaleInfoEx(localeName, LOCALE_STIMEFORMAT, timeFormat, length) == 0)
        return L"Unknown";

    return timeFormat;
}

std::wstring WindowsOptions::getDateFormat()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) == 0)
        return L"Unknown";

    constexpr int length = 32;
    WCHAR dateFormat[length];
    if (GetLocaleInfoEx(localeName, LOCALE_SLONGDATE, dateFormat, length) == 0)
        return L"Unknown";

    return dateFormat;
}

std::wstring WindowsOptions::getCurrency()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) == 0)
        return L"Unknown";

    constexpr int length = 8;
    WCHAR currency[length];
    if (GetLocaleInfoEx(localeName, LOCALE_SCURRENCY, currency, length) == 0)
        return L"Unknown";

    return currency;
}

int WindowsOptions::getTimeFormatSpecifier()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) == 0)
        return 0;

    int timeFormat;
    int formatLength = GetLocaleInfoEx(localeName,
                                       LOCALE_RETURN_NUMBER | LOCALE_ITIME,
                                       reinterpret_cast<LPWSTR>(&timeFormat),
                                       sizeof(timeFormat));
    if (formatLength == 0)
        return 0;

    return ((timeFormat == 0)? 12 : 24);
}

int WindowsOptions::getProcessorFamily()
{
    SYSTEM_INFO systemInformation;
    GetSystemInfo(&systemInformation);

    return systemInformation.wProcessorArchitecture;
}

int WindowsOptions::getProcessorModel()
{
    SYSTEM_INFO systemInformation;
    GetSystemInfo(&systemInformation);

    WORD model = systemInformation.wProcessorRevision;
    model >>= 8;

    return model;
}

int WindowsOptions::getProcessorStepping()
{
    SYSTEM_INFO systemInformation;
    GetSystemInfo(&systemInformation);

    WORD stepping = systemInformation.wProcessorRevision & 0b1111'1111;

    return stepping;
}

int WindowsOptions::getNumberOfProcessors()
{
    SYSTEM_INFO systemInformation;
    GetSystemInfo(&systemInformation);

    return static_cast<int>(systemInformation.dwNumberOfProcessors);
}

void WindowsOptions::getPhysicalMemorySize(int64_t *totalSize, int64_t *availableSize)
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (!GlobalMemoryStatusEx(&memoryStatus))
    {
        if (totalSize     != nullptr)
            *totalSize     = 0;
        if (availableSize != nullptr)
            *availableSize = 0;

        return;
    }

    if (totalSize     != nullptr)
        *totalSize     = static_cast<int64_t>(memoryStatus.ullTotalPhys);
    if (availableSize != nullptr)
        *availableSize = static_cast<int64_t>(memoryStatus.ullAvailPhys);
}

void WindowsOptions::getVirtualMemorySize(int64_t *totalSize, int64_t *availableSize)
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (!GlobalMemoryStatusEx(&memoryStatus))
    {
        if (totalSize     != nullptr)
            *totalSize     = 0;
        if (availableSize != nullptr)
            *availableSize = 0;

        return;
    }

    if (totalSize     != nullptr)
        *totalSize     = static_cast<int64_t>(memoryStatus.ullTotalVirtual);
    if (availableSize != nullptr)
        *availableSize = static_cast<int64_t>(memoryStatus.ullAvailVirtual);
}

void WindowsOptions::getPageFileSize(int64_t *totalSize, int64_t *availableSize)
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (!GlobalMemoryStatusEx(&memoryStatus))
    {
        if (totalSize     != nullptr)
            *totalSize     = 0;
        if (availableSize != nullptr)
            *availableSize = 0;

        return;
    }

    if (totalSize     != nullptr)
        *totalSize     = static_cast<int64_t>(memoryStatus.ullTotalPageFile);
    if (availableSize != nullptr)
        *availableSize = static_cast<int64_t>(memoryStatus.ullAvailPageFile);
}

void WindowsOptions::getFullScreenSize(int *width, int *height)
{
    if (width  != nullptr)
        *width  = GetSystemMetrics(SM_CXSCREEN);
    if (height != nullptr)
        *height = GetSystemMetrics(SM_CYSCREEN);
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
    if (diskMask == 0)
        return std::vector<std::string>{};

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
    case DRIVE_REMOVABLE:
        return "REMOVABLE";
    case DRIVE_FIXED:
        return "FIXED";
    case DRIVE_REMOTE:
        return "REMOTE";
    case DRIVE_CDROM:
        return "CD-ROM";
    case DRIVE_RAMDISK:
        return "RAM";
    case DRIVE_UNKNOWN:
    case DRIVE_NO_ROOT_DIR:
    default:
        return "UNKNOWN";
    }
}

void WindowsOptions::getDiskSize(const std::string &diskName, int64_t *totalSize, int64_t *freeSize)
{
    DWORD totalClusters;
    DWORD freeClusters;
    DWORD sectorsPerCluster;
    DWORD bytesPerSector;

    BOOL isSuccess = GetDiskFreeSpaceA(diskName.c_str(),
                                       &sectorsPerCluster,
                                       &bytesPerSector,
                                       &freeClusters,
                                       &totalClusters);
    if (!isSuccess)
    {
        if (totalSize != nullptr)
            *totalSize = 0;
        if (freeSize  != nullptr)
            *freeSize  = 0;

        return;
    }

    if (totalSize != nullptr)
        *totalSize = static_cast<int64_t>(totalClusters) * sectorsPerCluster * bytesPerSector;
    if (freeSize  != nullptr)
        *freeSize  = static_cast<int64_t>(freeClusters)  * sectorsPerCluster * bytesPerSector;
}

std::string WindowsOptions::getDiskFileSystem(const std::string &diskName)
{
    constexpr DWORD length = 64;
    CHAR fileSystemName[length];

    BOOL isSuccess = GetVolumeInformationA(diskName.c_str(),
                                           NULL,
                                           0,
                                           NULL,
                                           NULL,
                                           NULL,
                                           fileSystemName,
                                           length);
    if (!isSuccess)
        return "Unknown";

    return fileSystemName;
}
