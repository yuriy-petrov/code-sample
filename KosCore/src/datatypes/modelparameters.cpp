#include "modelparameters.h"

static const QChar FIELDS_SEPARATOR('=');
static const QChar VALUES_SEPARATOR(';');

QString Model::Parameters::Type::toString() const
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

Model::Parameters::Type Model::Parameters::Type::fromString(const QString &string)
{
    Type v;
    QRegExp parser(QString("(\\S+)%1(\\S+)").arg(FIELDS_SEPARATOR));

    foreach(const key_type& key, string.split(VALUES_SEPARATOR, QString::SkipEmptyParts)) {
        if(parser.indexIn(key) != -1) {
            v.insert(parser.cap(1), parser.cap(2).toDouble());
        }
    }

    return v;
}

QJsonValue Model::Parameters::Type::toJsonValue() const
{
    QByteArray buffer;
    QDataStream s(&buffer, QIODevice::WriteOnly);
    *this >> s;
    return QJsonValue(QString(buffer.toHex()));
}

Model::Parameters::Type Model::Parameters::Type::fromJsonValue(const QJsonValue &value)
{
    QDataStream s(QByteArray::fromHex(value.toString().toLocal8Bit()));
    Type v;
    v << s;
    return v;
}

QDataStream &Model::Parameters::Type::operator >>(QDataStream &stream) const
{
    return stream << *dynamic_cast<const QMap<QString,double>*>(this);
}

QDataStream &Model::Parameters::Type::operator <<(QDataStream &stream)
{
    return stream >> *dynamic_cast<QMap<QString,double>*>(this);
}

QDebug &Model::Parameters::Type::operator >>(QDebug &debug) const
{
    debug << "Model:Parameters:";
    foreach(const key_type& key, keys()) {
        debug.nospace() << key << "=" << value(key) << "; ";
    }
    return debug.space();
}
