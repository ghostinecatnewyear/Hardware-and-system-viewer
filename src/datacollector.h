#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include <QString>

class DataCollector
{
    DataCollector() = delete;

public:
    static void collectData(const QString &outFilePath,
                            const QString &stylesFilePath,
                            const QString &scriptsFilePath);
};

#endif // DATACOLLECTOR_H
