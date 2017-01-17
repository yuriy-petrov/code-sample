#include "PixmapWidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

PixmapWidget::PixmapWidget(QWidget * parent) :
    QWidget(parent)
{
}

PixmapWidget::~PixmapWidget()
{
}

QPixmap PixmapWidget::pixmap() const
{
    return m_pixmap;
}

void PixmapWidget::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    update();
}

void PixmapWidget::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    if (!m_pixmap.isNull() && this->size().isValid())
    {
        QPainter painter(this);
        qreal factor = qMin((qreal)this->width() / (qreal)m_pixmap.width(), (qreal)this->height() / (qreal)m_pixmap.height());

        QPixmap pixmap = m_pixmap.scaled(m_pixmap.size() * factor, Qt::KeepAspectRatio);
        painter.drawPixmap((this->width() - pixmap.width()) / 2.0, (this->height() - pixmap.height()) / 2.0, pixmap.width(), pixmap.height(), pixmap);
    }
}


