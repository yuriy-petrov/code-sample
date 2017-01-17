#include "ICimrexButton.h"

#include <QPainter>
#include <QVariant>
#include <QDebug>
ICimrexButton::ICimrexButton(QWidget *parent) :
    QPushButton(parent)
{
    QPixmap pixmap = property("pixmap").value<QPixmap>();
    pixmap.load(":/images/SimpleDownButton.png");
    qDebug() << "DRAW PIXMAP" << pixmap;
    setProperty("pixmap", pixmap);
}

void ICimrexButton::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    QPixmap pixmap(":/images/SimpleDownButton.png");
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(0,0, this->width(), this->height(), pixmap);
}
