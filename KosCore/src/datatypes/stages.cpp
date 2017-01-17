#include "stages.h"
#include <log.h>

static const QChar FIELDS_SEPARATOR('=');
static const QChar VALUES_SEPARATOR(';');

using namespace Player;

QString Player::Stages::toString() const
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

Player::Stages Player::Stages::fromString(const QString &string)
{
    Stages v;
    QRegExp parser(QString("(.+)%1(.+)").arg(FIELDS_SEPARATOR));

    foreach(const QString& value, string.split(VALUES_SEPARATOR, QString::SkipEmptyParts)) {
        if(parser.indexIn(value) != -1) {
            Player::Stage s = Player::Stage::fromString(parser.cap(2));
            v.insert(static_cast<Model::HystatMode::Type>(parser.cap(1).toInt()), s);
        }
    }

    return v;
}

QJsonValue Player::Stages::toJsonValue() const
{
    QByteArray buffer;
    QDataStream s(&buffer, QIODevice::WriteOnly);
    *this >> s;
    return QJsonValue(QString(buffer.toHex()));
}

Player::Stages Player::Stages::fromJsonValue(const QJsonValue &value)
{
    QDataStream s(QByteArray::fromHex(value.toString().toLocal8Bit()));
    Stages v;
    v << s;
    return v;
}

QDataStream &Player::Stages::operator >>(QDataStream &stream) const
{
    return stream << *this;
}

QDataStream &Player::Stages::operator <<(QDataStream &stream)
{
    return stream >> *this;
}

QDebug &Player::Stages::operator >>(QDebug &debug) const
{
    debug << "Stages:";
    foreach(const Stages::key_type& key, keys()) {
        debug.nospace() << key << "=" << value(key) << "; ";
    }
    return debug.space();
}
