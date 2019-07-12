#ifndef OUTERFILEINCLUDER_H
#define OUTERFILEINCLUDER_H

#include "filesystemworkmodule.h"

class QCheckBox;

class OuterFileIncluder : public FileSystemWorkModule
{
    Q_OBJECT

public:
    OuterFileIncluder(const QString &title = "Выбор файла", const QString &extensionFilter = "");
    ~OuterFileIncluder();

    bool isActive() const;

protected:
    QCheckBox *_activity;

private slots:
    virtual void onSpecifyPath() override;
    void onSwitchActivity();
};

#endif // OUTERFILEINCLUDER_H
