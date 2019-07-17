#ifndef DATAHANDLERTOHTML_H
#define DATAHANDLERTOHTML_H

class QString;
class QFile;

class DataHandlerToHTML
{
public:
    DataHandlerToHTML(const QString &outFilePath,
                      const QString &stylesFilePath,
                      const QString &scriptsFilePath);
    ~DataHandlerToHTML();

    void endWorkWithFile();
    void beginGroup(const QString &name);
    void endGroup();
    void addProperty(const QString &name, const QString &value, const bool doLineFeed);

private:
    QFile   *_file;
    QString *_stylesFilePath;
    QString *_scriptsFilePath;

    void addHeader();
    void addBottom();
};

#endif // DATAHANDLERTOHTML_H
