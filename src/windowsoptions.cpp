#include "windowsoptions.h"
#include <Windows.h>
#include <intrin.h>
#include <ShlObj.h>
#include <memory>
#include <cmath>
#include <cstdint>
#include <cstdio>

double WindowsOptions::fromBytesToGigabytes(const int64_t bytes)
{
    return bytes / pow(1024, 3);
}

bool WindowsOptions::is64BitSystem()
{
    SYSTEM_INFO info;

    GetSystemInfo(&info);

    return (info.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_INTEL);
}

std::string WindowsOptions::getOSName()
{
    HKEY key;

    if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                                       "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                                       0,
                                       KEY_QUERY_VALUE | KEY_WOW64_64KEY,
                                       &key))
    {
        return "Unknown";
    }

    DWORD size = 128;
    std::unique_ptr<CHAR> osName(new CHAR[size]);

    if (ERROR_SUCCESS != RegQueryValueExA(key,
                                          "ProductName",
                                          NULL,
                                          NULL,
                                          reinterpret_cast<LPBYTE>(osName.get()),
                                          &size))
    {
        RegCloseKey(key);

        return "Unknown";
    }

    RegCloseKey(key);

    return osName.get();
}

void WindowsOptions::getOSVersion(int *const majorVersion, int *const minorVersion, int *const buildNumber)
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
    std::unique_ptr<CHAR> computerName(new CHAR[length]);

    if (!GetComputerNameA(computerName.get(), &length))
        return "Unknown";

    return computerName.get();
}

std::string WindowsOptions::getUserName()
{
    DWORD length = 64;
    std::unique_ptr<CHAR> userName(new CHAR[length]);

    if (!GetUserNameA(userName.get(), &length))
        return "Unknown";

    return userName.get();
}

std::string WindowsOptions::getWindowsFolder()
{
    UINT length = 512;
    std::unique_ptr<CHAR> folderPath(new CHAR[length]);

    if (0 == GetWindowsDirectoryA(folderPath.get(), length))
        return "Unknown";

    return folderPath.get();
}

std::string WindowsOptions::getSystemFolder()
{
    UINT length = 512;
    std::unique_ptr<CHAR> folderPath(new CHAR[length]);

    if (0 == GetSystemDirectoryA(folderPath.get(), length))
        return "Unknown";

    return folderPath.get();
}

//std::string WindowsOptions::getDomainName()
//{
//    HKEY key;

//    if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_LOCAL_MACHINE,
//                                       "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters",
//                                       0,
//                                       KEY_QUERY_VALUE | KEY_WOW64_64KEY,
//                                       &key))
//    {
//        return "Unknown";
//    }

//    DWORD size = 64;
//    std::unique_ptr<CHAR> domainName(new CHAR[size]);

//    if (ERROR_SUCCESS != RegQueryValueExA(key,
//                                          "Domain",
//                                          NULL,
//                                          NULL,
//                                          reinterpret_cast<LPBYTE>(domainName.get()),
//                                          &size))
//    {
//        RegCloseKey(key);

//        return "Unknown";
//    }

//    if (domainName.get()[0] != '\0')
//    {
//        RegCloseKey(key);

//        return domainName.get();
//    }

//    LSTATUS result;
//    result = RegQueryValueExA(key,
//                              "HostName",
//                              NULL,
//                              NULL,
//                              reinterpret_cast<LPBYTE>(domainName.get()),
//                              &size);
//    if (result != ERROR_SUCCESS && result != ERROR_MORE_DATA)
//    {
//        RegCloseKey(key);

//        return "Unknown";
//    }

//    RegCloseKey(key);

//    return domainName.get();
//}

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
    return IsUserAnAdmin();
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

    if (0 == GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
        return 0;

    int countryCode;
    if (0 == GetLocaleInfoEx(localeName,
                             LOCALE_RETURN_NUMBER | LOCALE_IDIALINGCODE,
                             reinterpret_cast<LPWSTR>(&countryCode),
                             sizeof(countryCode)))
    {
        return 0;
    }

    return static_cast<int>(countryCode);
}

std::wstring WindowsOptions::getCountry()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];

    if (0 == GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
        return L"Unknown";

    constexpr int length = 64;
    WCHAR country[length];
    if (0 == GetLocaleInfoEx(localeName, LOCALE_SLOCALIZEDCOUNTRYNAME, country, length))
        return L"Unknown";

    return country;
}

std::wstring WindowsOptions::getLanguage()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (0 == GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
        return L"Unknown";

    constexpr int length = 64;
    WCHAR language[length];
    if (0 == GetLocaleInfoEx(localeName, LOCALE_SLOCALIZEDLANGUAGENAME, language, length))
        return L"Unknown";

    return language;
}

std::wstring WindowsOptions::getTimeFormat()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (0 == GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
        return L"Unknown";

    constexpr int length = 32;
    WCHAR timeFormat[length];
    if (0 == GetLocaleInfoEx(localeName, LOCALE_STIMEFORMAT, timeFormat, length))
        return L"Unknown";

    return timeFormat;
}

