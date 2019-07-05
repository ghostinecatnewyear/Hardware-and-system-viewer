#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include <QFile>

/**
 * Класс, создающий выходной файл HTML и обращающийся к
 * функциям библиотеки windowsoptions за информацией о
 * системе, которую затем компонует в выходном файле.
 */

class DataCollector
{
public:
    static void collectData(const QString outFilePath,
                            const QString stylesFilePath, const bool doIncludeStyles,
                            const QString scriptsFilePath, const bool doIncludeScripts);
};

#endif // DATACOLLECTOR_H
