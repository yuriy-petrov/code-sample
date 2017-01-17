#include "abstractvalvewidget.h"
#include "ui_abstractvalvewidget.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QtMath>

#include <log.h>

AbstractValveWidget::AbstractValveWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AbstractValveWidget)
    , m_Direction(clockWise)
    , m_currentAngle(0.0)
    , m_endAngle(0.0)
    , m_maxAngle(720.0)
    , m_rotateEanbledRadius(30)
    , m_isGrabbed(false)
    , m_grabAngleThr(30.0)
{
    ui->setupUi(this);
}

AbstractValveWidget::~AbstractValveWidget()
{
    delete ui;
}

void AbstractValveWidget::setName(const QString &name)
{
    m_name = name;
    update();
}

void AbstractValveWidget::setEndAngle(double value)
{
    m_endAngle = value;
    update();
}

void AbstractValveWidget::setRotatesCount(double value)
{
    m_maxAngle = m_endAngle + 360.0 * value;
}

void AbstractValveWidget::setClosurePercent(int value)
{
    switch(m_Direction) {
    case clockWise:
    {
        m_currentAngle = (m_maxAngle - m_endAngle) * (double)value * 0.01;
        break;
    }
    case counterClockWise:
    {
        m_currentAngle = (m_maxAngle - m_endAngle) * (100.0 - (double)value) * 0.01;
        break;
    }
    }

    update();
}

int AbstractValveWidget::closurePercent() const
{
    switch(m_Direction) {
    case clockWise:
    {
        return m_currentAngle * 100.0 / (m_maxAngle - m_endAngle);
    }
    case counterClockWise:
    {
        return 100.0 - m_currentAngle * 100.0 / (m_maxAngle - m_endAngle);
    }
    }
}

void AbstractValveWidget::open()
{
    setClosurePercent(0);
}

void AbstractValveWidget::close()
{
    setClosurePercent(100);
}

bool AbstractValveWidget::isOpen() const
{
    return closurePercent() != 100;
}

void AbstractValveWidget::setOpenDirection(AbstractValveWidget::RotationDirection value)
{
    m_Direction = value;
}

double AbstractValveWidget::normalizedAngle(double value) const
{
    while(value >= 360.0) value -= 360.0;
    return value;
}

void AbstractValveWidget::setCurrentAngle(double value)
{
//    LOG << "SET:" << value;
    m_currentAngle = qBound(0.0, value, m_maxAngle - m_endAngle);
    update();
}

double AbstractValveWidget::realAngle() const
{
    return normalizedAngle(m_currentAngle) + m_endAngle;
}

void AbstractValveWidget::setRotateEnabledRadiusPercent(int value)
{
    m_rotateEanbledRadius = 0.01 * rect().height() * 0.5 * value ;
}

double AbstractValveWidget::calcAngle(const QPoint &p) const
{
    QPoint center = rect().center();

    double angle = qRadiansToDegrees(qAtan((double)(p.y() - center.y()) / (double)(p.x() - center.x())));

    if((p.x() >= center.x()) && (p.y() <= center.y())) {
        angle = qAbs(angle);
    } else if((p.x() <= center.x()) && (p.y() <= center.y())) {
        angle = 180.0 - angle;
    } else if((p.x() <= center.x()) && (p.y() >= center.y())) {
        angle = 180.0 + qAbs(angle);
    } else if((p.x() >= center.x()) && (p.y() >= center.y())) {
        angle = 360.0 - angle;
    }

    return angle;
}

