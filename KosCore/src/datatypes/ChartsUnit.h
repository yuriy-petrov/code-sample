#ifndef CHARTSUNIT_H
#define CHARTSUNIT_H

#include <QMetaType>
#include <QDataStream>
#include <QString>
#include <QRegExp>
#include <QDebug>

class ChartsUnit
{
public:
    ChartsUnit()
        : m_lower(0)
        , m_upper(0)
    {}

    ChartsUnit(const QString& name, double lower, double upper)
        : m_name(name)
        , m_lower(lower)
        , m_upper(upper)
    {}

    void setName(const QString& name)
    { m_name = name; }

    inline const QString& name() const
    { return m_name; }

    void setLower(double value)
    { m_lower = value; }

    inline double lower() const
    { return m_lower; }

    void setUpper(double value)
    { m_upper = value; }

    inline double upper() const
    { return m_upper; }

public:

    QString toString() const
    {
        return QString("%1(%2:%3)")
                .arg(m_name)
                .arg(m_lower)
                .arg(m_upper);
    }

    static ChartsUnit fromString(const QString& string)
    {
        static QRegExp parser("(\\S+)\\(([0-9.,e]+):([0-9.,e]+)\\)");
        if(parser.indexIn(string) != -1) {
            return ChartsUnit(parser.cap(1),
                              parser.cap(2).toDouble(),
                              parser.cap(3).toDouble());
        }
        return ChartsUnit();
    }

    QDataStream& operator >>(QDataStream& stream) const
    {
        return stream << m_name
                      << m_lower
                      << m_upper;
    }

    QDataStream& operator <<(QDataStream& stream)
    {
        return stream >> m_name
                      >> m_lower
                      >> m_upper;
    }

    QDebug& operator >>(QDebug& debug) const
    {
        debug.nospace() << "ChartsUnit("
                        << m_name
                        << "="
                        << m_lower
                        << ":"
                        << m_upper
                        << ")";
        return debug.space();
    }

private:
    QString m_name;
    double m_lower;
    double m_upper;
};

Q_DECLARE_METATYPE( ChartsUnit )

inline QDataStream& operator <<(QDataStream& stream, const ChartsUnit& v)
{
    return v >> stream;
}

inline QDataStream& operator >>(QDataStream& stream, ChartsUnit& v)
{
    return v << stream;
}

inline QDebug& operator <<(QDebug debug, const ChartsUnit& v)
{
    return v >> debug;
}

#endif // CHARTSUNIT_H
