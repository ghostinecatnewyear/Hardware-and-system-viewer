#include "filesystemworkmodule.h"
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

FileSystemWorkModule::FileSystemWorkModule(const QString &title, const QString &extensionFilter)
    : QGroupBox(title),
      _path(new QLineEdit), _specifyPathButton(new QPushButton("Указать путь")),
      _extensionFilter(new QString(extensionFilter))
{
    auto layout = new QGridLayout;
    setLayout(layout);

    layout->addWidget(_path, 0, 0, 1, 4);

    connect(_specifyPathButton, &QPushButton::clicked, this, &FileSystemWorkModule::onSpecifyPath);
    layout->addWidget(_specifyPathButton, 0, 4, 1, 1);
}

FileSystemWorkModule::~FileSystemWorkModule()
{
    delete _path;
    delete _specifyPathButton;
    delete _extensionFilter;
}

QString FileSystemWorkModule::getPath() const
{
    return _path->text();
}
