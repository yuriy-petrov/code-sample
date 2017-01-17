#ifndef POWERSWEVENTFILTERWIDGET_H
#define POWERSWEVENTFILTERWIDGET_H

#include <AbstractEventFilterWidget.h>

namespace Ui {
class PowerSwEventFilterWidget;
}

class PowerSwEventFilterWidget : public AbstractEventFilterWidget
{
    Q_OBJECT

public:
    explicit PowerSwEventFilterWidget(QWidget *parent = 0);
    ~PowerSwEventFilterWidget();

    // AbstractEventFilterWidget interface
public:
    virtual bool isValid();
    virtual QString errorText();

public slots:
    virtual void save(AbstractEventFilter *eventFilter);
    virtual void load(AbstractEventFilter *eventFilter);

private:
    Ui::PowerSwEventFilterWidget *ui;
};

#endif // POWERSWEVENTFILTERWIDGET_H
