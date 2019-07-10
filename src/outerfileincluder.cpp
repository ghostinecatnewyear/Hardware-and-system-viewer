#include "outerfileincluder.h"
#include <QFileDialog>
#include <QLayout>

OuterFileIncluder::OuterFileIncluder(const QString &title, const QString &extensionFilter)
    : FileSystemWorkModule(title, extensionFilter),
      _activity("Подключить")
{
    connect(&_activity, &QCheckBox::clicked, this, &OuterFileIncluder::onSwitchActivity);
    onSwitchActivity();
    QLayout *layout = this->layout();
    layout->addWidget(&_activity);
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
