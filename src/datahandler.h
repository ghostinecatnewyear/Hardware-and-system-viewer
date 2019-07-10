#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QFile>
#include <string>

class Property;

class DataHandler
{
public:
    DataHandler(const QString &outFilePath, const QString &stylesFilePath, const QString &scriptsFilePath);
    ~DataHandler();

    void endWorkWithFile();
    void addGroup(const QString &name, const std::vector<Property> &propertyList);

private:
    QFile   _file;
    QString _stylesFilePath;
    QString _scriptsFilePath;

    void addHeader();
    void addBottom();
    void addProperty(const Property &property);
};

class Property
{
public:
    Property(const QString &name, const QString &value);

    const QString &getName() const;
    const QString &getValue() const;

private:
    QString _name;
    QString _value;
};

#endif // DATAHANDLER_H
