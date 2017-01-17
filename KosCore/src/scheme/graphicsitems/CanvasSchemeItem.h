#ifndef CANVASSCHEMEITEM_H
#define CANVASSCHEMEITEM_H

class SchemeScene;
class CanvasSchemeElement;

#include <QGraphicsRectItem>
#include <QSet>
#include <AbstractSchemeItem.h>

class CanvasSchemeItem : public AbstractSchemeItem, public QGraphicsRectItem
{

    Q_OBJECT

public:

    CanvasSchemeItem(SchemeItemHelper * schemeItemHelper,
                     CanvasSchemeElement * canvasSchemeElement,
                     QGraphicsItem * parentItem = NULL);

    CanvasSchemeElement * canvasSchemeElement() const;

    bool gridVisible() const;
    void setGridVisible(bool gridVisible);

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

public slots:

    virtual void updateZoom();

signals:

    void boundigRectChanged(const QRectF & boundingRect);

protected slots:

    virtual void elementChanged();

protected:

    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent * event);

protected:

    CanvasSchemeElement * m_canvasSchemeElement;

    bool m_gridVisible;

    QPointF m_mousePos;

    bool m_isMoved;

};

#endif // CANVASSCHEMEITEM_H
