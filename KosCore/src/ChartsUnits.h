#ifndef CHARTSUNITS_H
#define CHARTSUNITS_H

#include <QHash>
#include <QString>
#include <QJsonValue>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <snapshot.h>

#include "ChartsUnit.h"

class ChartsUnits : public QHash<QString, ChartsUnit>
{
public:

    void setUnit(const ChartsUnit& unit);
    ChartsUnit unit(const QString& name) const;
    ChartsUnit& unit(const QString& name);

public:

    QDataStream& operator >>(QDataStream& stream) const;
    QDataStream& operator <<(QDataStream& stream);
    QDebug& operator >>(QDebug& debug) const;

    QString toString() const;
    static ChartsUnits fromString(const QString& string);

    QJsonValue toJsonValue() const;
    static ChartsUnits fromJsonValue(const QJsonValue& value);

    QVariant toVariant() const;
};

Q_DECLARE_METATYPE( ChartsUnits )

inline QDataStream& operator <<(QDataStream& stream, const ChartsUnits& v)
{
    return v >> stream;
}

inline QDataStream& operator >>(QDataStream& stream, ChartsUnits& v)
{
    return v << stream;
}

inline QDebug& operator <<(QDebug debug, const ChartsUnits& v)
{
    return v >> debug;
}


#endif // CHARTSUNITS_H
