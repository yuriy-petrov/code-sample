#ifndef MODELTYPESHELPER_H
#define MODELTYPESHELPER_H

#include <QString>
#include <QJsonValue>
#include <modeltypes.h>

namespace Model
{


class TypesHelper
{
public:

    enum
    {
        ModelKeyRole = Qt::UserRole
    };

public:

    static const QMap<Model::HystatMode::Type, QString>& hystatModeNames();
    static QString hystatModeToString(Model::HystatMode::Type mode);
    static Model::HystatMode::Type hystatModeFromString(const QString& name);

    static const QMap<Model::HwSwitchPos, QString>& hwSwitchPosNames();
    static QString hwSwitchPosToString(Model::HwSwitchPos pos);
    static Model::HwSwitchPos hwSwitchPosFromString(const QString& name);

    static const QMap<bool, QString>& cellStackEnableNames();

    static QJsonValue toJsonValue(const QString& key, const QVariant& value);
    static QVariant fromJsonValue(const QString& key, const QJsonValue& value);

    static QString toString(const QString& key, const QVariant& value);
    static QVariant fromString(const QString& key, const QString& value);

    static QVariant initValue(const QString& key);

    static bool sameTypes(const QString& key1, const QString& key2);

    static QStringList valuesNames(const QString& key);
};

}

#endif // MODELTYPESHELPER_H
