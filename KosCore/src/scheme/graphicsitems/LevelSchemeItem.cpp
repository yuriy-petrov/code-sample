#include "LevelSchemeItem.h"

#include "LevelSchemeElement.h"
#include "SchemeScene.h"

#include <KosTypesHelper.h>
#include <StringsKeys.h>
#include <SchemeKeys.h>
#include <SettingsStorage.h>
#include <CanvasSchemeItem.h>
#include <CanvasSchemeElement.h>
#include <SchemeItemHelper.h>

#include <QPainter>
#include <QApplication>
#include <QStyle>
#include <QGraphicsSceneContextMenuEvent>
#include <QSvgRenderer>

LevelSchemeItem::LevelSchemeItem(SchemeItemHelper * schemeItemHelper,
                                 LevelSchemeElement * levelSchemeElement,
                                 QGraphicsItem * parentItem) :
    AbstractSchemeItem(schemeItemHelper, levelSchemeElement),
    QGraphicsPixmapItem(parentItem),
    m_levelSchemeElement(levelSchemeElement)

{
    this->setAcceptHoverEvents(true);

    elementChanged();

    QObject::connect(m_schemeItemHelper->schemeScene()->canvasSchemeItem()->canvasSchemeElement(), SIGNAL(changed()),
                     this, SLOT(elementChanged()));
    QObject::connect(m_levelSchemeElement, SIGNAL(changed()),
                     this, SLOT(elementChanged()));

    this->setGraphicsItem(this);
}

QPixmap LevelSchemeItem::levelPixmap(LevelSchemeElement * levelSchemeElement, qreal factor)
{
    QImage image;
    QSvgRenderer svgRenderer;
    if (svgRenderer.load(QString(":/images/levelSchemeElements/%1.svg").arg(levelSchemeElement->levelElementType())))
    {
        image = QImage(svgRenderer.defaultSize() * factor, QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter painter(&image);
        svgRenderer.render(&painter);
    }
    else
    {
        if (image.load(QString(":/images/levelSchemeElements/%1.png").arg(levelSchemeElement->levelElementType())))
        {
            QTransform transform;
            transform.scale(factor, factor);
            image = image.transformed(transform);
        }
        else
        {
            return QApplication::style()->standardPixmap(QStyle::SP_MessageBoxQuestion);
        }
    }

    int minEdge = 0;
    int maxEdge = 0;
    for (int x = 0; x < image.size().width(); ++x)
    {
        for (int y = 0; y < image.size().height(); ++y)
        {
            if (image.pixel(x, y) == KosConsts::MAGIC_COLOR.rgba())
            {
                minEdge = qMin(minEdge, y);
                maxEdge = qMax(maxEdge, y);
            }
        }
    }

    qreal screenHeight = maxEdge - minEdge;
    qreal screenY = maxEdge - (screenHeight / 100.0)*levelSchemeElement->value();

    for (int y = minEdge; y < maxEdge; ++y)
    {
        for (int x = 0; x < image.size().width(); ++x)
        {
            if (image.pixel(x, y) == KosConsts::MAGIC_COLOR.rgba())
            {
                image.setPixel(x, y, y < screenY ? KosTypesHelper::instance()->substanceTypeColors()[levelSchemeElement->firstSubstanceType()].rgba() : KosTypesHelper::instance()->substanceTypeColors()[levelSchemeElement->secondSubstanceType()].rgba());
            }
        }
    }

    if (levelSchemeElement->mirroredHorizontal() || levelSchemeElement->mirroredVertical())
    {
        image = image.mirrored(levelSchemeElement->mirroredHorizontal(), levelSchemeElement->mirroredVertical());
    }

    QPixmap pixmap;
    pixmap = pixmap.fromImage(image);

    QPainter painter(&pixmap);
    AbstractSchemeItem::drawSelectRect(&painter, levelSchemeElement);
    return pixmap;
}

void LevelSchemeItem::updateZoom()
{
    if (m_levelSchemeElement->stretchable())
    {
        elementChanged();
    }
    else
    {
        this->setPos(m_levelSchemeElement->position() * m_schemeItemHelper->schemeScene()->zoom());
    }
}

void LevelSchemeItem::elementChanged()
{
    this->setToolTip(m_levelSchemeElement->tooltip());

    qreal factor = m_schemeItemHelper->schemeScene()->canvasSchemeItem()->canvasSchemeElement()->levelFactor() * m_levelSchemeElement->factor();
    if (m_levelSchemeElement->stretchable())
    {
        factor *= m_schemeItemHelper->schemeScene()->zoom();
    }
    QPixmap pixmap = LevelSchemeItem::levelPixmap(m_levelSchemeElement, factor);

    this->setPixmap(pixmap);
    this->setOffset(-pixmap.width() / 2.0,
                    -pixmap.height() / 2.0);
    this->setPos(m_levelSchemeElement->position() * m_schemeItemHelper->schemeScene()->zoom());

    AbstractSchemeItem::elementChanged();
}
