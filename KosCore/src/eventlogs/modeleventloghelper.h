#ifndef MODELEVENTLOGHELPER_H
#define MODELEVENTLOGHELPER_H

#include <modeltypes.h>
#include <modeleventlogelement.h>

#include <QJsonValue>
#include <QVariant>

class ModelEventLogHelper
{
public:
    static QJsonValue toJsonValue(const QString& key, const QVariant& value);
    static QVariant fromJsonValue(const QString &key, const QJsonValue& jsonValue);

    static Model::HystatMode::Type mode(const QVariant& value);

    static bool powerOn(const QVariant& value);

    static QString eventDescription(const QString& key, const QVariant& value);
    static QString filterDescription(const QString& key, const QVariant& value);

    static ModelEventLogElement * generateEventLogElement(const QString& key, const QVariant& value);
};

#endif // MODELEVENTLOGHELPER_H
