#include "outerfileincluder.h"
#include <QHBoxLayout>
#include <QFileDialog>

OuterFileIncluder::OuterFileIncluder(const QString &title, const QString &extensionFilter)
    : FileSystemWorkModule(title, extensionFilter)
{
    _activity.setText("Подключить");
    connect(&_activity, SIGNAL(clicked()), this, SLOT(onSwitchActivity()));
    onSwitchActivity();
    _layout.addWidget(&_activity);
}

bool OuterFileIncluder::isActive() const
{
    return _activity.isChecked();
}

Q_SLOT void OuterFileIncluder::onSpecifyPath()
{
    QString outerFilePath(QFileDialog::getOpenFileName(nullptr, "Выбор файла", "C:/", _extensionFilter));
    if (!QFile::exists(outerFilePath))
        return;
    _path.setText(outerFilePath);
}

Q_SLOT void OuterFileIncluder::onSwitchActivity()
{
    _path.setEnabled(_activity.isChecked());
    _specifyPathButton.setEnabled(_activity.isChecked());
}
