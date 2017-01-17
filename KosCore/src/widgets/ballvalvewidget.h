#ifndef BALLVALVEWIDGET_H
#define BALLVALVEWIDGET_H

#include <abstractvalvewidget.h>

class BallValveWidget : public AbstractValveWidget
{
    Q_OBJECT
public:
    explicit BallValveWidget(QWidget *parent = 0);

    // AbstractValveWidget interface
protected:
    virtual void drawValve(QPainter &painter, const QRect &rect) const;
};

#endif // BALLVALVEWIDGET_H
