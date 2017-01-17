#include "AbstractSchemeItem.h"

#include "AbstractSchemeElement.h"
#include "SchemeKeys.h"
#include "KosTypes.h"

#include <QApplication>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QPaintDevice>
#include <QPen>
#include <QBrush>
#include <QDebug>

AbstractSchemeItem::AbstractSchemeItem(SchemeItemHelper * schemeItemHelper,
                                       AbstractSchemeElement * element,
                                       QObject * parent) :
    QObject(parent),
    m_schemeItemHelper(schemeItemHelper),
    m_element(element),
    m_graphicsItem(NULL),
    m_formTextItem(NULL)
{
    QObject::connect(element, SIGNAL(changed()),
                     this, SLOT(elementChanged()));
}

SchemeItemHelper * AbstractSchemeItem::schemeItemHelper() const
{
    return m_schemeItemHelper;
}

AbstractSchemeElement * AbstractSchemeItem::element() const
{
    return m_element;
}

void AbstractSchemeItem::setGraphicsItem(QGraphicsItem * graphicsItem)
{
    m_graphicsItem = graphicsItem;
}

void AbstractSchemeItem::drawSelectRect(QPainter * painter, AbstractSchemeElement * element)
{
    if (element->isHighlighted())
    {
        QPen pen(Qt::SolidLine);
        pen.setWidth(KosConsts::HIGHLIGHT_PEN_WIDTH);
        pen.setColor(KosConsts::HIGHLIGHT_PEN_COLOR);

        QBrush brush(Qt::SolidPattern);
        brush.setColor(KosConsts::HIGHLIGHT_RECT_COLOR);

        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawRect(QRect(0, 0, painter->device()->width(), painter->device()->height()));
    }
}

void AbstractSchemeItem::elementChanged()
{
    updateForm();
}

void AbstractSchemeItem::updateForm()
{
    if (!m_element->formText().isEmpty() && m_element->formFontSize() > 0 && m_graphicsItem)
    {
        if (!m_formTextItem)
        {
            m_formTextItem = new QGraphicsPixmapItem(m_graphicsItem);
            m_formTextItem->setVisible(true);
        }

        QFont font = QApplication::font();
        font.setPointSize(m_element->formFontSize());
        QFontMetrics fm(font);

        QRect originalTextRect = fm.boundingRect(m_element->formText());
        QRect textRect = originalTextRect;
        if (m_element->formRotation() == 1 || m_element->formRotation() == 3)
        {
            textRect.setWidth(originalTextRect.height());
            textRect.setHeight(originalTextRect.width());
        }

        QImage image(originalTextRect.width() + 2, originalTextRect.height() + 2, QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter painter(&image);
        painter.setFont(font);
        painter.setOpacity(1);
        painter.setBrush(QBrush(QColor(Qt::black)));
        painter.setPen(QPen(QColor(Qt::black)));
        painter.drawText(QRect(0, 0, originalTextRect.width() + 2, originalTextRect.height() + 2), Qt::AlignCenter, m_element->formText());

        qreal angle = 0;
        switch (m_element->formRotation())
        {
            case 0: angle = 0; break;
            case 1: angle = 90; break;
            case 2: angle = 180; break;
            case 3: angle = 270; break;
        }
        QPixmap pixmap = QPixmap::fromImage(image.transformed(QTransform().rotate(angle)));
        m_formTextItem->setPixmap(pixmap);

        int x = 0, y = 0;
        switch (m_element->formPositionX())
        {
            case KosTypes::Left: x = -m_graphicsItem->boundingRect().width() / 2.0; break;
            case KosTypes::HCenter: x = 0; break;
            case KosTypes::Right: x = m_graphicsItem->boundingRect().width() / 2.0; break;
        }
        switch (m_element->formPositionY())
        {
            case KosTypes::Top: y = -m_graphicsItem->boundingRect().height() / 2.0; break;
            case KosTypes::VCenter: y = 0; break;
            case KosTypes::Bottom: y = m_graphicsItem->boundingRect().height() / 2.0; break;
        }

        switch (m_element->formAlignmentX())
        {
            case KosTypes::Left: x -= m_formTextItem->boundingRect().width(); break;
            case KosTypes::HCenter: x -= m_formTextItem->boundingRect().width() / 2.0; break;
            case KosTypes::Right: break;
        }
        switch (m_element->formAlignmentY())
        {
            case KosTypes::Top: y -= m_formTextItem->boundingRect().height(); break;
            case KosTypes::VCenter: y -= m_formTextItem->boundingRect().height() / 2.0; break;
            case KosTypes::Bottom: break;
        }

        m_formTextItem->setPos(QPointF(x, y) + m_element->formOffset());
    }
    else
    {
        if (m_formTextItem)
        {
            delete m_formTextItem;
            m_formTextItem = NULL;
        }
    }
}
