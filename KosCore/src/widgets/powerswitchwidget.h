#ifndef POWERSWITCHWIDGET_H
#define POWERSWITCHWIDGET_H

#include <abstractvalvewidget.h>

class PowerSwitchWidget : public AbstractValveWidget
{
    Q_OBJECT
public:
    explicit PowerSwitchWidget(QWidget *parent = 0);

    void powerOn();
    void powerOff();
    bool isPowerOn() const;

signals:
    void stateChanged(bool isPoweron);

    // AbstractValveWidget interface
protected:
    virtual void drawValve(QPainter &painter, const QRect &rect) const;

private slots:
    void changed(int closurePercent, bool isFinal);
};

#endif // POWERSWITCHWIDGET_H
