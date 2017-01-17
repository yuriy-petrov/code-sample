#include "TextSchemeItem.h"

#include "TextSchemeElement.h"
#include "SchemeScene.h"
#include "StringsKeys.h"
#include "SettingsStorage.h"
#include "SchemeItemHelper.h"

#include <math.h>
#include <QApplication>
#include <QFontMetrics>
#include <QPainter>

TextSchemeItem::TextSchemeItem(SchemeItemHelper * schemeItemHelper,
                               TextSchemeElement * textSchemeElement,
                               QGraphicsItem * parentItem) :
    AbstractSchemeItem(schemeItemHelper, textSchemeElement),
    QGraphicsItem(parentItem),
    m_pixmapItem(new QGraphicsPixmapItem(this)),
    m_textSchemeElement(textSchemeElement)
{
    this->setAcceptHoverEvents(true);

    elementChanged();

    m_schemeItemHelper->settingsStorage()->setHandler(SettingsKeys::SCHEME_FONT_FAMILY, this, SLOT(elementChanged()));
    m_schemeItemHelper->settingsStorage()->setHandler(SettingsKeys::SCHEME_FONT_SIZE, this, SLOT(elementChanged()));

    QObject::connect(m_textSchemeElement, SIGNAL(changed()),
                     this, SLOT(elementChanged()));

    this->setGraphicsItem(this);
}

QPixmap TextSchemeItem::textPixmap(TextSchemeElement * textSchemeElement, const QFont & font)
{
    QFont cfont = font;
    cfont.setPointSize(textSchemeElement->fontSize());
    QFontMetrics fm(cfont);

    qreal margin = 3;

    QRect textRect = fm.boundingRect(textSchemeElement->text());
    QRectF frameRect;
    if (textSchemeElement->frameType() == TextSchemeElement::FrameType::Rect)
    {
        frameRect = QRectF(margin, margin, textRect.width() + 2*margin, textRect.height() + 2*margin);
    }
    else if (textSchemeElement->frameType() == TextSchemeElement::FrameType::Ellipse)
    {
        qreal a = textRect.width() / 2.0 + margin;
        qreal b = textRect.height() / 2.0 + margin;
        qreal radius = sqrt(a*a + b*b);
        frameRect = QRectF(margin, margin, 2*radius, 2*radius);
    }

    QRectF totalRect = QRectF(0, 0, frameRect.width() + 2*margin, frameRect.height() + 2*margin);

    QImage image(totalRect.size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setBrush(QBrush(Qt::white));
    painter.setFont(cfont);
    if (textSchemeElement->frameVisible())
    {
        if (textSchemeElement->frameType() == TextSchemeElement::FrameType::Rect)
        {
            painter.drawRect(frameRect);
        }
        else if (textSchemeElement->frameType() == TextSchemeElement::FrameType::Ellipse)
        {
            painter.drawEllipse(frameRect);
        }
    }
    painter.drawText(totalRect, Qt::AlignCenter, textSchemeElement->text());

    AbstractSchemeItem::drawSelectRect(&painter, textSchemeElement);

    QPixmap pixmap;
    pixmap.convertFromImage(image);

    if (textSchemeElement->rotation() != 0)
    {
        pixmap = pixmap.transformed(QTransform().rotate(textSchemeElement->rotation()));
    }

    return pixmap;
}

QRectF TextSchemeItem::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void TextSchemeItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void TextSchemeItem::updateZoom()
{
    this->setPos(m_textSchemeElement->position() * m_schemeItemHelper->schemeScene()->zoom());
}

void TextSchemeItem::elementChanged()
{
    this->setToolTip(m_textSchemeElement->tooltip());

    m_pixmapItem->setPixmap(TextSchemeItem::textPixmap(m_textSchemeElement, QFont(m_schemeItemHelper->settingsStorage()->value(SettingsKeys::SCHEME_FONT_FAMILY).toString(), m_schemeItemHelper->settingsStorage()->value(SettingsKeys::SCHEME_FONT_SIZE).toInt())));
    m_pixmapItem->setOffset(QPointF(-m_pixmapItem->pixmap().width() / 2.0, -m_pixmapItem->pixmap().height() / 2.0) + m_textSchemeElement->screenOffset());

    updateZoom();
    AbstractSchemeItem::elementChanged();
}
