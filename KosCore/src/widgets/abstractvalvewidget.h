#ifndef ABSTRACTVALVEWIDGET_H
#define ABSTRACTVALVEWIDGET_H

#include <QWidget>

namespace Ui {
class AbstractValveWidget;
}

class AbstractValveWidget : public QWidget
{
    Q_OBJECT

public:
    enum RotationDirection {
        clockWise,
        counterClockWise
    };

public:
    explicit AbstractValveWidget(QWidget *parent = 0);
    virtual ~AbstractValveWidget();

    void setName(const QString& name);
    inline const QString& name() const;

    void setEndAngle(double value); // установить угол крайнего положения ручки
    void setRotatesCount(double value); // установить число оборотов

    void setClosurePercent(int value); // установить процент закрытия
    int closurePercent() const;  // процент закрытия

    void open();
    void close();
    bool isOpen() const;

    void setOpenDirection(RotationDirection value);
    inline RotationDirection openDirection() const;

signals:
    void changed(int closurePercent, bool isFinal);

protected:
    double normalizedAngle(double value) const;
    double calcAngle(const QPoint& p) const;

    void setCurrentAngle(double value);
    double realAngle() const;

    void setRotateEnabledRadiusPercent(int value);

    void draw(QPainter& painter, const QRect& rect) const;

    virtual void drawValve(QPainter& painter, const QRect& rect) const = 0;

    virtual void drawName(QPainter& painter, const QRect& rect) const;
    virtual void drawRotationHelper(QPainter& painter, const QRect& rect) const;

    double currentAngle() const;
    double drawingAngle() const;
    double drawingAngle(double angle) const;

    inline double maxAngle() const;

    QRect drawRect() const;

    void paintEvent(QPaintEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    bool rotateEnabled(const QPoint &p) const;

private:
    Ui::AbstractValveWidget *ui;

    QString m_name;

    RotationDirection m_Direction;

    double m_currentAngle; // текущий угол поворота
    double m_endAngle; // угол крайнего положения
    double m_maxAngle; // максимальный угол поворота

    int m_rotateEanbledRadius; // радиус, начиная с которого разрешено вращение

    bool m_isGrabbed;
    double m_grabAngleThr; // предел угла захвата мышкой (относительно текущего угла)
    double m_grabAngle; // угол точки захвата от-но текущего угла

    QPainterPath m_rotateHelperClipPath;
};

const QString &AbstractValveWidget::name() const
{
    return m_name;
}

AbstractValveWidget::RotationDirection AbstractValveWidget::openDirection() const
{
    return m_Direction;
}

double AbstractValveWidget::maxAngle() const
{
    return m_maxAngle;
}

#endif // ABSTRACTVALVEWIDGET_H
