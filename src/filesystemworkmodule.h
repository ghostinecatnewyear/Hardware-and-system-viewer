#ifndef FILESYSTEMWORKMODULE_H
#define FILESYSTEMWORKMODULE_H

#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

class FileSystemWorkModule : public QGroupBox
{
    Q_OBJECT

public:
    FileSystemWorkModule(const QString &title, const QString &extensionFilter);
    QString getPath() const;
    void setExtensionFilter(const QString &filter);

protected:
    QGridLayout _layout;
    QLineEdit   _path;
    QPushButton _specifyPathButton;
    QString     _extensionFilter;

protected slots:
    virtual void onSpecifyPath() = 0;
};

#endif // FILESYSTEMWORKMODULE_H
