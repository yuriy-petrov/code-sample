#include "handvalvewidget.h"

#include <QtMath>
#include <QPainter>

HandValveWidget::HandValveWidget(QWidget *parent)
    : AbstractValveWidget(parent)
{
    setRotateEnabledRadiusPercent(10);
}

void HandValveWidget::drawValve(QPainter &painter, const QRect &rect) const
{
    const int caseWidth = drawRect().width() * 0.25;

    const QColor handleOutlineColor("#000000");
    const QColor handleColor("#454c52");

    const QColor caseColor("#737077");
    const QColor caseOutlineColor("#000000");

    const QColor markerColor("#800000");
//    const QColor caseOutlineColor("#000000");

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

    double angle = qRadiansToDegrees(drawingAngle()) - 90.0;
    QTransform transform;
    transform.translate(drawRect().center().x(), drawRect().center().y());
    transform.rotate(angle);
    painter.setTransform(transform);

    // ручка
    QRect handleRect(-drawRect().width() * 0.8 * 0.5, -drawRect().width() * 0.8 * 0.5,
                     drawRect().width() * 0.8, drawRect().width() * 0.8);

    painter.setPen(QPen(handleOutlineColor, 2));
    painter.setBrush(handleColor);
    painter.drawEllipse(handleRect);

    // маркер
    QRect markerRect(-3, 0, 6, handleRect.height() / 2);

    painter.setPen(Qt::NoPen);
    painter.setBrush(markerColor);

    painter.drawRect(markerRect);

    // направление вращения
    QFont helperFont;
    QFontMetrics helperFontMetrics(helperFont);
    QColor helperColor("#FFFFCC");
    QString helperOpenedString = tr("O");
    QString helperClosedString = tr("C");

    painter.setFont(helperFont);
    painter.setPen(QPen(helperColor, 1));

    painter.save();

    QTransform t = painter.transform();
    t.rotate(-40.0);
    t.translate(0, handleRect.height() * 0.45);
    t.rotate(180.0);
    painter.setTransform(t);

    painter.drawText(-helperFontMetrics.width(helperOpenedString) * 0.5,
                     helperFontMetrics.height() * 0.5,
                     helperOpenedString);

    painter.restore();
    painter.save();

    t = painter.transform();
    t.rotate(40.0);
    t.translate(0, handleRect.height() * 0.45);
    t.rotate(180.0);
    painter.setTransform(t);    t.rotate(80.0);

    painter.drawText(-helperFontMetrics.width(helperClosedString) * 0.5,
                     helperFontMetrics.height() * 0.5,
                     helperClosedString);

    painter.restore();

    // болт

    double screwWidth = 35;
    QRect screwRect(-screwWidth * 0.5, -screwWidth * 0.5, screwWidth, screwWidth);

    painter.setPen(QPen(handleOutlineColor, 1));
    painter.setBrush(handleColor.darker());

    painter.drawEllipse(screwRect);


    painter.restore();
}
