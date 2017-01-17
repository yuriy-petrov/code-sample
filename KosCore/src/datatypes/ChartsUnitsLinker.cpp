#include "ChartsUnitsLinker.h"

static const QChar FIELDS_SEPARATOR('=');
static const QChar VALUES_SEPARATOR(';');

void ChartsUnitsLinker::setChartUnitLink(const Snapshot::Key &chart, const QString &unitName)
{
    insert(chart, unitName);
}

QString ChartsUnitsLinker::chartUnitLink(const Snapshot::Key &chart)
{
    return contains(chart) ?
                value(chart) :
                QString();
}

QDataStream &ChartsUnitsLinker::operator >>(QDataStream &stream) const
{
    return stream << *dynamic_cast<const QHash<Snapshot::Key, QString>*>(this);
}

QDataStream &ChartsUnitsLinker::operator <<(QDataStream &stream)
{
    return stream >> *dynamic_cast<QHash<Snapshot::Key, QString>*>(this);
}

QDebug &ChartsUnitsLinker::operator >>(QDebug &debug) const
{
    debug << "ChartsUnitsLinker:";
    foreach(const key_type& key, keys()) {
        debug.nospace() << key << "=" << value(key) << "; ";
    }
    return debug.space();
}

QString ChartsUnitsLinker::toString() const
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

ChartsUnitsLinker ChartsUnitsLinker::fromString(const QString &string)
{
    ChartsUnitsLinker instance;
    QRegExp parser(QString("(\\S+)%1(\\S+)").arg(FIELDS_SEPARATOR));

    foreach(const key_type& key, string.split(VALUES_SEPARATOR, QString::SkipEmptyParts)) {
        if(parser.indexIn(key) != -1) {
            instance.insert(parser.cap(1), parser.cap(2));
        }
    }

    return instance;
}

QJsonValue ChartsUnitsLinker::toJsonValue() const
{
    QByteArray buffer;
    QDataStream s(&buffer, QIODevice::WriteOnly);
    *this >> s;
    return QJsonValue(QString(buffer.toHex()));
}

ChartsUnitsLinker ChartsUnitsLinker::fromJsonValue(const QJsonValue &value)
{
    QDataStream s(QByteArray::fromHex(value.toString().toLocal8Bit()));
    ChartsUnitsLinker instance;
    instance << s;
    return instance;
}

QVariant ChartsUnitsLinker::toVariant() const
{
    return QVariant::fromValue<ChartsUnitsLinker>(*this);
}
