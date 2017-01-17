#ifndef CHARTSUNITSLINKER_H
#define CHARTSUNITSLINKER_H

#include <QHash>
#include <QMetaType>
#include <QDataStream>
#include <QJsonValue>
#include <snapshot.h>

class ChartsUnitsLinker : public QHash<Snapshot::Key, QString>
{
public:

    void setChartUnitLink(const Snapshot::Key& chart, const QString& unitName);
    QString chartUnitLink(const Snapshot::Key& chart);

public:

    QDataStream &operator >>(QDataStream& stream) const;
    QDataStream& operator <<(QDataStream& stream);
    QDebug& operator >>(QDebug& debug) const;

    QString toString() const;
    static ChartsUnitsLinker fromString(const QString& string);

    QJsonValue toJsonValue() const;
    static ChartsUnitsLinker fromJsonValue(const QJsonValue& value);

    QVariant toVariant() const;
};

Q_DECLARE_METATYPE( ChartsUnitsLinker )

inline QDataStream& operator <<(QDataStream& stream, const ChartsUnitsLinker& v)
{
    return v >> stream;
}

inline QDataStream& operator >>(QDataStream& stream, ChartsUnitsLinker& v)
{
    return v << stream;
}

inline QDebug& operator <<(QDebug debug, const ChartsUnitsLinker& v)
{
    return v >> debug;
}

#endif // CHARTSUNITSLINKER_H
