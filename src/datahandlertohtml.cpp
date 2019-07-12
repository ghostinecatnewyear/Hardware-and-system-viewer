#include "datahandlertohtml.h"
#include <QFile>

DataHandlerToHTML::DataHandlerToHTML(const QString &outFilePath,
                                     const QString &stylesFilePath,
                                     const QString &scriptsFilePath)
    : _file(new QFile(outFilePath)),
      _stylesFilePath(new QString(stylesFilePath)),
      _scriptsFilePath(new QString(scriptsFilePath))
{
    _file->open(QIODevice::WriteOnly);
    addHeader();
}

DataHandlerToHTML::~DataHandlerToHTML()
{
    endWorkWithFile();
}

void DataHandlerToHTML::endWorkWithFile()
{
    if (!_file)
        return;

    addBottom();
    _file->close();
    delete _file;
    _file = nullptr;
    delete _stylesFilePath;
    delete _scriptsFilePath;
}

void DataHandlerToHTML::beginGroup(const QString &name)
{
    if (!_file)
        return;

    _file->write("\t\t<P>");
    _file->write("<DIV class=\"group\">\n");

    _file->write("\t\t\t<DIV class=\"group-name\">");
    _file->write(qPrintable(name));
    _file->write("</DIV>\n");
}

void DataHandlerToHTML::endGroup()
{
    if (!_file)
        return;

    _file->write("\t\t</DIV>");
    _file->write("</P>\n");
}

void DataHandlerToHTML::addProperty(const QString &name, const QString &value, const bool doLineFeed)
{
    if (!_file)
        return;

    _file->write("\t\t\t<SPAN class=\"property\">\n");

    _file->write("\t\t\t\t<SPAN class=\"property-name\">");
    _file->write(qPrintable(name + " "));
    _file->write("</SPAN>\n");

    _file->write("\t\t\t\t<SPAN class=\"property-value\">");
    _file->write(qPrintable(value));
    _file->write("</SPAN>\n");

    _file->write("\t\t\t</SPAN>");

    if (doLineFeed)
        _file->write("<BR>");

    _file->write("\n");
}

void DataHandlerToHTML::addHeader()
{
    if (!_file)
        return;

    _file->write("<HTML>\n");
    _file->write("\t<HEAD>\n");

    if (!_stylesFilePath->isEmpty())
    {
        _file->write(qPrintable("\t\t<LINK href=\"" + *_stylesFilePath + "\" rel=\"stylesheet\">\n"));
    }
    if (!_scriptsFilePath->isEmpty())
    {
        _file->write(qPrintable("\t\t<SCRIPT src=\"" + *_scriptsFilePath + "\">"));
        _file->write("</SCRIPT>\n");
    }

    _file->write("\t</HEAD>\n");
    _file->write("\t<BODY>\n");
}

void DataHandlerToHTML::addBottom()
{
    if (!_file)
        return;

    _file->write("\t</BODY>\n");
    _file->write("</HTML>");
}
