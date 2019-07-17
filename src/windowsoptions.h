#ifndef WINDOWSOPTIONS_H
#define WINDOWSOPTIONS_H

#include <string>
#include <vector>

namespace WindowsOptions
{
    double      fromBytesToGigabytes(const int64_t bytes);
    std::string getWindowsVersion();
    bool        is64BitSystem();

    // Operating system
    std::string getOSName();
    void        getOSVersion(int *majorVersion, int *minorVersion, int *buildNumber);
    std::string getComputerName();
    std::string getUserName();
    std::string getWindowsFolder();
    std::string getSystemFolder();
    std::string getLocalTime();
    std::string getLocalDate();
    bool        isUserAnAdministrator();

    // User Locale Settings
    int          getCodePage();
    int          getOEMCodePage();
    int          getCountryCode();
    std::wstring getCountry();
    std::wstring getLanguage();
    std::wstring getTimeFormat();
    std::wstring getDateFormat();
    std::wstring getCurrency();
    int          getTimeFormatSpecifier();

    // Hardware
    int  getProcessorFamily();
    int  getProcessorModel();
    int  getProcessorStepping();
    int  getNumberOfProcessors();
    void getPhysicalMemorySize(int64_t *totalSize, int64_t *avilableSize);
    void getVirtualMemorySize(int64_t *totalSize, int64_t *avilableSize);
    void getPageFileSize(int64_t *totalSize, int64_t *avilableSize);
    void getFullScreenSize(int *width, int *height);
    int  getBitsPerPixel();
    int  getNumberOfMonitors();

    // Disks
    std::vector<std::string> getDisks();
    std::string getDiskType(const std::string &diskName);
    void        getDiskSize(const std::string &diskName, int64_t *totalSize, int64_t *freeSize);
    std::string getDiskFileSystem(const std::string &diskName);
}

#endif // WINDOWSOPTIONS_H
