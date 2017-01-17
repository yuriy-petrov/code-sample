#ifndef CANVASSCHEMEELEMENT_H
#define CANVASSCHEMEELEMENT_H

#include "AbstractSchemeElement.h"

#include <QSize>
#include <QPointF>
#include <QRectF>

class CanvasSchemeElement : public AbstractSchemeElement
{

    Q_OBJECT

public:

    CanvasSchemeElement(QObject * parent = 0);

    virtual void fromJsonObject(const QJsonObject & jsonObject);
    virtual QJsonObject toJsonObject() const;

    static QString schemeElementName();

    QString title() const;
    void setTitle(const QString & title);

    QSize size() const;
    void setSize(const QSize & size);

    int gridStep() const;
    void setGridStep(const int & gridStep);

    qreal defaultZoom() const;
    void setDefaultZoom(const qreal & defaultZoom);

    qreal basicFactor() const;
    void setBasicFactor(const qreal & basicFactor);

    qreal valveFactor() const;
    void setValveFactor(const qreal & valveFactor);

    qreal levelFactor() const;
    void setLevelFactor(const qreal & levelFactor);

    void setParameters(const QString & title,
                       const QSize & size,
                       const int & gridStep,
                       qreal defaultZoom,
                       const qreal & basicFactor,
                       const qreal & valveFactor,
                       const qreal & levelFactor);

    QPointF pointByGrid(const QPointF & point, bool checkSize = true) const;
    QPointF pointBySize(const QPointF & point) const;

    virtual void move(const QPointF & dp);

private:

    QString m_title;
    QSize m_size;
    int m_gridStep;
    qreal m_defaultZoom;
    qreal m_basicFactor;
    qreal m_valveFactor;
    qreal m_levelFactor;

};

#endif // CANVASSCHEMEELEMENT_H
