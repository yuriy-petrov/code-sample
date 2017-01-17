#include <QtMath>

#include "clockindicatorprivate.h"
#include "ui_clockindicatorwidget.h"

ClockIndicatorPrivate::ClockIndicatorPrivate(QWidget *parent)
    : QObject(parent)
    , ui(new Ui::ClockIndicatorWidget)
    , m_type(ClockIndicatorWidget::Classic)
    , m_value(0.0)
    , m_maxValue(250.0)
    , m_Text("U, Volt")
    , m_axisHeightPointerPercentage(0.9)
    , m_subTickHeight(3)
    , m_valueTickHeight(5)
    , m_valueTickCount(5)
    , m_subTickPerValueTickCount(5)
    , m_tickWidth(2)
    , m_subtickWidth(1)
    , m_bottomHeightPercent(0.4)
    , m_pointerBottomPercent(0.3)
    , m_pointerHeightPercent(0.7)
    , m_caseWidth(5)
    , m_axisLabelFont(QFont("Arial", 6))
    , m_textFont(QFont("Arial", 8))
    , m_pointerColor("#464244")
    , m_dialColor("#FFFFF0")
    , m_bottomColor("#333330")
    , m_caseColor("black")
    , m_textColor("#CC9999")
    , m_axisColor("#7575A3")
    , m_axisLabelColor("#5E7298")
{
    ui->setupUi(parent);
}

ClockIndicatorPrivate::~ClockIndicatorPrivate()
{
    delete ui;
}

