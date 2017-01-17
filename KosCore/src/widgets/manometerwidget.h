#ifndef MANOMETERWIDGET_H
#define MANOMETERWIDGET_H

#include <QWidget>

class ManometerWidgetPrivate;

class ManometerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManometerWidget(QWidget *parent = 0);
    virtual ~ManometerWidget();

    void setValue(double value);    // положение стрелки в значениях оси
    void setMaxValue(double value); // максимальное значение на оси

    // текст внизу на шкале у основания стрелки
    void setText(const QString& value); // текст на шкале

public:
    void paintEvent(QPaintEvent* e);

private:
    ManometerWidgetPrivate* m_private;
};

#endif // MANOMETERWIDGET_H
