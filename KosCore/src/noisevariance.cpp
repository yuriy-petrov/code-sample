#include <log.h>

#include "noisevariance.h"

static const QChar FIELDS_SEPARATOR('=');
static const QChar VALUES_SEPARATOR(';');

void Model::NoiseVariance::mixinNoise(Snapshot &snapshot, qint64 simulationTime_ms) const
{
    foreach(const key_type& key, keys()) {
        QVariant variantValue = snapshot.value(key);
        if(variantValue.isValid()) {
            double dv = variantValue.toDouble();
            double noise = value(key) * (double)qrand() / (double)RAND_MAX - value(key) / 2.0;
            dv += noise;
            snapshot.setValue(key, dv, simulationTime_ms);
            LOG << "Mixin noise" << key << noise;
        }
    }
}

QString Model::NoiseVariance::toString() const
{
    QStringList list;

    foreach(const key_type& key, keys()) {
        list << QString("%1%2%3")
                .arg(key)
                .arg(FIELDS_SEPARATOR)
                .arg(value(key));
    }

    return list.join(VALUES_SEPARATOR);
}

Model::NoiseVariance Model::NoiseVariance::fromString(const QString &string)
{
    NoiseVariance nv;
    QRegExp parser(QString("(\\S+)%1(\\S+)").arg(FIELDS_SEPARATOR));

    foreach(const key_type& key, string.split(VALUES_SEPARATOR, QString::SkipEmptyParts)) {
        if(parser.indexIn(key) != -1) {
            nv.insert(parser.cap(1), parser.cap(2).toDouble());
        }
    }

    return nv;
}

QJsonValue Model::NoiseVariance::toJsonValue() const
{
    QByteArray buffer;
    QDataStream s(&buffer, QIODevice::WriteOnly);
    *this >> s;
    return QJsonValue(QString(buffer.toHex()));
}

Model::NoiseVariance Model::NoiseVariance::fromJsonValue(const QJsonValue &value)
{
    QDataStream s(QByteArray::fromHex(value.toString().toLocal8Bit()));
    NoiseVariance nv;
    nv << s;
    return nv;
}

QDataStream &Model::NoiseVariance::operator >>(QDataStream &stream) const
{
    return stream << *dynamic_cast<const QHash<Snapshot::Key, double>*>(this);
}

QDataStream &Model::NoiseVariance::operator <<(QDataStream &stream)
{
    return stream >> *dynamic_cast<QHash<Snapshot::Key, double>*>(this);
}

QDebug &Model::NoiseVariance::operator >>(QDebug &debug) const
{
    debug << "NoiseVariance:";
    foreach(const NoiseVariance::key_type& key, keys()) {
        debug.nospace() << key << "=" << value(key) << "; ";
    }
    return debug.space();
}
