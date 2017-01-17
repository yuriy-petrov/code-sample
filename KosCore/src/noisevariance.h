#ifndef NOISEVARIANCE_H
#define NOISEVARIANCE_H

#include <QHash>
#include <snapshot.h>

namespace Model {

class NoiseVariance : public QHash<Snapshot::Key, double>
{
public:
    void mixinNoise(Snapshot& snapshot, qint64 simulationTime_ms) const;

public:
    QString toString() const;
    static NoiseVariance fromString(const QString& string);

    QJsonValue toJsonValue() const;
    static NoiseVariance fromJsonValue(const QJsonValue& value);

    QDataStream& operator >>(QDataStream& stream) const;
    QDataStream& operator <<(QDataStream& stream);

    QDebug& operator >>(QDebug& debug) const;
};

inline QDataStream& operator <<(QDataStream& stream, const NoiseVariance& nv)
{
    return nv >> stream;
}

inline QDataStream& operator >>(QDataStream& stream, NoiseVariance& nv)
{
    return nv << stream;
}

inline QDebug& operator <<(QDebug debug, const NoiseVariance& nv)
{
    return nv >> debug;
}

}

Q_DECLARE_METATYPE( Model::NoiseVariance )

#endif // NOISEVARIANCE_H
