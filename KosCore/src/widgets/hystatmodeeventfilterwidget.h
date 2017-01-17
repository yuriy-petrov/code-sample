#ifndef HYSTATMODEEVENTFILTERWIDGET_H
#define HYSTATMODEEVENTFILTERWIDGET_H

#include <AbstractEventFilterWidget.h>

namespace Ui {
class HystatModeEventFilterWidget;
}

class HystatModeEventFilterWidget : public AbstractEventFilterWidget
{
    Q_OBJECT

public:
    explicit HystatModeEventFilterWidget(QWidget *parent = 0);
    ~HystatModeEventFilterWidget();

    // AbstractEventFilterWidget interface
public:
    virtual bool isValid();
    virtual QString errorText();

public slots:
    virtual void save(AbstractEventFilter *eventFilter);
    virtual void load(AbstractEventFilter *eventFilter);

private:
    Ui::HystatModeEventFilterWidget *ui;
};

#endif // HYSTATMODEEVENTFILTERWIDGET_H
