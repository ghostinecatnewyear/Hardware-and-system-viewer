#ifndef WINDOWSOPTIONS_H
#define WINDOWSOPTIONS_H

#include <string>
#include <vector>

namespace WindowsOptions
{
    constexpr int timeStringLength = 8;
    constexpr int dateStringLength = 10;

    double fromBytesToGigabytes(const int64_t bytes);

    // Operating system
    std::string getComputerName();
    std::string getUserName();
    std::string getWindowsFolder();
    std::string getSystemFolder();
    std::string getLocalTime();
    std::string getLocalDate();
    bool        isUserAnAdministrator();

    // User Locale Settings
    unsigned int getCodePage();

    // Hardware
    unsigned long getNumberOfProcessors();
    void          getPhysicalMemorySize(int64_t &totalSize, int64_t &avilableSize);
    void          getVirtualMemorySize(int64_t &totalSize, int64_t &avilableSize);
    void          getPageFileSize(int64_t &totalSize, int64_t &avilableSize);
    void          getFullScreenSize(int &width, int &height);
    int           getBitsPerPixel();
    int           getNumberOfMonitors();

    // Disks
    std::vector<std::string> getDisks();
    std::string              getDiskType(const std::string &diskName);
    void                     getDiskSize(const std::string &diskName,
                                         int64_t &totalSize,
                                         int64_t &freeSize);
    std::string getDiskFileSystem(const std::string &diskName);
}

#endif // WINDOWSOPTIONS_H
