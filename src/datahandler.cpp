#include "datahandler.h"

DataHandler::DataHandler(const QString &outFilePath,
                         const QString &stylesFilePath,
                         const QString &scriptsFilePath)
    : _file(outFilePath), _stylesFilePath(stylesFilePath), _scriptsFilePath(scriptsFilePath)
{
    _file.open(QIODevice::WriteOnly);
    addHeader();
}

DataHandler::~DataHandler()
{
    endWorkWithFile();
}

void DataHandler::endWorkWithFile()
{
    if (!_file.isOpen())
        return;

    addBottom();
    _file.close();
}

void DataHandler::addGroup(const QString &name, const std::vector<Property> &propertyList)
{
    if (!_file.isOpen())
        return;

    _file.write("\t\t<P>");
    _file.write("<DIV class=\"group\">\n");

    _file.write("\t\t\t<DIV class=\"group-name\">");
    _file.write(name.toUtf8());
    _file.write("</DIV>\n");

    for (auto &property : propertyList)
        addProperty(property);

    _file.write("\t\t</DIV>");
    _file.write("</P>\n");
}

void DataHandler::addProperty(const Property &property)
{
    if (!_file.isOpen())
        return;

    _file.write("\t\t\t<DIV class=\"property\">\n");

    _file.write("\t\t\t\t<SPAN class=\"property-name\">");
    _file.write(property.getName().toUtf8());
    _file.write(" </SPAN>\n");

    _file.write("\t\t\t\t<SPAN class=\"property-value\">");
    _file.write(property.getValue().toUtf8());
    _file.write("</SPAN>\n");

    _file.write("\t\t\t</DIV>\n");
}

void DataHandler::addHeader()
{
    if (!_file.isOpen())
        return;

    _file.write("<HTML>\n");
    _file.write("\t<HEAD>\n");

    if (!_stylesFilePath.isEmpty())
    {
        _file.write(("\t\t<LINK href=\"" + _stylesFilePath + "\" rel=\"stylesheet\">\n").toUtf8());
    }
    if (!_scriptsFilePath.isEmpty())
    {
        _file.write(("\t\t<SCRIPT src=\"" + _scriptsFilePath + "\">").toUtf8());
        _file.write("</SCRIPT>\n");
    }

    _file.write("\t</HEAD>\n");
    _file.write("\t<BODY>\n");
}

void DataHandler::addBottom()
{
    _file.write("\t</BODY>\n");
    _file.write("</HTML>");
}

Property::Property(const QString &name, const QString &value)
    : _name(name), _value(value)
{

}

const QString &Property::getName() const
{
    return _name;
}

const QString &Property::getValue() const
{
    return _value;
}
