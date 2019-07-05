#ifndef FILESYSTEMWORKMODULE_H
#define FILESYSTEMWORKMODULE_H

#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>

class FileSystemWorkModule : public QGroupBox
{
    Q_OBJECT

public:
    FileSystemWorkModule(const QString &title, const QString extensionFilter);
    ~FileSystemWorkModule();
    QString getPath() const;

protected:
    QGridLayout *_layout;
    QLineEdit *_path;
    QPushButton *_specifyPathButton;
    const QString _extensionFilter;

protected slots:
    virtual void onSpecifyPath() = 0;
};

#endif // FILESYSTEMWORKMODULE_H