void ClockIndicatorPrivate::paint(QPainter &painter, const QRect& rect)
{
    painter.save();

    painter.setRenderHints(QPainter::Antialiasing);

    QRect caseRect = rect.adjusted(3, 3, -3, -3);

    switch(m_type) {
        case ClockIndicatorWidget::Classic:
        {
            QRect bottomRect = caseRect.adjusted(0, caseRect.height() * (1.0 - m_bottomHeightPercent), 0, 0);

            // область шкалы
            QRect dialRect = caseRect.adjusted(0, 0, 0, -caseRect.height() * m_bottomHeightPercent);
            painter.setPen(QPen(m_dialColor, 1));
            painter.setBrush(m_dialColor);
            painter.drawRect(dialRect);

            // текст
            QRect textRect = caseRect;
            textRect.setHeight(QFontMetrics(m_textFont).height() + 3);
            textRect.moveTop(bottomRect.top() - textRect.height() - caseRect.height() * 0.03);
            painter.setPen(m_textColor);
            painter.setBrush(Qt::NoBrush);
            painter.drawText(textRect, m_Text, QTextOption(Qt::AlignCenter));



            // шкала

            double pointerHeight = m_pointerHeightPercent * caseRect.height() - m_caseWidth;
            double dialheight = pointerHeight * m_axisHeightPointerPercentage - m_caseWidth;

            QRect axisRect = dialRect.adjusted(3, dialRect.height() - dialheight, -3, 0);
            QPoint pointerBottom = QPoint(axisRect.center().x(), axisRect.bottom() + bottomRect.height() * m_pointerBottomPercent);

            double angleL = qAcos((caseRect.height() / 2.0) / pointerHeight);
            double angleR = qDegreesToRadians(180.0) + angleL;

            double valueTickAngle = (angleR - angleR) / m_valueTickCount;
            double subValueTickAngle = valueTickAngle / m_subTickPerValueTickCount;

            double tick = 0;
            double tickStep = m_maxValue / m_valueTickCount;
            double subTickStep = tickStep / m_subTickPerValueTickCount;

            QPen tickPen(m_axisColor, m_tickWidth);
            QPen subtickPen(m_axisColor, m_subtickWidth);

            painter.setPen(m_axisColor);
            painter.setBrush(Qt::NoBrush);
            painter.setFont(m_axisLabelFont);
            QFontMetrics fm(m_axisLabelFont);

            while (tick <= m_maxValue) {
                QString label = QString::number((int)tick);

                double angle = angleL + tick * (qDegreesToRadians(180.0) - 2.0 * angleL) / m_maxValue;

                QPoint p1 = QPoint(pointerBottom.x() - (m_valueTickHeight + dialheight) * qCos(angle),
                                   pointerBottom.y() - (m_valueTickHeight + dialheight) * qSin(angle));
                QPoint p2 = QPoint(pointerBottom.x() - dialheight * qCos(angle),
                                   pointerBottom.y() - dialheight * qSin(angle));
                double alpha = qAtan((double)fm.width(label) * 0.5 / dialheight) * 0.5;
                QPoint p3 = QPoint(pointerBottom.x() - (dialheight - 3 - fm.width(label)) * qCos(angle + alpha),
                                   pointerBottom.y() - (dialheight - 3 - fm.width(label)) * qSin(angle + alpha));

                painter.setPen(tickPen);
                painter.drawLine(p1, p2);

                QTransform transform;
                transform.translate(p3.x(), p3.y());
                transform.rotateRadians(qDegreesToRadians(180.0) + angle);

                painter.save();
                painter.setPen(m_axisLabelColor);
                painter.setTransform(transform);
                painter.drawText(QPoint(0, 0), label);
                painter.restore();

                for(int i = 1; (i < m_subTickPerValueTickCount) && (tick + i * subTickStep < m_maxValue); ++i) {
                    double angle = angleL + (tick + i * subTickStep) * (qDegreesToRadians(180.0) - 2.0 * angleL) / m_maxValue;

                    QPoint p1 = QPoint(pointerBottom.x() - (m_subTickHeight + dialheight) * qCos(angle),
                                       pointerBottom.y() - (m_subTickHeight + dialheight) * qSin(angle));
                    QPoint p2 = QPoint(pointerBottom.x() - dialheight * qCos(angle),
                                       pointerBottom.y() - dialheight * qSin(angle));
                    painter.setPen(subtickPen);
                    painter.drawLine(p1, p2);
                }

                tick += tickStep;
            }

            // стрелка
            painter.setPen(m_pointerColor);
            painter.setBrush(Qt::NoBrush);

            double valueAngle = angleL + m_value * (qDegreesToRadians(180.0) - 2.0 * angleL) / m_maxValue;

            QPoint p2 = QPoint(pointerBottom.x() - (pointerHeight - m_caseWidth - 5) * qCos(valueAngle),
                               pointerBottom.y() - (pointerHeight - m_caseWidth - 5) * qSin(valueAngle));

            painter.drawLine(pointerBottom, p2);

            // нижняя часть
            painter.setPen(QPen(m_bottomColor, 1));
            painter.setBrush(m_bottomColor);
            painter.drawRect(bottomRect);

            break;
        }

        case ClockIndicatorWidget::HYSTAT_ANGLED:
        {
            // область шкалы
            QRect dialRect = caseRect;
            painter.setPen(QPen(m_dialColor, 1));
            painter.setBrush(m_dialColor);
            painter.drawRect(dialRect);

            // текст
            int textHeight = QFontMetrics(m_textFont).height();
            painter.setPen(m_textColor);
            painter.setBrush(Qt::NoBrush);
            painter.drawText(dialRect.left() + textHeight * 1.5,
                             dialRect.top() + textHeight * 2.5,
                             m_Text);

            // шкала
            double pointerShift = 20.0;
            QPoint pointerBottom = QPoint(dialRect.bottomRight().x() - pointerShift,
                                          dialRect.bottomRight().y() - pointerShift);
            double pointerHeight = m_pointerHeightPercent * (caseRect.height() - m_caseWidth - pointerShift);

            double angleL = 0.0;
            double angleR = 90.0;

            double valueTickAngle = (angleR - angleR) / m_valueTickCount;
            double subValueTickAngle = valueTickAngle / m_subTickPerValueTickCount;

            double tick = 0;
            double tickStep = m_maxValue / m_valueTickCount;
            double subTickStep = tickStep / m_subTickPerValueTickCount;

            double valueToAngle = (angleR - angleL) / m_maxValue;

            QPen tickPen(m_axisColor, m_tickWidth);
            QPen subtickPen(m_axisColor, m_subtickWidth);

            painter.setFont(m_axisLabelFont);
            QFontMetrics fontMetrics(m_axisLabelFont);

            painter.setPen(m_axisColor);
            painter.setBrush(Qt::NoBrush);
            painter.setFont(m_axisLabelFont);
            QFontMetrics fm(m_axisLabelFont);

            while (tick <= m_maxValue) {
                QString label = QString::number((int)tick);

                double angle = 90.0 + angleL + tick * valueToAngle;

                QTransform transform;
                transform.translate(pointerBottom.x(), pointerBottom.y());
                transform.rotate(angle);
                transform.translate(0, pointerHeight);
                painter.setTransform(transform);

                painter.setPen(tickPen);
                painter.drawLine(0, 0, 0, -m_valueTickHeight);

                painter.save();
                transform.reset();
                transform.translate(pointerBottom.x(), pointerBottom.y());
                transform.rotate(angle);
                transform.translate(0, pointerHeight - 15);
                transform.rotate(-angle);
                painter.setTransform(transform);

                painter.setPen(m_axisLabelColor);
                painter.drawText(-fontMetrics.width(label) * 0.5,
                                 fontMetrics.height() * 0.5,
                                 label);
                painter.restore();

                if(tick < m_maxValue) {
                    // полушаги
                    angle += tickStep * valueToAngle * 0.5;
                    transform.reset();
                    transform.translate(pointerBottom.x(), pointerBottom.y());
                    transform.rotate(angle);
                    transform.translate(0, pointerHeight);
                    painter.setTransform(transform);

                    painter.setPen(subtickPen);
                    painter.drawLine(0, 0, 0, -m_valueTickHeight);
                }

                for(int i = 1; (i < m_subTickPerValueTickCount) && (tick + i * subTickStep < m_maxValue); ++i) {
                    painter.save();
                    double angle = 90.0 + angleL + (tick + i * subTickStep) * valueToAngle;

                    QTransform transform;
                    transform.translate(pointerBottom.x(), pointerBottom.y());
                    transform.rotate(angle);
                    transform.translate(0, pointerHeight);
                    painter.setTransform(transform);

                    painter.setPen(subtickPen);
                    painter.drawLine(0, 0, 0, -m_subTickHeight);
                    painter.restore();
                }

                tick += tickStep;
            }

            // стрелка
            double angle = 90.0 + angleL + m_value * valueToAngle;
            QTransform transform;
            transform.translate(pointerBottom.x(), pointerBottom.y());
            transform.rotate(angle);
            painter.setTransform(transform);

            painter.setPen(QPen(m_pointerColor, 1));
            painter.setBrush(Qt::NoBrush);

            painter.drawLine(0, 0, 0, pointerHeight);

            // крепление стрелки

            painter.setTransform(QTransform());
            painter.setBrush(m_pointerColor);
            painter.drawEllipse(pointerBottom, 7, 7);

            break;
        }
    }

    painter.setTransform(QTransform());

    // корпус
    painter.setPen(QPen(m_caseColor, m_caseWidth));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(caseRect, 5, 5);

    painter.restore();
}
