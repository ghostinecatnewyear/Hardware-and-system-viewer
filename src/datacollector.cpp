#include "datacollector.h"
#include "windowsoptions.h"
#include "datahandler.h"

using namespace WindowsOptions;

void DataCollector::collectData(const QString &outFilePath,
                                const QString &stylesFilePath,
                                const QString &scriptsFilePath)
{
    DataHandler dataHandler(outFilePath, stylesFilePath, scriptsFilePath);

    std::vector<Property> properties;
    constexpr int maximumPropertiesInGroup = 18;
    properties.reserve(maximumPropertiesInGroup);

    properties.push_back(Property("Computer Name",       QString::fromStdString(getComputerName()      )));
    properties.push_back(Property("User Name",           QString::fromStdString(getUserName()          )));
    properties.push_back(Property("Windows Folder",      QString::fromStdString(getWindowsFolder()     )));
    properties.push_back(Property("System Folder",       QString::fromStdString(getSystemFolder()      )));
    properties.push_back(Property("Local Time and Date", QString::fromStdString(getLocalTimeAndDate()  )));
    properties.push_back(Property("Administrator",       QString::fromStdString(isUserAnAdministrator())));
    dataHandler.addGroup("Operating System", properties);

    properties.clear();
    properties.push_back(Property("Code Page", QString::number(getCodePage())));
    dataHandler.addGroup("User Locale Settings", properties);

    properties.clear();
    properties.push_back(Property("Number of Processors", QString::number(getNumberOfProcessors())));
    dataHandler.addGroup("Hardware", properties);

    dataHandler.endWorkWithFile();
}
