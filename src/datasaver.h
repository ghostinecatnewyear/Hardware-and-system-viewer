#ifndef DATASAVER_H
#define DATASAVER_H

#include "filesystemworkmodule.h"

/**
 * Этот класс позволяет выбрать путь сохранения выходного файла.
 * Пока не используется: возможно, он лишний.
 */

class DataSaver : public FileSystemWorkModule
{
    Q_OBJECT

public:
    DataSaver(const QString &title = "Сохранение файла", const QString &extensionFilter = "");

protected slots:
    virtual void onSpecifyPath() override;
};

#endif // DATASAVER_H
