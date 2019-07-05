#include "filesystemworkmodule.h"

FileSystemWorkModule::FileSystemWorkModule(const QString &title, const QString extensionFilter)
    : QGroupBox(),
      _extensionFilter(extensionFilter)
{
    setTitle(title);

    _layout = new QGridLayout;
    setLayout(_layout);

    _path = new QLineEdit("");
    _layout->addWidget(_path, 0, 0, 1, 4);

    _specifyPathButton = new QPushButton("Указать путь");
    _layout->addWidget(_specifyPathButton, 0, 4, 1, 1);
    connect(_specifyPathButton, SIGNAL(clicked()), this, SLOT(onSpecifyPath()));
}

FileSystemWorkModule::~FileSystemWorkModule()
{
    delete _layout;
    delete _path;
    delete _specifyPathButton;
}

QString FileSystemWorkModule::getPath() const
{
    return _path->text();
}
