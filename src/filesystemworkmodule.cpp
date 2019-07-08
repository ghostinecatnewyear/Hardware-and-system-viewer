#include "filesystemworkmodule.h"

FileSystemWorkModule::FileSystemWorkModule(const QString &title, const QString &extensionFilter)
    : QGroupBox(title),
      _extensionFilter(extensionFilter)
{
    setLayout(&_layout);

    _layout.addWidget(&_path, 0, 0, 1, 4);

    _specifyPathButton.setText("Указать путь");
    connect(&_specifyPathButton, SIGNAL(clicked()), this, SLOT(onSpecifyPath()));
    _layout.addWidget(&_specifyPathButton, 0, 4, 1, 1);
}

QString FileSystemWorkModule::getPath() const
{
    return _path.text();
}

void FileSystemWorkModule::setExtensionFilter(const QString &filter)
{
    _extensionFilter = filter;
}
