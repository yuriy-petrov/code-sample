#ifndef HWSWITCHEVENTFILTERWIDGET_H
#define HWSWITCHEVENTFILTERWIDGET_H

#include <AbstractEventFilterWidget.h>

namespace Ui {
    class HwSwitchEventFilterWidget;
}

class HwSwitchEventFilterWidget : public AbstractEventFilterWidget
{
    Q_OBJECT

public:
    explicit HwSwitchEventFilterWidget(QWidget *parent = 0);
    ~HwSwitchEventFilterWidget();

    // AbstractEventFilterWidget interface
public:
    bool isValid();
    QString errorText();

public slots:
    void save(AbstractEventFilter * eventFilter);
    void load(AbstractEventFilter * eventFilter);

private:
    Ui::HwSwitchEventFilterWidget *ui;

};

#endif // HWSWITCHEVENTFILTERWIDGET_H
