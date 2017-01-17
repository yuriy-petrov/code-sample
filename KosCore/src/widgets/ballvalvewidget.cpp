#include "ballvalvewidget.h"

#include <QtMath>
#include <QPainter>

BallValveWidget::BallValveWidget(QWidget *parent)
    : AbstractValveWidget(parent)
{
    setRotateEnabledRadiusPercent(5);
}


void BallValveWidget::drawValve(QPainter &painter, const QRect &rect) const
{
    const int caseWidth = drawRect().width() * 0.25;

    const double handleHeightPercent = 0.8;
    const double handleArrowHeightPercent = 0.1;
//    const int handleWidth = 30;
    const QColor handleOutlineColor("#000000");
    const QColor handleColor("#454c52");

    const QColor caseColor("#737077");
    const QColor caseOutlineColor("#000000");

    const int screwSize = caseWidth * 0.6;

    const QColor markerColor("#800000");
//    const QColor caseOutlineColor("#000000");

    const QColor helperTextColor("#CCCCCC");

    QFont helperFont;
    QFontMetrics helperFontMetrics(helperFont);

    painter.save();

    painter.setRenderHint(QPainter::Antialiasing, true);

    // корпус
    QRect caseRect = drawRect().adjusted((drawRect().width() - caseWidth) * 0.5,
                                         0,
                                         -(drawRect().width() - caseWidth) * 0.5,
                                         0);
    painter.setPen(QPen(caseOutlineColor, 2));
    painter.setBrush(caseColor);
    painter.drawRect(caseRect);

    // направление вращения
    painter.save();

    QString helperOpenedString = tr("O");
    QString helperClosedString = tr("C");

    painter.setPen(QPen(Qt::black, 1));
    painter.setFont(helperFont);

    double helperHeight = drawRect().width() * 0.5;
    double angle = normalizedAngle(qRadiansToDegrees(drawingAngle(0.0)));
    if((angle > 160.0) && (angle < 200.0)) {
        angle = (openDirection() == AbstractValveWidget::counterClockWise ? 160 : 200.0);
    } else if((angle > -20.0) && (angle < 20.0)) {
        angle = (openDirection() == AbstractValveWidget::counterClockWise ? -20.0 : 20.0);
    }
    angle += 90.0;
    if(openDirection() == AbstractValveWidget::counterClockWise) {
        angle = -angle;
    }

    QTransform transform;
    transform.translate(drawRect().center().x(), drawRect().center().y());
    transform.rotate(angle);
    transform.translate(0, helperHeight);
    transform.rotate(-angle);
    painter.setTransform(transform);

    painter.drawText(-helperFontMetrics.width(helperClosedString) * 0.5,
                     helperFontMetrics.height() * 0.5,
                     helperClosedString);
//    painter.drawRect(-5, -5, 10, 10);

    angle = normalizedAngle(maxAngle());
    if((angle > 240.0) && (angle < 300.0)) {
        angle = (openDirection() == AbstractValveWidget::clockWise ? 240 : 300.0);
    } else if((angle > 60.0) && (angle < 120.0)) {
        angle = (openDirection() == AbstractValveWidget::clockWise ? 60 : 120.0);
    }
    angle += 90.0;

    transform.reset();
    transform.translate(drawRect().center().x(), drawRect().center().y());
    transform.rotate(angle);
    transform.translate(0.0, helperHeight);
    transform.rotate(-angle);
    painter.setTransform(transform);

    painter.drawText(-helperFontMetrics.width(helperOpenedString) * 0.5,
                     helperFontMetrics.height() * 0.5 - 2,
                     helperOpenedString);
//    painter.drawRect(-5, -5, 10, 10);

    painter.restore();

    // ручка
    const double handleLength = drawRect().width() * 0.5;
    const double handleWidth = handleLength * 0.7;
    QPolygon handle(9);
    handle.setPoint(0, 0, -handleLength);
    handle.setPoint(1, handleWidth * 0.5 * 0.6, -handleLength * 0.6);
    handle.setPoint(2, handleWidth * 0.5, -handleLength * 0.25);
    handle.setPoint(3, handleWidth * 0.5, handleLength * 0.35);
    handle.setPoint(4, handleWidth * 0.5 * 0.5, handleLength * 0.6);
    handle.setPoint(5, -handleWidth * 0.5 * 0.5, handleLength * 0.6);
    handle.setPoint(6, -handleWidth * 0.5, handleLength * 0.35);
    handle.setPoint(7, -handleWidth * 0.5, -handleLength * 0.25);
    handle.setPoint(8, -handleWidth * 0.5 * 0.6, -handleLength * 0.6);

    angle = 90.0 + qRadiansToDegrees(drawingAngle());

    transform.reset();
    transform.translate(drawRect().center().x(), drawRect().center().y());
    transform.rotate(angle);
    painter.setTransform(transform);

    painter.setPen(QPen(handleOutlineColor, 2));
    painter.setBrush(handleColor);

    painter.drawPolygon(handle);

    // болт

    QRect screwRect = QRect(-screwSize * 0.5, - screwSize * 0.5, screwSize, screwSize);

    painter.setPen(QPen(handleOutlineColor, 1));
    painter.setBrush(handleColor.darker());

    painter.drawEllipse(screwRect);

    painter.restore();
}
