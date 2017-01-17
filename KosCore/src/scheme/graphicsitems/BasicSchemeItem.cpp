#include "BasicSchemeItem.h"

#include "BasicSchemeElement.h"
#include "StringsKeys.h"
#include "SchemeKeys.h"
#include "SettingsStorage.h"
#include "SchemeScene.h"
#include "CanvasSchemeItem.h"
#include "CanvasSchemeElement.h"
#include "SchemeItemHelper.h"

#include <QApplication>
#include <QStyle>
#include <QSvgRenderer>
#include <QPainter>

BasicSchemeItem::BasicSchemeItem(SchemeItemHelper * schemeItemHelper,
                                 BasicSchemeElement * basicSchemeElement,
                                 QGraphicsItem * parentItem) :
    AbstractSchemeItem(schemeItemHelper, basicSchemeElement),
    QGraphicsPixmapItem(parentItem),
    m_basicSchemeElement(basicSchemeElement)
{
    this->setAcceptHoverEvents(true);
    this->setGraphicsItem(this);

    elementChanged();

    QObject::connect(m_schemeItemHelper->schemeScene()->canvasSchemeItem()->canvasSchemeElement(), SIGNAL(changed()),
                     this, SLOT(elementChanged()));
    QObject::connect(m_basicSchemeElement, SIGNAL(changed()),
                     this, SLOT(elementChanged()));
}

QPixmap BasicSchemeItem::basicPixmap(BasicSchemeElement * basicSchemeElement, qreal factor)
{
    QImage image;
    QSvgRenderer svgRenderer;
    if (svgRenderer.load(QString(":/images/basicSchemeElements/%1-%2.svg").arg(basicSchemeElement->type()).arg(basicSchemeElement->state())))
    {
        image = QImage(svgRenderer.defaultSize() * factor * basicSchemeElement->factor(), QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter painter(&image);
        svgRenderer.render(&painter);
    }
    else
    {
        if (image.load(QString(":/images/basicSchemeElements/%1-%2.png").arg(basicSchemeElement->type()).arg(basicSchemeElement->state())))
        {
            QTransform transform;
            transform.scale(factor * basicSchemeElement->factor(), factor * basicSchemeElement->factor());
            image = image.transformed(transform);
        }
        else
        {
            image = QApplication::style()->standardPixmap(QStyle::SP_MessageBoxQuestion).toImage();
        }
    }

    for (int x = 0; x < image.size().width(); ++x)
    {
        for (int y = 0; y < image.size().height(); ++y)
        {
            if (image.pixel(x, y) == KosConsts::MAGIC_COLOR.rgba())
            {
                image.setPixel(x, y, basicSchemeElement->color().rgba());
            }
        }
    }

    if (basicSchemeElement->rotation() != 0)
    {
        image = image.transformed(QTransform().rotate(basicSchemeElement->rotation()));
    }

    if (basicSchemeElement->mirroredHorizontal() || basicSchemeElement->mirroredVertical())
    {
        image = image.mirrored(basicSchemeElement->mirroredHorizontal(), basicSchemeElement->mirroredVertical());
    }

    QPixmap pixmap;
    pixmap.convertFromImage(image);

    QPainter painter(&pixmap);
    AbstractSchemeItem::drawSelectRect(&painter, basicSchemeElement);
    return pixmap;
}

void BasicSchemeItem::updateZoom()
{
    qreal factor = m_schemeItemHelper->schemeScene()->canvasSchemeItem()->canvasSchemeElement()->basicFactor();
    if (m_basicSchemeElement->strechable())
    {
        factor *= m_schemeItemHelper->schemeScene()->zoom();
    }

    this->setPixmap(BasicSchemeItem::basicPixmap(m_basicSchemeElement, factor));
    this->setOffset(-this->pixmap().width() / 2.0,
                    -this->pixmap().height() / 2.0);
    this->setPos(m_basicSchemeElement->position() * m_schemeItemHelper->schemeScene()->zoom());
    AbstractSchemeItem::elementChanged();
}

void BasicSchemeItem::elementChanged()
{
    this->setToolTip(m_basicSchemeElement->tooltip());
    updateZoom();
}
