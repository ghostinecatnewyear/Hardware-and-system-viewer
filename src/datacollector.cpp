#include "datacollector.h"
#include "windowsoptions.h"

using namespace WindowsOptions;

void DataCollector::collectData(const QString &outFilePath,
                                const QString &stylesFilePath,  const bool doIncludeStyles,
                                const QString &scriptsFilePath, const bool doIncludeScripts)
{
    QFile outFile(outFilePath);
    outFile.open(QIODevice::WriteOnly);

    if (doIncludeStyles)
    {
        outFile.write(("[Внешний файл CSS \""
                       + stylesFilePath  + "\" подключён]<br><br>").toUtf8());
    }
    if (doIncludeScripts)
    {
        outFile.write(("[Внешний файл JavaScript \""
                       + scriptsFilePath + "\" подключён]<br><br>").toUtf8());
    }

    outFile.write("Operating System<br>");
    outFile.write(QString::fromStdString("Computer Name "  + getComputerName()  + "<br>").toUtf8());
    outFile.write(QString::fromStdString("Windows Folder " + getWindowsFolder() + "<br>").toUtf8());
    outFile.write(QString::fromStdString("System Folder "  + getSystemFolder()  + "<br>").toUtf8());

    outFile.write("<br>Hardware<br>");
    outFile.write(("Number of Processors " + QString::number(getNumberOfProcessors()) + "<br>").toUtf8());

    outFile.close();
}
