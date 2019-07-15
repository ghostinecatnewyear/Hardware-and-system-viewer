#include "systemdatacollector.h"
#include "windowsoptions.h"
#include "datahandlertohtml.h"
#include <QString>
#include <array>
#include <cstdint>

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

    dataHandler.addProperty("Computer Name",  QString::fromStdString(getComputerName() ), true);
    dataHandler.addProperty("User Name",      QString::fromStdString(getUserName()     ), true);
    dataHandler.addProperty("Windows Folder", QString::fromStdString(getWindowsFolder()), true);
    dataHandler.addProperty("System Folder",  QString::fromStdString(getSystemFolder() ), true);

    dataHandler.addProperty("Local Time and Date",
                            QString::fromStdString(getLocalDate() + " " + getLocalTime()),
                            true);

    dataHandler.addProperty("Administrator", (isUserAnAdministrator())? "Yes" : "No", true);

    dataHandler.endGroup();
}

void SystemDataCollector::collectUserLocaleSettingsData(DataHandlerToHTML &dataHandler)
{
    dataHandler.beginGroup("User Locale Settings");

    dataHandler.addProperty("Code Page",     QString::number(getCodePage()   ), true);
    dataHandler.addProperty("OEM Code Page", QString::number(getOEMCodePage()), true);

    dataHandler.endGroup();
}

void SystemDataCollector::collectHardwareData(DataHandlerToHTML &dataHandler)
{
    dataHandler.beginGroup("Hardware");

    dataHandler.addProperty("Processor Family",     QString::number(getProcessorFamily()   ), true);
    dataHandler.addProperty("Processor Model",      QString::number(getProcessorModel()    ), true);
    dataHandler.addProperty("Processor Stepping",   QString::number(getProcessorStepping() ), true);
    dataHandler.addProperty("Number of Processors", QString::number(getNumberOfProcessors()), true);

    int64_t totalPysical;
    int64_t availablePhysical;
    getPhysicalMemorySize(totalPysical, availablePhysical);
    dataHandler.addProperty("Physical Memory",
                            QString::number(fromBytesToGigabytes(totalPysical)) + " GB",
                            true);
    dataHandler.addProperty("Physical Memory Available",
                            QString::number(fromBytesToGigabytes(availablePhysical)) + " GB",
                            true);

    int64_t totalVirtual;
    int64_t availableVirtual;
    getVirtualMemorySize(totalVirtual, availableVirtual);
    dataHandler.addProperty("Virtual Memory",
                            QString::number(fromBytesToGigabytes(totalVirtual)) + " GB",
                            true);
    dataHandler.addProperty("Virtual Memory Available",
                            QString::number(fromBytesToGigabytes(availableVirtual)) + " GB",
                            true);

    int64_t totalPageFile;
    int64_t availablePageFile;
    getPageFileSize(totalPageFile, availablePageFile);
    dataHandler.addProperty("Page File",
                            QString::number(fromBytesToGigabytes(totalPageFile)) + " GB",
                            true);
    dataHandler.addProperty("Page File Available",
                            QString::number(fromBytesToGigabytes(availablePageFile)) + " GB",
                            true);

    int screenWidth;
    int screenHeight;
    getFullScreenSize(screenWidth, screenHeight);
    dataHandler.addProperty("Full Screen Size",
                            QString::number(screenWidth) + "x" + QString::number(screenHeight),
                            true);
    dataHandler.addProperty("Bit Per Pixel",
                            QString::number(getBitsPerPixel()),
                            true);
    dataHandler.addProperty("Number of Monitors",
                            QString::number(getNumberOfMonitors()),
                            true);

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
        getDiskSize(disk, totalDiskSize, freeDiskSize);
        dataHandler.addProperty("Size",
                                QString::number(fromBytesToGigabytes(totalDiskSize)) + " GB",
                                false);
        dataHandler.addProperty("Free Size",
                                QString::number(fromBytesToGigabytes(freeDiskSize))  + " GB",
                                false);
        dataHandler.addProperty("File System",
                                QString::fromStdString(getDiskFileSystem(disk)),
                                true);
    }

    dataHandler.endGroup();
}
