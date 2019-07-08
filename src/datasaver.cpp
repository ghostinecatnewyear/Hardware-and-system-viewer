#include "datasaver.h"
#include <QFileDialog>

DataSaver::DataSaver(const QString &title, const QString &extensionFilter)
    : FileSystemWorkModule(title, extensionFilter)
{

}

Q_SLOT void DataSaver::onSpecifyPath()
{
    _path.setText(QFileDialog::getSaveFileName(nullptr, "Сохранение файла", "C:/", "*.html"));
}
