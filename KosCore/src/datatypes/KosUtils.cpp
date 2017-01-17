#include "KosUtils.h"

extern KosUtils * KosUtils::m_instance = NULL;

KosUtils * KosUtils::instance()
{
    if (m_instance == NULL)
    {
        m_instance = new KosUtils();
    }

    return m_instance;
}

QColor KosUtils::colorFromString(const QString & text)
{
    QStringList parts = text.split("/");
    if (parts.size() != 4)
    {
        return QColor();
    }
    return QColor(parts[0].toInt(), parts[1].toInt(), parts[2].toInt(), parts[3].toInt());
}

QString KosUtils::colorToString(const QColor & color)
{
    return QString("%1/%2/%3/%4").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
}

QPointF KosUtils::pointFromString(const QString & text)
{
    QStringList coords = text.split("x");
    if (coords.size() != 2)
    {
        return QPointF();
    }
    return QPointF(coords[0].toDouble(), coords[1].toDouble());
}

QString KosUtils::pointToString(const QPointF & point)
{
    return QString("%1x%2").arg(point.x()).arg(point.y());
}

KosUtils::KosUtils() :
    QObject()
{
}
