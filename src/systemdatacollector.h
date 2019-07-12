#ifndef SYSTEMDATACOLLECTOR_H
#define SYSTEMDATACOLLECTOR_H

class QString;
class DataHandlerToHTML;

class SystemDataCollector
{
    SystemDataCollector() = delete;

public:
    static void collectData(const QString &outFilePath,
                            const QString &stylesFilePath,
                            const QString &scriptsFilePath);

private:
    static void collectOperatingSystemData(DataHandlerToHTML &dataHandler);
    static void collectUserLocaleSettingsData(DataHandlerToHTML &dataHandler);
    static void collectHardwareData(DataHandlerToHTML &dataHandler);
    static void collectDisksData(DataHandlerToHTML &dataHandler);
};

#endif // SYSTEMDATACOLLECTOR_H
