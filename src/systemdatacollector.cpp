#include "systemdatacollector.h"
#include "windowsoptions.h"
#include "datahandlertohtml.h"
#include <QString>
#include <string>
#include <vector>
#include <cstdint>
#include <cmath>

using namespace WindowsOptions;

void SystemDataCollector::collectData(const QString &outFilePath,
                                      const QString &stylesFilePath,
                                      const QString &scriptsFilePath)
{
    DataHandlerToHTML dataHandler(outFilePath, stylesFilePath, scriptsFilePath);

    collectOperatingSystemData(dataHandler);
    collectUserLocaleSettingsData(dataHandler);
    collectHardwareData(dataHandler);
    collectDisksData(dataHandler);

    dataHandler.endWorkWithFile();
}

void SystemDataCollector::collectOperatingSystemData(DataHandlerToHTML &dataHandler)
{
    dataHandler.beginGroup("Operating System");

    bool is64Bit = is64BitSystem();
    QString formattedString;
    formattedString.sprintf("%s %d-bit", getOSName().c_str(), (is64Bit? 64 : 32));
    dataHandler.addProperty("OS Name", formattedString, true);

    int minorVersion;
    int majorVersion;
    int buildNumber;
    getOSVersion(&minorVersion, &majorVersion, &buildNumber);
    formattedString.sprintf("Version %d.%d Build (%d)", minorVersion, majorVersion, buildNumber);
    dataHandler.addProperty("OS Info", formattedString, true);

    dataHandler.addProperty("Computer Name" , QString::fromStdString(getComputerName() ), true);
    dataHandler.addProperty("User Name"     , QString::fromStdString(getUserName()     ), true);
    dataHandler.addProperty("Windows Folder", QString::fromStdString(getWindowsFolder()), true);
    dataHandler.addProperty("System Folder" , QString::fromStdString(getSystemFolder() ), true);

    formattedString.sprintf("%s %s", getLocalDate().c_str(), getLocalTime().c_str());
    dataHandler.addProperty("Local Time and Date", formattedString, true);

    dataHandler.addProperty("Administrator", (isUserAnAdministrator())? "Yes" : "No", true);

    dataHandler.endGroup();
}

void SystemDataCollector::collectUserLocaleSettingsData(DataHandlerToHTML &dataHandler)
{
    dataHandler.beginGroup("User Locale Settings");

    dataHandler.addProperty("Code Page"    , QString::number(getCodePage()   )       , true);
    dataHandler.addProperty("OEM Code Page", QString::number(getOEMCodePage())       , true);
    dataHandler.addProperty("Country Code" , QString::number(getCountryCode())       , true);
    dataHandler.addProperty("Country"      , QString::fromStdWString(getCountry()   ), true);
    dataHandler.addProperty("Language"     , QString::fromStdWString(getLanguage()  ), true);
    dataHandler.addProperty("Time Format"  , QString::fromStdWString(getTimeFormat()), true);
    dataHandler.addProperty("Date Format"  , QString::fromStdWString(getDateFormat()), true);
    dataHandler.addProperty("Currency"     , QString::fromStdWString(getCurrency()  ), true);

    QString formattedString;
    formattedString.sprintf("%d-hour format", getTimeFormatSpecifier());
    dataHandler.addProperty("Time Format Specifier", formattedString, true);

    dataHandler.endGroup();
}

void SystemDataCollector::collectHardwareData(DataHandlerToHTML &dataHandler)
{
    dataHandler.beginGroup("Hardware");

    dataHandler.addProperty("Processor",            QString::fromStdString(getProcessorName()), true);


    QString formattedString;
    formattedString.sprintf("%d MHz", getProcessorMHzFrequency());
    dataHandler.addProperty("Processor Speed", formattedString, true);

    dataHandler.addProperty("Processor Family"    , QString::number(getProcessorFamily()   )    , true);
    dataHandler.addProperty("Processor Model"     , QString::number(getProcessorModel()    )    , true);
    dataHandler.addProperty("Processor Stepping"  , QString::number(getProcessorStepping() )    , true);
    dataHandler.addProperty("Number of Processors", QString::number(getNumberOfProcessors())    , true);
    dataHandler.addProperty("Bios"                , QString::fromStdString(getBios()           ), true);
    dataHandler.addProperty("Bios Information"    , QString::fromStdString(getBiosInformation()), true);
    dataHandler.addProperty("Bios Date"           , QString::fromStdString(getBiosDate()       ), true);

    int64_t totalPysical;
    int64_t availablePhysical;
    getPhysicalMemorySize(&totalPysical, &availablePhysical);
    formattedString.sprintf("%7.3lf GB", fromBytesToGigabytes(totalPysical)     );
    dataHandler.addProperty("Physical Memory",           formattedString, true);
    formattedString.sprintf("%7.3lf GB", fromBytesToGigabytes(availablePhysical));
    dataHandler.addProperty("Physical Memory Available", formattedString, true);

    int64_t totalVirtual;
    int64_t availableVirtual;
    getVirtualMemorySize(&totalVirtual, &availableVirtual);
    formattedString.sprintf("%7.3lf GB", fromBytesToGigabytes(totalVirtual)    );
    dataHandler.addProperty("Virtual Memory",           formattedString, true);
    formattedString.sprintf("%7.3lf GB", fromBytesToGigabytes(availableVirtual));
    dataHandler.addProperty("Virtual Memory Available", formattedString, true);

    int64_t totalPageFile;
    int64_t availablePageFile;
    getPageFileSize(&totalPageFile, &availablePageFile);
    formattedString.sprintf("%7.3lf GB", fromBytesToGigabytes(totalPageFile)    );
    dataHandler.addProperty("Page File",           formattedString, true);
    formattedString.sprintf("%7.3lf GB", fromBytesToGigabytes(availablePageFile));
    dataHandler.addProperty("Page File Available", formattedString, true);

    int screenWidth;
    int screenHeight;
    getFullScreenSize(&screenWidth, &screenHeight);
    formattedString.sprintf("%dx%d", screenWidth, screenHeight);
    dataHandler.addProperty("Full Screen Size", formattedString, true);

    dataHandler.addProperty("Bit Per Pixel",      QString::number(getBitsPerPixel()    ), true);
    dataHandler.addProperty("Number of Monitors", QString::number(getNumberOfMonitors()), true);

    dataHandler.endGroup();
}

void SystemDataCollector::collectDisksData(DataHandlerToHTML &dataHandler)
{
    dataHandler.beginGroup("Disks");

    std::vector<std::string> diskList = getDisks();
    for (const auto &disk : diskList)
    {
        dataHandler.addProperty("Name", QString::fromStdString(disk)             , false);
        dataHandler.addProperty("Type", QString::fromStdString(getDiskType(disk)), false);

        int64_t totalDiskSize;
        int64_t freeDiskSize;
        getDiskSize(disk, &totalDiskSize, &freeDiskSize);

        QString formattedString;
        formattedString.sprintf("%7.3lf GB", fromBytesToGigabytes(totalDiskSize));
        dataHandler.addProperty("Size"     , formattedString, false);
        formattedString.sprintf("%7.3lf GB", fromBytesToGigabytes(freeDiskSize) );
        dataHandler.addProperty("Free Size", formattedString, false);

        dataHandler.addProperty("File System", QString::fromStdString(getDiskFileSystem(disk)), true);
    }

    dataHandler.endGroup();
}
