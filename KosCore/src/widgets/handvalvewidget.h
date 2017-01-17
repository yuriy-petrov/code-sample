#ifndef HANDVALVEWIDGET_H
#define HANDVALVEWIDGET_H

#include <abstractvalvewidget.h>

class HandValveWidget : public AbstractValveWidget
{
    Q_OBJECT
public:
    explicit HandValveWidget(QWidget *parent = 0);

protected:
    virtual void drawValve(QPainter& painter, const QRect& rect) const;
};

#endif // HANDVALVEWIDGET_H