std::wstring WindowsOptions::getDateFormat()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (0 == GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
        return L"Unknown";

    constexpr int length = 32;
    WCHAR dateFormat[length];
    if (0 == GetLocaleInfoEx(localeName, LOCALE_SLONGDATE, dateFormat, length))
        return L"Unknown";

    return dateFormat;
}

std::wstring WindowsOptions::getCurrency()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (0 == GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
        return L"Unknown";

    constexpr int length = 8;
    WCHAR currency[length];
    if (0 == GetLocaleInfoEx(localeName, LOCALE_SCURRENCY, currency, length))
        return L"Unknown";

    return currency;
}

int WindowsOptions::getTimeFormatSpecifier()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    if (0 == GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
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

std::string WindowsOptions::getProcessorName()
{
    HKEY key;

    if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                                       "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                                       0,
                                       KEY_QUERY_VALUE | KEY_WOW64_64KEY,
                                       &key))
    {
        return "Unknown";
    }

    DWORD size = 128;
    std::unique_ptr<CHAR> processorName(new CHAR[size]);

    if (ERROR_SUCCESS != RegQueryValueExA(key,
                                          "ProcessorNameString",
                                          NULL,
                                          NULL,
                                          reinterpret_cast<LPBYTE>(processorName.get()),
                                          &size))
    {
        RegCloseKey(key);

        return "Unknown";
    }

    RegCloseKey(key);

    return processorName.get();
}

int WindowsOptions::getProcessorMHzFrequency()
{
    HKEY key;

    if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                                       "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                                       0,
                                       KEY_QUERY_VALUE | KEY_WOW64_64KEY,
                                       &key))
    {
        return 0;
    }

    DWORD size = sizeof(DWORD);
    std::unique_ptr<DWORD> processorSpeed(new DWORD);

    if (ERROR_SUCCESS != RegQueryValueExA(key,
                                          "~MHz",
                                          NULL,
                                          NULL,
                                          reinterpret_cast<LPBYTE>(processorSpeed.get()),
                                          &size))
    {
        RegCloseKey(key);

        return 0;
    }

    RegCloseKey(key);

    return static_cast<int>(*processorSpeed);
}

int WindowsOptions::getProcessorFamily()
{
    SYSTEM_INFO systemInformation;
    GetSystemInfo(&systemInformation);

    return systemInformation.wProcessorLevel;
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

std::string WindowsOptions::getBios()
{
    HKEY key;

    if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                                       "HARDWARE\\DESCRIPTION\\System\\BIOS",
                                       0,
                                       KEY_QUERY_VALUE | KEY_WOW64_64KEY,
                                       &key))
    {
        return "Unknown";
    }

    DWORD size = 128;
    std::unique_ptr<CHAR> bios(new CHAR[size]);

    if (ERROR_SUCCESS != RegQueryValueExA(key,
                                          "BIOSVersion",
                                          NULL,
                                          NULL,
                                          reinterpret_cast<LPBYTE>(bios.get()),
                                          &size))
    {
        RegCloseKey(key);

        return "Unknown";
    }

    RegCloseKey(key);

    return bios.get();
}

std::string WindowsOptions::getBiosInformation()
{
    HKEY key;

    if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                                       "HARDWARE\\DESCRIPTION\\System",
                                       0,
                                       KEY_QUERY_VALUE | KEY_WOW64_64KEY,
                                       &key))
    {
        return "Unknown";
    }

    DWORD size = 128;
    std::unique_ptr<CHAR> biosInfo(new CHAR[size]);

    if (ERROR_SUCCESS != RegQueryValueExA(key,
                                          "SystemBiosVersion",
                                          NULL,
                                          NULL,
                                          reinterpret_cast<LPBYTE>(biosInfo.get()),
                                          &size))
    {
        RegCloseKey(key);

        return "Unknown";
    }

    RegCloseKey(key);

    return biosInfo.get();
}

std::string WindowsOptions::getBiosDate()
{
    HKEY key;

    if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                                       "HARDWARE\\DESCRIPTION\\System\\BIOS",
                                       0,
                                       KEY_QUERY_VALUE | KEY_WOW64_64KEY,
                                       &key))
    {
        return "Unknown";
    }

    DWORD size = 128;
    std::unique_ptr<CHAR> biosDate(new CHAR[size]);

    if (ERROR_SUCCESS != RegQueryValueExA(key,
                                          "BIOSReleaseDate",
                                          NULL,
                                          NULL,
                                          reinterpret_cast<LPBYTE>(biosDate.get()),
                                          &size))
    {
        RegCloseKey(key);

        return "Unknown";
    }

    RegCloseKey(key);

    return biosDate.get();
}

void WindowsOptions::getPhysicalMemorySize(int64_t *const totalSize, int64_t *const availableSize)
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);

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

void WindowsOptions::getVirtualMemorySize(int64_t *const totalSize, int64_t *const availableSize)
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);

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

void WindowsOptions::getPageFileSize(int64_t *const totalSize, int64_t *const availableSize)
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);

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

void WindowsOptions::getFullScreenSize(int *const width, int *const height)
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

void WindowsOptions::getDiskSize(const std::string &diskName, int64_t *const totalSize, int64_t *const freeSize)
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
