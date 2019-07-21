#ifndef WINDOWSOPTIONS_H
#define WINDOWSOPTIONS_H

#include <string>
#include <vector>

namespace WindowsOptions
{
    double fromBytesToGigabytes(const int64_t bytes);
    bool   is64BitSystem();

    // Operating system
    std::string getOSName();
    void        getOSVersion(int *const majorVersion, int *const minorVersion, int *const buildNumber);
    std::string getComputerName();
    std::string getUserName();
    std::string getWindowsFolder();
    std::string getSystemFolder();
    std::string getDomainName(); // не реализована
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
    std::string getProcessorName();
    int         getProcessorMHzFrequency();
    int         getProcessorFamily();
    int         getProcessorModel();
    int         getProcessorStepping();
    int         getNumberOfProcessors();
    std::string getBios();
    std::string getBiosInformation();
    std::string getBiosDate();
    void        getPhysicalMemorySize(int64_t *const totalSize, int64_t *const avilableSize);
    void        getVirtualMemorySize(int64_t *const totalSize, int64_t *const avilableSize);
    void        getPageFileSize(int64_t *const totalSize, int64_t *const avilableSize);
    void        getFullScreenSize(int *const width, int *const height);
    int         getBitsPerPixel();
    int         getNumberOfMonitors();

    // Disks
    std::vector<std::string> getDisks();
    std::string              getDiskType(const std::string &diskName);
    void                     getDiskSize(const std::string &diskName, int64_t *const totalSize,
                                                                      int64_t *const freeSize);
    std::string              getDiskFileSystem(const std::string &diskName);
}

#endif // WINDOWSOPTIONS_H
