#include "TankSchemeItem.h"

#include "TankSchemeElement.h"
#include "SchemeScene.h"

#include <KosTypesHelper.h>
#include <StringsKeys.h>
#include <SchemeKeys.h>
#include <SettingsStorage.h>
#include <SchemeItemHelper.h>

#include <QPainter>
#include <QApplication>
#include <QStyle>

TankSchemeItem::TankSchemeItem(SchemeItemHelper * schemeItemHelper,
                               TankSchemeElement * tankSchemeElement,
                               QGraphicsItem * parentItem) :
    AbstractSchemeItem(schemeItemHelper, tankSchemeElement),
    QGraphicsPixmapItem(parentItem),
    m_tankSchemeElement(tankSchemeElement)
{
    this->setAcceptHoverEvents(true);

    elementChanged();

    QObject::connect(m_tankSchemeElement, SIGNAL(changed()),
                     this, SLOT(elementChanged()));

    this->setGraphicsItem(this);
}

QPixmap TankSchemeItem::tankPixmap(TankSchemeElement * tankSchemeElement, qreal factor)
{
    int margin = 3;
    QSize size(tankSchemeElement->size() * (tankSchemeElement->stretchable() ? factor : 1));
    QSize totalSize(2*margin + size.width(), 2*margin + size.height());

    QImage image(totalSize, QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);

    qreal sceneValue = tankSchemeElement->value() * (size.height() / 100.0);
    QRectF tankRect(margin, margin + size.height() - sceneValue, size.width(), sceneValue);
    painter.fillRect(tankRect, QBrush(KosTypesHelper::instance()->substanceTypeColors()[tankSchemeElement->substanceType()].rgba(), Qt::SolidPattern));

    painter.setBrush(QBrush(QColor(0, 0, 0, 0)));
    painter.drawRect(QRect(margin, margin, size.width(), size.height()));

    AbstractSchemeItem::drawSelectRect(&painter, tankSchemeElement);

    QPixmap pixmap;
    pixmap.convertFromImage(image);
    return pixmap;
}

void TankSchemeItem::updateZoom()
{
    if (m_tankSchemeElement->stretchable())
    {
        elementChanged();
    }
    else
    {
        this->setPos(m_tankSchemeElement->position() * m_schemeItemHelper->schemeScene()->zoom());
    }
}

void TankSchemeItem::elementChanged()
{
    this->setToolTip(m_tankSchemeElement->tooltip());

    QPixmap pixmap = TankSchemeItem::tankPixmap(m_tankSchemeElement, m_schemeItemHelper->schemeScene()->zoom());

    this->setPixmap(pixmap);
    this->setOffset(-pixmap.width() / 2.0,
                    -pixmap.height() / 2.0);
    this->setPos(m_tankSchemeElement->position() * m_schemeItemHelper->schemeScene()->zoom());

    AbstractSchemeItem::elementChanged();
}
