#include "ChartsUnits.h"

static const QChar FIELDS_SEPARATOR('=');
static const QChar VALUES_SEPARATOR(';');

void ChartsUnits::setUnit(const ChartsUnit &unit)
{
    insert(unit.name(), unit);
}

ChartsUnit ChartsUnits::unit(const QString &name) const
{
    return contains(name) ?
                value(name) :
                ChartsUnit();
}

ChartsUnit &ChartsUnits::unit(const QString &name)
{
    if(!contains(name)) {
        setUnit(ChartsUnit(name, 0, 0));
    }

    return (*this)[name];//(*dynamic_cast<const QHash<Snapshot::Key, ChartsUnit>*>(this))[name];
}

QDataStream &ChartsUnits::operator >>(QDataStream &stream) const
{
    return stream << *dynamic_cast<const QHash<Snapshot::Key, ChartsUnit>*>(this);
}

QDataStream &ChartsUnits::operator <<(QDataStream &stream)
{
    return stream >> *dynamic_cast<QHash<Snapshot::Key, ChartsUnit>*>(this);
}

QDebug &ChartsUnits::operator >>(QDebug &debug) const
{
    debug << "ChartsUnits:";
    foreach(const key_type& key, keys()) {
        debug.nospace() << key << "=" << value(key) << "; ";
    }
    return debug.space();
}

QString ChartsUnits::toString() const
{
    QStringList list;

    foreach(const key_type& key, keys()) {
        list << QString("%1%2%3")
                .arg(key)
                .arg(FIELDS_SEPARATOR)
                .arg(value(key).toString());
    }

    return list.join(VALUES_SEPARATOR);
}

ChartsUnits ChartsUnits::fromString(const QString &string)
{
    ChartsUnits instance;
    QRegExp parser(QString("(\\S+)%1(\\S+)").arg(FIELDS_SEPARATOR));

    foreach(const key_type& key, string.split(VALUES_SEPARATOR, QString::SkipEmptyParts)) {
        if(parser.indexIn(key) != -1) {
            instance.insert(parser.cap(1), ChartsUnit::fromString(parser.cap(2)));
        }
    }

    return instance;
}

QJsonValue ChartsUnits::toJsonValue() const
{
    QByteArray buffer;
    QDataStream s(&buffer, QIODevice::WriteOnly);
    *this >> s;
    return QJsonValue(QString(buffer.toHex()));
}

ChartsUnits ChartsUnits::fromJsonValue(const QJsonValue &value)
{
    QDataStream s(QByteArray::fromHex(value.toString().toLocal8Bit()));
    ChartsUnits instance;
    instance << s;
    return instance;
}

QVariant ChartsUnits::toVariant() const
{
    return QVariant::fromValue<ChartsUnits>(*this);
}
