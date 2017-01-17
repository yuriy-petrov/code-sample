#include "ValveSchemeItem.h"

#include "ValveSchemeElement.h"
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
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QSvgRenderer>

ValveSchemeItem::ValveSchemeItem(SchemeItemHelper * schemeItemHelper,
                                 ValveSchemeElement * valveSchemeElement,
                                 QGraphicsItem * parentItem) :
    AbstractSchemeItem(schemeItemHelper, valveSchemeElement),
    QGraphicsPixmapItem(parentItem),
    m_valveSchemeElement(valveSchemeElement)
{
    this->setAcceptHoverEvents(true);

    elementChanged();

    m_schemeItemHelper->settingsStorage()->setHandler(SettingsKeys::SCHEME_FONT_FAMILY, this, SLOT(elementChanged()));
    m_schemeItemHelper->settingsStorage()->setHandler(SettingsKeys::SCHEME_FONT_SIZE, this, SLOT(elementChanged()));

    QObject::connect(m_schemeItemHelper->schemeScene()->canvasSchemeItem()->canvasSchemeElement(), SIGNAL(changed()),
                     this, SLOT(elementChanged()));
    QObject::connect(m_valveSchemeElement, SIGNAL(changed()),
                     this, SLOT(elementChanged()));

    this->setGraphicsItem(this);
}

QPixmap ValveSchemeItem::valvePixmap(ValveSchemeElement * valveSchemeElement, qreal factor, const QFont & font)
{
    QImage image;
    QSvgRenderer svgRenderer;
    if (svgRenderer.load(QString(":/images/valveSchemeElements/%1.svg").arg(valveSchemeElement->valveType())))
    {
        image = QImage(svgRenderer.defaultSize() * factor, QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter painter(&image);
        svgRenderer.render(&painter);
    }
    else
    {
        Q_ASSERT(image.load(QString(":/images/valveSchemeElements/%1.png").arg(valveSchemeElement->valveType())));
        QTransform transform;
        transform.scale(factor, factor);
        image = image.transformed(transform);
    }

    for (int x = 0; x < image.size().width(); ++x)
    {
        for (int y = 0; y < image.size().height(); ++y)
        {
            if (image.pixel(x, y) == KosConsts::MAGIC_COLOR.rgba())
            {
                image.setPixel(x, y, valveSchemeElement->closePercentage() == 100 ? KosTypesHelper::instance()->substanceTypeColors()[valveSchemeElement->substanceType()].rgba() : KosConsts::OPENED_VALVE_COLOR.rgba());
            }
        }
    }

    if (valveSchemeElement->rotation() != 0)
    {
        image = image.transformed(QTransform().rotate(valveSchemeElement->rotation()));
    }

    if (valveSchemeElement->mirroredHorizontal() || valveSchemeElement->mirroredVertical())
    {
        image = image.mirrored(valveSchemeElement->mirroredHorizontal(), valveSchemeElement->mirroredVertical());
    }

    if (!valveSchemeElement->isValid())
    {
        drawInvalid(valveSchemeElement, &image);
    }

    QPainter painter(&image);
    AbstractSchemeItem::drawSelectRect(&painter, valveSchemeElement);

    QPixmap pixmap;
    pixmap = pixmap.fromImage(image);

    if (valveSchemeElement->closePercentageVisible())
    {
        pixmap = drawClosePercentage(valveSchemeElement, pixmap, font);
    }

    return pixmap;
}

void ValveSchemeItem::updateZoom()
{
    this->setPos(m_valveSchemeElement->position() * m_schemeItemHelper->schemeScene()->zoom());
    AbstractSchemeItem::elementChanged();
}

void ValveSchemeItem::elementChanged()
{
    this->setToolTip(m_valveSchemeElement->tooltip());

    QPixmap pixmap = ValveSchemeItem::valvePixmap(m_valveSchemeElement, m_schemeItemHelper->schemeScene()->canvasSchemeItem()->canvasSchemeElement()->valveFactor(), QFont(m_schemeItemHelper->settingsStorage()->value(SettingsKeys::SCHEME_FONT_FAMILY).toString(), m_schemeItemHelper->settingsStorage()->value(SettingsKeys::SCHEME_FONT_SIZE).toInt()));

    this->setPixmap(pixmap);
    this->setOffset(-pixmap.width() / 2.0,
                    -pixmap.height() / 2.0);
    updateZoom();
}

void ValveSchemeItem::drawInvalid(ValveSchemeElement * valveSchemeElement, QPaintDevice * device)
{
    Q_UNUSED(valveSchemeElement);

    qreal dx = device->width() / 4.0;
    qreal dy = device->height() / 4.0;

    QPainter painter(device);
    QPolygonF polygon;

    polygon.append(QPointF(dx, 0));
    polygon.append(QPointF(dx * 2, dy));
    polygon.append(QPointF(dx * 3, 0));
    polygon.append(QPointF(dx * 4, dy));
    polygon.append(QPointF(dx * 3, dy * 2));
    polygon.append(QPointF(dx * 4, dy * 3));
    polygon.append(QPointF(dx * 3, dy * 4));
    polygon.append(QPointF(dx * 2, dy * 3));
    polygon.append(QPointF(dx, dy * 4));
    polygon.append(QPointF(0, dy * 3));
    polygon.append(QPointF(dx, dy * 2));
    polygon.append(QPointF(0, dy));

    QBrush brush(Qt::SolidPattern);
    brush.setColor(QColor(255, 0, 0, 255));
    painter.setBrush(brush);

    QPen pen(Qt::SolidLine);
    pen.setColor(QColor(192, 0, 0, 255));
    painter.setPen(pen);

    painter.drawPolygon(polygon);
}

QPixmap ValveSchemeItem::drawClosePercentage(ValveSchemeElement * valveSchemeElement, const QPixmap & pixmap, const QFont & font)
{
    QString text = QString("%1%").arg(valveSchemeElement->closePercentage());
    QRect textRect = QFontMetrics(font).boundingRect(text);

    qreal margin = 3;
    QRect totalRect(QPoint(valveSchemeElement->closePercentagePositionX(), valveSchemeElement->closePercentagePositionY()),
                QSize(textRect.width() + margin*2.0, textRect.height() + margin*2.0));

    int dx = 0;
    if (totalRect.left() < 0)
    {
        dx = abs(totalRect.left());
    }
    if (totalRect.right() > pixmap.width())
    {
        dx = qMax(dx, totalRect.right() - pixmap.width());
    }
    int dy = 0;
    if (totalRect.top() < 0)
    {
        dy = abs(totalRect.top());
    }
    if (totalRect.bottom() > pixmap.height())
    {
        dy = qMax(dy, totalRect.bottom() - pixmap.height());
    }

    QImage newImage(QSize(pixmap.size() + 2*QSize(dx + margin, dy + margin)), QImage::Format_ARGB32);
    newImage.fill(Qt::transparent);
    QPainter painter(&newImage);

    painter.setOpacity(1);
    painter.setFont(font);

    QBrush brush(Qt::SolidPattern);
    brush.setColor(QColor(Qt::white));
    painter.setBrush(brush);

    QPen pen(Qt::SolidLine);
    pen.setColor(QColor(Qt::black));
    painter.setPen(pen);

    painter.translate(dx + margin, dy + margin);
    painter.drawPixmap(0, 0, pixmap);
    painter.drawRect(totalRect);

    pen.setColor(QColor(Qt::black));
    painter.setPen(pen);

    painter.drawText(totalRect, Qt::AlignCenter, text);
    QPixmap newPixmap;
    newPixmap.convertFromImage(newImage);
    return newPixmap;
}
