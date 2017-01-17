#include "LEDWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

LEDWidget::LEDWidget(QWidget *parent) :
    QWidget(parent)
{
}

LEDWidget::~LEDWidget()
{

}

void LEDWidget::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
}
