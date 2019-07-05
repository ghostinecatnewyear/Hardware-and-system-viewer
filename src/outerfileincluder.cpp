#include "outerfileincluder.h"
#include <QHBoxLayout>
#include <QFileDialog>

OuterFileIncluder::OuterFileIncluder(const QString &title, const QString &extensionFilter)
    : FileSystemWorkModule(title, extensionFilter)
{
    _activity = new QCheckBox("Подключить");
    onSwitchActivity();
    _layout->addWidget(_activity);
    connect(_activity, SIGNAL(clicked()), this, SLOT(onSwitchActivity()));
}

OuterFileIncluder::~OuterFileIncluder()
{
    delete _activity;
}

bool OuterFileIncluder::isActive() const
{
    return _activity->isChecked();
}

Q_SLOT void OuterFileIncluder::onSpecifyPath()
{
    QString outerFilePath(QFileDialog::getOpenFileName(nullptr, "Выбор файла", "C:/", _extensionFilter));
    if (!QFile::exists(outerFilePath))
        return;
    _path->setText(outerFilePath);
}

Q_SLOT void OuterFileIncluder::onSwitchActivity()
{
    if (_activity->isChecked())
    {
        _path->setEnabled(true);
        _specifyPathButton->setEnabled(true);
    }
    else
    {
        _path->setEnabled(false);
        _specifyPathButton->setEnabled(false);
    }
}
