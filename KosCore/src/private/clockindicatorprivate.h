#ifndef CLOCKINDICATORPRIVATE_H
#define CLOCKINDICATORPRIVATE_H

#include <QObject>
#include <QPainter>

#include "clockindicatorwidget.h"

namespace Ui {
class ClockIndicatorWidget;
}

class ClockIndicatorPrivate : public QObject
{
    Q_OBJECT
    friend class ClockIndicatorWidget;

public:
    explicit ClockIndicatorPrivate(QWidget *parent = 0);
    virtual ~ClockIndicatorPrivate();

    void paint(QPainter& painter, const QRect &rect);

private:
    Ui::ClockIndicatorWidget *ui;

    ClockIndicatorWidget::Type m_type;

    double m_value;
    double m_maxValue;

    QString m_Text;

    double m_axisHeightPointerPercentage;
    double m_valueTickHeight;
    double m_subTickHeight;
    double m_valueTickCount;
    double m_subTickPerValueTickCount;
    double m_tickWidth;
    double m_subtickWidth;

    double m_bottomHeightPercent;

    double m_pointerBottomPercent;
    double m_pointerHeightPercent;
    double m_pointerWidth;

    double m_axisLabelFontSize;
    QFont m_axisLabelFont;
    QFont m_textFont;

    double m_caseWidth;

    QColor m_pointerColor;
    QColor m_dialColor;
    QColor m_bottomColor;
    QColor m_caseColor;
    QColor m_textColor;
    QColor m_axisLabelColor;
    QColor m_axisColor;

    double m_angle;
};

#endif // CLOCKINDICATORPRIVATE_H
