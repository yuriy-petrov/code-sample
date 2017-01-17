#ifndef KOSUTILS_H
#define KOSUTILS_H

#include <QColor>
#include <QPointF>
#include <QObject>

class KosUtils : public QObject
{

    Q_OBJECT

public:

    static KosUtils * instance();

    QColor colorFromString(const QString & text);
    QString colorToString(const QColor & color);

    QPointF pointFromString(const QString & text);
    QString pointToString(const QPointF & point);

private:

    KosUtils();

private:

    static KosUtils * m_instance;

};

#endif // KOSUTILS_H
