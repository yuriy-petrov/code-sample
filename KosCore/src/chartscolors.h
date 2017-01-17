#ifndef CHARTSCOLORS_H
#define CHARTSCOLORS_H

#include <QHash>
#include <QString>
#include <QColor>
#include <QDataStream>
#include <QDebug>

class ChartsColors
{
public:
    ChartsColors();
    ~ChartsColors();

    void setColor(const QString& key, const QColor& color);
    inline QColor color(const QString& key) const;

    void remove(const QString& key);

    inline bool contains(const QString& key) const;

    inline bool isEmpty() const;

    inline int size() const;

    QStringList keys() const;

    void clear();

public:
    QDataStream& operator >>(QDataStream& stream) const;
    QDataStream& operator <<(QDataStream& stream);
    QDebug& operator >>(QDebug& debug) const;

    QString toString() const;
    inline static ChartsColors fromString(const QString& string);
    void loadFromString(const QString& string);

private:
    QHash<QString, QColor> m_Colors;
};

Q_DECLARE_METATYPE( ChartsColors )

QColor ChartsColors::color(const QString &key) const
{
    return m_Colors.contains(key) ?
                m_Colors[key] :
                QColor();
}

bool ChartsColors::contains(const QString &key) const
{
    return m_Colors.contains(key);
}

bool ChartsColors::isEmpty() const
{
    return m_Colors.isEmpty();
}

int ChartsColors::size() const
{
    return m_Colors.size();
}

ChartsColors ChartsColors::fromString(const QString &string)
{
    ChartsColors colors;
    colors.loadFromString(string);
    return colors;
}

inline QDataStream& operator <<(QDataStream& stream, const ChartsColors& colors)
{
    return colors >> stream;
}

inline QDataStream& operator >>(QDataStream& stream, ChartsColors& colors)
{
    return colors << stream;
}

inline QDebug& operator <<(QDebug debug, ChartsColors& colors)
{
    return colors >> debug;
}

#endif // CHARTSCOLORS_H