void AbstractValveWidget::draw(QPainter &painter, const QRect &rect) const
{
    if(!m_name.isEmpty()) {
        drawName(painter, rect);
    }
    drawValve(painter, rect);

//    painter.save();

//    QRect drawRect = rect.adjusted(0, 0, -1, -1);
//    int minSide = qMin(drawRect.width(), drawRect.height());
//    drawRect.setSize(QSize(minSide, minSide));
//    drawRect.moveCenter(rect.center());

//    painter.setPen(QPen(Qt::black, 1));
//    painter.setBrush(Qt::NoBrush);
//    painter.drawEllipse(drawRect);

//    double angle = drawingAngle();

////    LOG << "ANGLE:" << m_currentAngle;
////    LOG << "DRAW :" << angle;

//    QPoint p1 = drawRect.center();
//    QPoint p2(p1.x() + drawRect.height() * qCos(angle),
//              p1.y() + drawRect.height() * qSin(angle));

//    painter.drawLine(p1, p2);

//    painter.restore();

    //    drawRotationHelper(painter, drawRect);
}

void AbstractValveWidget::drawName(QPainter &painter, const QRect &rect) const
{
    QFont font("Arial, 7");
    QFontMetrics fontMetrics(font);

    painter.setFont(font);
    painter.setPen(QPen(Qt::black, 1));

    painter.drawText(0, fontMetrics.height(), m_name);
}

void AbstractValveWidget::drawRotationHelper(QPainter &painter, const QRect &rect) const
{
//    QRect drawRect = rect.adjusted(m_rotateEanbledRadius,
//                                   m_rotateEanbledRadius,
//                                   -m_rotateEanbledRadius,
//                                   -m_rotateEanbledRadius);

//    painter.setPen(Qt::NoPen);
//    painter.setBrush(Qt::lightGray);

    //    painter.drawEllipse(drawRect);
}

double AbstractValveWidget::currentAngle() const
{
    return m_currentAngle;
}

double AbstractValveWidget::drawingAngle() const
{
    return qDegreesToRadians(360.0 - (m_currentAngle + m_endAngle));
}

double AbstractValveWidget::drawingAngle(double angle) const
{
    return qDegreesToRadians(360.0 - (angle + m_endAngle));
}

QRect AbstractValveWidget::drawRect() const
{
    QRect r = rect().adjusted(0, 0, -1, -1);
    int minSide = qMin(r.width(), r.height());
    r.setSize(QSize(minSide, minSide));
    r.moveCenter(rect().center());

    return r;
}

void AbstractValveWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    draw(painter, rect());
}

void AbstractValveWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(!m_isGrabbed) {
        return;
    }

    if(rotateEnabled(e->pos())) {
        double newAngle = calcAngle(e->pos());
        double angle = newAngle - normalizedAngle(realAngle());
        if((newAngle < 90.0) && (normalizedAngle(realAngle()) > 270.0)) {
            angle = 360.0 + angle;
        } else if((normalizedAngle(realAngle()) < 90.0) && (newAngle > 270.0)) {
            angle = angle - 360.0;
        }

//        LOG << "new:" << newAngle << "old:" << normalizedAngle(realAngle()) << "angle:" << angle;

        if(qAbs(angle) <= m_grabAngleThr) {
            setCurrentAngle(m_currentAngle + angle);

            emit changed(closurePercent(), false);
            LOG << "CLOSURE:" << closurePercent() << "%";
        }
    }
}

void AbstractValveWidget::mousePressEvent(QMouseEvent *e)
{
    if(m_isGrabbed) {
        return;
    }

    m_grabAngle = calcAngle(e->pos());

    if(qAbs(m_grabAngle - normalizedAngle(realAngle())) <= m_grabAngleThr) {
        m_isGrabbed = true;
        LOG << "GRAB";
    }
}

void AbstractValveWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_isGrabbed) {
        LOG << "UNGRAB";
    }

    emit changed(closurePercent(), true);
    LOG << "CLOSURE:" << closurePercent() << "%";

    m_isGrabbed = false;

}

bool AbstractValveWidget::rotateEnabled(const QPoint& p) const
{
    int x = qAbs(p.x() - rect().center().x());
    int y = qAbs(p.y() - rect().center().y());

    return qSqrt(x * x + y * y) >= m_rotateEanbledRadius;
}
