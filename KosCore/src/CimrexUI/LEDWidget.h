#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QWidget>

class LEDWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LEDWidget(QWidget *parent = 0);
    ~LEDWidget();

protected:
    void paintEvent(QPaintEvent* pe);

signals:

public slots:

};

#endif // LEDWIDGET_H
