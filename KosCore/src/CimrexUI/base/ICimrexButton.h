#ifndef ICIMREXBUTTON_H
#define ICIMREXBUTTON_H

#include <QPushButton>

class ICimrexButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ICimrexButton(QWidget *parent = 0);

signals:

public slots:

protected:
    virtual void paintEvent(QPaintEvent* pe);
};

#endif // ICIMREXBUTTON_H
