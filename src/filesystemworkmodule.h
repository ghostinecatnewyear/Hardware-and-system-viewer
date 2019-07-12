#ifndef FILESYSTEMWORKMODULE_H
#define FILESYSTEMWORKMODULE_H

#include <QGroupBox>

class QLineEdit;
class QPushButton;
class QString;

class FileSystemWorkModule : public QGroupBox
{
    Q_OBJECT

public:
    FileSystemWorkModule(const QString &title, const QString &extensionFilter);
    ~FileSystemWorkModule();

    QString getPath() const;

protected:
    QLineEdit   *_path;
    QPushButton *_specifyPathButton;
    QString     *_extensionFilter;

protected slots:
    virtual void onSpecifyPath() = 0;
};

#endif // FILESYSTEMWORKMODULE_H
