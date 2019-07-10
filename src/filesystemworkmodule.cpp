#include "filesystemworkmodule.h"
#include <QGridLayout>

FileSystemWorkModule::FileSystemWorkModule(const QString &title, const QString &extensionFilter)
    : QGroupBox(title),
      _specifyPathButton("Указать путь"), _extensionFilter(extensionFilter)
{
    QGridLayout *layout = new QGridLayout;
    setLayout(layout);

    layout->addWidget(&_path, 0, 0, 1, 4);

    connect(&_specifyPathButton, &QPushButton::clicked, this, &FileSystemWorkModule::onSpecifyPath);
    layout->addWidget(&_specifyPathButton, 0, 4, 1, 1);
}

QString FileSystemWorkModule::getPath() const
{
    return _path.text();
}

void FileSystemWorkModule::setExtensionFilter(const QString &filter)
{
    _extensionFilter = filter;
}
