#include "datacollector.h"

void DataCollector::collectData(const QString outFilePath,
                                const QString stylesFilePath, const bool doIncludeStyles,
                                const QString scriptsFilePath, const bool doIncludeScripts)
{
    QFile outFile(outFilePath);
    outFile.open(QIODevice::WriteOnly);

    if (doIncludeStyles)
        outFile.write(("[Внешний файл CSS \"" + stylesFilePath + "\" подключён]<br>").toUtf8());
    if (doIncludeScripts)
        outFile.write(("[Внешний файл JavaScript \"" + scriptsFilePath + "\" подключён]<br>").toUtf8());
    outFile.write("[Данные об операционной системе и аппаратном обеспечении]<br>");

    outFile.close();
}
