#include "manometerwidget.h"
#include "ui_manometerwidget.h"
#include "manometerwidgetprivate.h"

ManometerWidget::ManometerWidget(QWidget *parent)
    : QWidget(parent)
    , m_private(new ManometerWidgetPrivate(this))

{

}

ManometerWidget::~ManometerWidget()
{

}

void ManometerWidget::setValue(double value)
{
    m_private->m_value = value;
    update();
}

void ManometerWidget::setMaxValue(double value)
{
    m_private->m_maxValue = value;
    update();
}

void ManometerWidget::setText(const QString &value)
{
    m_private->m_Text = value;
    update();
}

void ManometerWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    m_private->paint(painter, rect());
}
