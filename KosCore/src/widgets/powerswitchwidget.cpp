#include "powerswitchwidget.h"

#include <QtMath>
#include <QPainter>

PowerSwitchWidget::PowerSwitchWidget(QWidget *parent)
    : AbstractValveWidget(parent)
{
    setRotateEnabledRadiusPercent(5);
    setEndAngle(146.0);
    setRotatesCount(70.0 / 360.0);
    setOpenDirection(AbstractValveWidget::counterClockWise);
    powerOff();

    connect(this, &AbstractValveWidget::changed,
            this, &PowerSwitchWidget::changed);
}

void PowerSwitchWidget::powerOn()
{
    open();
}

void PowerSwitchWidget::powerOff()
{
    close();
}

bool PowerSwitchWidget::isPowerOn() const
{
    return isOpen();
}

void PowerSwitchWidget::drawValve(QPainter &painter, const QRect &rect) const
{
    const int caseWidth = drawRect().width() * 0.5;

//    const double handleHeightPercent = 0.8;
//    const double handleArrowHeightPercent = 0.1;
//    const int handleWidth = 30;
    const QColor handleOutlineColor("#3D3D3D");
    const QColor handleColor("#4C4C4C");

    const QColor caseColor("#595959");
    const QColor caseOutlineColor("#474747");

    const QColor onlayColor("#C6CDCD");
    const QColor onlayOutlineColor("#C6CDCD");

    const QColor labelColor("#7E6969");

    const QColor markerColor("#800000");
//    const QColor caseOutlineColor("#000000");

    painter.save();

    painter.setRenderHint(QPainter::Antialiasing, true);

    // корпус
    QRect caseRect(0, 0, caseWidth, caseWidth);
    caseRect.moveCenter(drawRect().center());

    painter.setPen(QPen(caseOutlineColor, 2));
    painter.setBrush(caseColor);
    painter.drawRect(caseRect);

    // метки
    double riskLength = 5;

    QString label;
    QFont labelFont("Arial", 7);
    QFontMetrics fm(labelFont);

    painter.setPen(labelColor);
    painter.setFont(labelFont);

    label = tr("Off");
    painter.drawText(caseRect.left() - fm.width(label) - riskLength,
                     caseRect.top() + fm.height(),
                     label);
    label = tr("On");
    painter.drawText(caseRect.left() - fm.width(label) - riskLength,
                     caseRect.bottom() - 5,
                     label);

    // накладка на корпус
    painter.setPen(QPen(caseColor, 1));
    painter.setBrush(onlayColor);
    painter.drawEllipse(caseRect.adjusted(3, 3, -3, -3));


    // ручка
    double angle = 90.0 + qRadiansToDegrees(drawingAngle());

    QTransform transform;
    transform.translate(caseRect.center().x(), caseRect.center().y());
    transform.rotate(angle);
    painter.setTransform(transform);

    double handleLength = drawRect().width() * 0.7;
    double handleWidth = handleLength * 0.3;

    double markerLength = handleLength * 0.25;
    double markerWidth = handleWidth * 0.2;
    double markerShift = markerLength * 0.2;


    QRect handleRect(-handleWidth * 0.5, -handleLength * 0.4,
                     handleWidth, handleLength);

    painter.setPen(QPen(handleOutlineColor, 3));
    painter.setBrush(handleColor);
    painter.drawRect(handleRect);

    painter.setPen(QPen(handleOutlineColor, 2));
    painter.setBrush(onlayColor);
    painter.drawRect(
                handleRect.adjusted((handleWidth - markerWidth) * 0.5, markerShift,
                                    -(handleWidth - markerWidth) * 0.5, markerShift - (handleLength - markerLength))
                );

    painter.restore();
}

void PowerSwitchWidget::changed(int closurePercent, bool isFinal)
{
    if(isFinal) {
        emit stateChanged(isPowerOn());
    }
}
