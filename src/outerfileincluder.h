#ifndef OUTERFILEINCLUDER_H
#define OUTERFILEINCLUDER_H

#include <QCheckBox>
#include "filesystemworkmodule.h"

class OuterFileIncluder : public FileSystemWorkModule
{
    Q_OBJECT

public:
    OuterFileIncluder(const QString &title = "Выбор файла", const QString &extensionFilter = QString());
    ~OuterFileIncluder() override;
    bool isActive() const;

protected:
    QCheckBox *_activity;

private slots:
    virtual void onSpecifyPath() override;
    void onSwitchActivity();
};

#endif // OUTERFILEINCLUDER_H
