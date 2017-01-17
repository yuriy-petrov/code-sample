#include <QPaintEvent>

#include "clockindicatorwidget.h"
#include "ui_clockindicatorwidget.h"
#include "clockindicatorprivate.h"

ClockIndicatorWidget::ClockIndicatorWidget(QWidget *parent)
    : QWidget(parent)
    , m_private(new ClockIndicatorPrivate(parent))
{
}

ClockIndicatorWidget::~ClockIndicatorWidget()
{
}

void ClockIndicatorWidget::setType(ClockIndicatorWidget::Type type)
{
    m_private->m_type = type;
    update();
}

ClockIndicatorWidget::Type ClockIndicatorWidget::type() const
{
    return m_private->m_type;
}

void ClockIndicatorWidget::setValue(double value)
{
    m_private->m_value = value;
    update();
}

void ClockIndicatorWidget::setMaxValue(double value)
{
    m_private->m_maxValue = value;
    update();
}

void ClockIndicatorWidget::setText(const QString &value)
{
    m_private->m_Text = value;
    update();
}

void ClockIndicatorWidget::setTextFont(const QFont &font)
{
    m_private->m_textFont = font;
    update();
}

void ClockIndicatorWidget::setTextColor(const QColor &color)
{
    m_private->m_textColor = color;
    update();
}

void ClockIndicatorWidget::setCaseWidth(double value)
{
    m_private->m_caseWidth = value;
    update();
}

void ClockIndicatorWidget::setCaseColor(const QColor &color)
{
    m_private->m_caseColor = color;
    update();
}

void ClockIndicatorWidget::setBottomHeightPercent(int value)
{
    m_private->m_bottomHeightPercent = (double)value / 100.0;
    update();
}

void ClockIndicatorWidget::setBottomColor(const QColor &color)
{
    m_private->m_bottomColor = color;
    update();
}

void ClockIndicatorWidget::setPointerWidthPix(int value)
{
    m_private->m_pointerWidth = value;
    update();
}

void ClockIndicatorWidget::setPointerBottomPercent(int value)
{
    m_private->m_pointerBottomPercent = (double)value / 100.0;
    update();
}

void ClockIndicatorWidget::setPointerHeightPercent(int value)
{
    m_private->m_pointerHeightPercent = (double)value / 100.0;
    update();
}

void ClockIndicatorWidget::setPointerColor(const QColor &color)
{
    m_private->m_pointerColor = color;
    update();
}

void ClockIndicatorWidget::setDialColor(const QColor &color)
{
    m_private->m_dialColor = color;
    update();
}

void ClockIndicatorWidget::setAxisHeightPercent(int value)
{
    m_private->m_axisHeightPointerPercentage = (double)value / 100.0;
    update();
}

void ClockIndicatorWidget::setTickHeightPix(int value)
{
    m_private->m_valueTickHeight = value;
    update();
}

void ClockIndicatorWidget::setSubtickHeightPix(int value)
{
    m_private->m_subTickHeight = value;
    update();
}

void ClockIndicatorWidget::setTickWidthPix(int value)
{
    m_private->m_tickWidth = value;
    update();
}

void ClockIndicatorWidget::setSubtickWidthPix(int value)
{
    m_private->m_subtickWidth = value;
    update();
}

void ClockIndicatorWidget::setTicksCount(int value)
{
    m_private->m_valueTickCount = value;
    update();
}

void ClockIndicatorWidget::setSubticksPerTickCount(int value)
{
    m_private->m_subTickPerValueTickCount = value;
    update();
}

void ClockIndicatorWidget::setAxisLabelsFont(const QFont &font)
{
    m_private->m_axisLabelFont = font;
    update();
}

void ClockIndicatorWidget::setAxisTicksColor(const QColor &color)
{
    m_private->m_axisColor = color;
    update();
}

void ClockIndicatorWidget::setAxisLabelsColor(const QColor &color)
{
    m_private->m_axisLabelColor = color;
    update();
}

void ClockIndicatorWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    m_private->paint(painter, rect());
}
