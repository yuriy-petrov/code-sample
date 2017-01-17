#include <log.h>

#include "chartscolors.h"

static const QChar FIELDS_SEPARATOR('=');
static const QChar VALUES_SEPARATOR(';');

ChartsColors::ChartsColors()
{
}

ChartsColors::~ChartsColors()
{

}

void ChartsColors::setColor(const QString &key, const QColor &color)
{
    m_Colors[key] = color;
}

void ChartsColors::remove(const QString &key)
{
    m_Colors.remove(key);
}

QStringList ChartsColors::keys() const
{
    QStringList list = m_Colors.keys();
    qSort(list);
    return list;
}

void ChartsColors::clear()
{
    m_Colors.clear();
}

QDataStream &ChartsColors::operator >>(QDataStream &stream) const
{
    return stream << toString();
}

QDataStream &ChartsColors::operator <<(QDataStream &stream)
{
    QString string;

    stream >> string;

    fromString(string);

    return stream;
}

QDebug &ChartsColors::operator >>(QDebug &debug) const
{
    foreach(const QString& key, m_Colors.keys()) {
        debug << key << ":" << m_Colors[key].name(QColor::HexRgb) << endl;
    }

    return debug;
}

QString ChartsColors::toString() const
{
    QStringList list;

    foreach(const QString& key, m_Colors.keys()) {
        list << QString("%1%2%3")
                .arg(key)
                .arg(FIELDS_SEPARATOR)
                .arg(m_Colors[key].name(QColor::HexRgb));
    }

    return list.join(VALUES_SEPARATOR);
}

void ChartsColors::loadFromString(const QString &string)
{
    m_Colors.clear();

    QRegExp parser(QString("(\\S+)%1(\\S+)").arg(FIELDS_SEPARATOR));

    foreach(const QString& value, string.split(VALUES_SEPARATOR, QString::SkipEmptyParts)) {
        if(parser.indexIn(value) != -1) {
            m_Colors.insert(parser.cap(1), parser.cap(2));
        }
    }
}
