#ifndef MANOMETERWIDGETPRIVATE_H
#define MANOMETERWIDGETPRIVATE_H

#include <QObject>
#include <QPainter>

namespace Ui {
class ManometerWidget;
}

class ManometerWidgetPrivate : public QObject
{
    Q_OBJECT
public:
    explicit ManometerWidgetPrivate(QWidget *parent = 0);
    virtual ~ManometerWidgetPrivate();

private:
    void paint(QPainter& painter, const QRect &rect);


private:
    Ui::ManometerWidget *ui;

    double m_value;
    double m_maxValue;

    QString m_Text;

    double m_beginScaleAngle;
    double m_scaleAngleSize;

    double m_axisHeightPercentage;
    double m_valueTickHeight;
    double m_subTickHeight;
    double m_valueTickCount;
    double m_subTickPerValueTickCount;
    double m_tickWidth;
    double m_subtickWidth;

    double m_pointerHeightPercent;
    double m_pointerWidth;

    double m_axisLabelHeightPercent;
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

private:
    friend class ManometerWidget;
};

#endif // MANOMETERWIDGETPRIVATE_H
