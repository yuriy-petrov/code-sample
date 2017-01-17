#include "manometerwidgetprivate.h"
#include "ui_manometerwidget.h"

#include <QtMath>

ManometerWidgetPrivate::ManometerWidgetPrivate(QWidget *parent)
    : QObject(parent)
    , ui(new Ui::ManometerWidget)
    , m_value(0.0)
    , m_maxValue(16.0)
    , m_Text("bar")
    , m_beginScaleAngle(130.0)
    , m_scaleAngleSize(280.0)
    , m_axisHeightPercentage(0.73)
    , m_subTickHeight(3)
    , m_valueTickHeight(5)
    , m_valueTickCount(8)
    , m_subTickPerValueTickCount(4)
    , m_tickWidth(2)
    , m_subtickWidth(1)
    , m_pointerHeightPercent(0.7)
    , m_pointerWidth(3.0)
    , m_caseWidth(5)
    , m_axisLabelHeightPercent(0.05)
    , m_axisLabelFont(QFont("Arial", 6))
    , m_textFont(QFont("Arial", 8))
    , m_pointerColor("#464244")
    , m_dialColor("#d4e0e6")//#FFFFF0")
    , m_bottomColor("#333330")
    , m_caseColor("#acacb6")
    , m_textColor("#CC9999")
    , m_axisColor("#7575A3")
    , m_axisLabelColor("#5E7298")
{
    ui->setupUi(parent);
}

ManometerWidgetPrivate::~ManometerWidgetPrivate()
{
    delete ui;
}

void ManometerWidgetPrivate::paint(QPainter &painter, const QRect &rect)
{
    painter.setRenderHints(QPainter::Antialiasing);

    // корпус
    QRect caseRect = rect.adjusted(m_caseWidth, m_caseWidth, -m_caseWidth, -m_caseWidth);
    const int caseWidth = qMin(caseRect.width(), caseRect.height());
    caseRect.setSize(QSize(caseWidth, caseWidth));
    caseRect.moveCenter(rect.center());

    painter.setPen(QPen(m_caseColor, m_caseWidth));
    painter.setBrush(m_dialColor);
    painter.drawEllipse(caseRect);

    // текст
    QFontMetrics textFM(m_axisLabelFont);
    painter.setPen(m_textColor);
    painter.setBrush(Qt::NoBrush);
    painter.drawText(QPoint(caseRect.center().x() - textFM.width(m_Text),
                     caseRect.bottom() - caseRect.height() * m_axisLabelHeightPercent - textFM.height()),
                     m_Text);



    // шкала
    double pointerHeight = m_pointerHeightPercent * caseRect.height() * 0.5 - m_caseWidth;
    double dialheight = m_axisHeightPercentage * caseRect.height() * 0.5 - m_caseWidth;

    QPoint pointerBottom = caseRect.center();

    double angleL = m_beginScaleAngle;
    double angleR = m_beginScaleAngle - m_scaleAngleSize;

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
        QString label = QString::number(tick);

        double angle = 270.0 + angleL + tick * m_scaleAngleSize / m_maxValue;

        QTransform transform;
        transform.translate(pointerBottom.x(), pointerBottom.y());
        transform.rotate(angle);
        painter.setTransform(transform);

        painter.setPen(tickPen);
        painter.drawLine(0, m_valueTickHeight + dialheight,
                         0, dialheight);

        for(int i = 1; (i < m_subTickPerValueTickCount) && (tick + i * subTickStep < m_maxValue); ++i) {
            painter.save();
            double angle = 270.0 + angleL + (tick + i * subTickStep) * m_scaleAngleSize / m_maxValue;

            QTransform transform;
            transform.translate(pointerBottom.x(), pointerBottom.y());
            transform.rotate(angle);
            painter.setTransform(transform);

            painter.setPen(subtickPen);
            painter.drawLine(0, m_subTickHeight + dialheight,
                             0, dialheight);
            painter.restore();
        }

        painter.save();

        transform.translate((double)fm.width(label) * 0.5 * -1.0 + fm.width(label),
                            m_valueTickHeight + dialheight + (double)fm.height() * 0.5);
        transform.rotate(180.0);
        painter.setTransform(transform);

        painter.setPen(m_axisLabelColor);
        painter.drawText(0, 0, label);

        painter.restore();

        tick += tickStep;
    }

    // стрелка
    double angle = 270.0 + angleL + m_value * m_scaleAngleSize / m_maxValue;
    double pointerLength = caseRect.height() * m_pointerHeightPercent * 0.5;
    double pointerTailLength = pointerLength * 0.35;
    double pointerTailWidth = m_pointerWidth * 2.0;

    QPolygon pointer(5);
    pointer.setPoint(0, 0, pointerLength);
    pointer.setPoint(1, m_pointerWidth * 0.5, 0);
    pointer.setPoint(2, pointerTailWidth * 0.5, -pointerTailLength);
    pointer.setPoint(3, -pointerTailWidth * 0.5, -pointerTailLength);
    pointer.setPoint(4, -m_pointerWidth * 0.5, 0);


    QTransform transform;
    transform.translate(pointerBottom.x(), pointerBottom.y());
    transform.rotate(angle);
    painter.setTransform(transform);

    painter.setPen(QPen(m_pointerColor, 1));
    painter.setBrush(m_pointerColor);

    painter.drawPolygon(pointer);

    painter.drawEllipse(-3, -3, 6, 6);
}
