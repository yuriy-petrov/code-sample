#include "CanvasSchemeItem.h"

#include "CanvasSchemeElement.h"
#include "SchemeScene.h"
#include "SchemeView.h"
#include "SchemeItemHelper.h"

#include <QGraphicsSceneContextMenuEvent>
#include <QBrush>
#include <QDebug>

CanvasSchemeItem::CanvasSchemeItem(SchemeItemHelper * schemeItemHelper,
                                   CanvasSchemeElement * canvasSchemeElement,
                                   QGraphicsItem * parentItem) :
    AbstractSchemeItem(schemeItemHelper, canvasSchemeElement),
    QGraphicsRectItem(parentItem),
    m_canvasSchemeElement(canvasSchemeElement),
    m_gridVisible(false),
    m_isMoved(false)
{
    this->setBrush(QBrush(QColor(Qt::white)));

    elementChanged();

    QObject::connect(m_canvasSchemeElement, SIGNAL(changed()),
                     this, SLOT(elementChanged()));
}

CanvasSchemeElement * CanvasSchemeItem::canvasSchemeElement() const
{
    return m_canvasSchemeElement;
}

bool CanvasSchemeItem::gridVisible() const
{
    return m_gridVisible;
}

void CanvasSchemeItem::setGridVisible(bool gridVisible)
{
    m_gridVisible = gridVisible;
    elementChanged();
}

void CanvasSchemeItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    QGraphicsRectItem::paint(painter, option, widget);

    if (m_gridVisible)
    {
        if (m_canvasSchemeElement->gridStep() != 0)
        {
            for (qreal x = m_canvasSchemeElement->gridStep() * m_schemeItemHelper->schemeScene()->zoom(); x <= this->boundingRect().width(); x += m_canvasSchemeElement->gridStep() * m_schemeItemHelper->schemeScene()->zoom())
            {
                for (qreal y = m_canvasSchemeElement->gridStep() * m_schemeItemHelper->schemeScene()->zoom(); y <= this->boundingRect().height(); y += m_canvasSchemeElement->gridStep() * m_schemeItemHelper->schemeScene()->zoom())
                {
                    painter->drawEllipse(QRectF(x, y, 1, 1));
                }
            }
        }
    }
}

void CanvasSchemeItem::updateZoom()
{
    this->setRect(QRectF(0, 0, m_canvasSchemeElement->size().width() * m_schemeItemHelper->schemeScene()->zoom(), m_canvasSchemeElement->size().height() * m_schemeItemHelper->schemeScene()->zoom()));
    update();
    emit boundigRectChanged(this->boundingRect());
}

void CanvasSchemeItem::elementChanged()
{
    this->setToolTip(m_canvasSchemeElement->tooltip());
    updateZoom();
    AbstractSchemeItem::elementChanged();
}

void CanvasSchemeItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    m_mousePos = event->pos();
    event->accept();
}

void CanvasSchemeItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    QPointF dp = event->pos() - m_mousePos;
    m_mousePos = event->pos();

    QPointF sceneCenter = m_schemeItemHelper->schemeScene()->schemeView()->mapToScene(QPoint(m_schemeItemHelper->schemeScene()->schemeView()->width() / 2, m_schemeItemHelper->schemeScene()->schemeView()->height() / 2));

    if (!m_isMoved)
    {
        m_isMoved = true;
        m_schemeItemHelper->schemeScene()->schemeView()->centerOn(sceneCenter - dp);
        m_isMoved = false;
    }

    event->accept();
}

void CanvasSchemeItem::wheelEvent(QGraphicsSceneWheelEvent * event)
{
    QPointF sceneCenter = m_schemeItemHelper->schemeScene()->schemeView()->mapToScene(QPoint(m_schemeItemHelper->schemeScene()->schemeView()->width() / 2, m_schemeItemHelper->schemeScene()->schemeView()->height() / 2));
    sceneCenter = sceneCenter / m_schemeItemHelper->schemeScene()->zoom();

    qreal zoom = m_schemeItemHelper->schemeScene()->zoom();

    if (event->delta() > 0)
    {
        zoom += m_schemeItemHelper->schemeScene()->zoomDelta();
    }
    else if (event->delta() < 0)
    {
        zoom -= m_schemeItemHelper->schemeScene()->zoomDelta();
    }

    m_schemeItemHelper->schemeScene()->setZoom(zoom);

    sceneCenter = sceneCenter * m_schemeItemHelper->schemeScene()->zoom();
    m_schemeItemHelper->schemeScene()->schemeView()->centerOn(sceneCenter);
}
