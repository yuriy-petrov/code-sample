#include "ElementsMoveWidget.h"

#include "SchemeDataProvider.h"
#include "SchemeElementContainer.h"

#include <QApplication>
#include <QStyle>
#include <QPainter>
#include <QMouseEvent>

ElementsMoveWidget::ElementsMoveWidget(QWidget * parent) :
    QWidget(parent),
    m_schemeDataProvider(NULL)
{
    m_pixmap = QApplication::style()->standardPixmap(QStyle::SP_BrowserReload);
    this->setMinimumSize(m_pixmap.size());
    this->setMaximumSize(m_pixmap.size());
}

ElementsMoveWidget::~ElementsMoveWidget()
{
}

void ElementsMoveWidget::setSchemeDataProvider(SchemeDataProvider * schemeDataProvider)
{
    m_schemeDataProvider = schemeDataProvider;
}

void ElementsMoveWidget::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap.width(), m_pixmap.height(), m_pixmap);
}

void ElementsMoveWidget::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mouseLastPos = event->pos();
        event->accept();
    }
}

void ElementsMoveWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons().testFlag(Qt::LeftButton) && m_schemeDataProvider)
    {
        QPoint dp = event->pos() - m_mouseLastPos;

        foreach (AbstractSchemeElementContainer * elementContainer, m_schemeDataProvider->elementContainers())
        {
            foreach (AbstractSchemeElement * schemeElement, elementContainer->abstractElements())
            {
                if (schemeElement->isHighlighted())
                {
                    schemeElement->move(dp);
                }
            }
        }

        m_mouseLastPos = event->pos();
        event->accept();
    }
}

void ElementsMoveWidget::mouseReleaseEvent(QMouseEvent * event)
{

}

