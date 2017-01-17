#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

#pragma once

#include <QString>
#include "mustache.h"
#include <QVariantHash>

class HTMLTemplate
{
public:
    HTMLTemplate(QString filepath = "default.html");

    QString htmlTemplate();
private:
    void readLine(QByteArray data);
    QString _filePath;
    QString _template;
};

#endif // HTMLTEMPLATE_H
