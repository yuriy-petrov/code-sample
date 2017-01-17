#include "HTMLTemplate.h"
#include <QDebug>
#include <QFile>

HTMLTemplate::HTMLTemplate(QString filePath)
    :   _filePath(filePath)
{
    qDebug() << "create new template for file" << _filePath;

    QFile fileTemplate(":/templates/" + filePath.split('.').first() + '/' + filePath);
    if (!fileTemplate.open(QIODevice::ReadOnly | QIODevice::Text)) {

        fileTemplate.setFileName(":/templates/" + _filePath);
        if ( !fileTemplate.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return;
        }
    }


    while (!fileTemplate.atEnd()) {

        QByteArray line = fileTemplate.readLine();
        readLine(line);
    }

    fileTemplate.close();
}

QString HTMLTemplate::htmlTemplate()
{
    return _template;
}

void HTMLTemplate::readLine(QByteArray data)
{
    _template.append(QString(data));
}
