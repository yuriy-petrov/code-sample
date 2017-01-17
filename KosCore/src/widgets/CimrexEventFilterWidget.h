#ifndef CIMREXEVENTFILTERWIDGET_H
#define CIMREXEVENTFILTERWIDGET_H

#include <AbstractEventFilterWidget.h>

namespace Ui {
class CimrexEventFilterWidget;
}

class CimrexEventFilterWidget : public AbstractEventFilterWidget
{
    Q_OBJECT

public:
    CimrexEventFilterWidget(QWidget *parent);
    ~CimrexEventFilterWidget();

    // AbstractEventFilterWidget interface
public:
    virtual bool isValid();
    virtual QString errorText();

public slots:
    virtual void save(AbstractEventFilter *eventFilter);
    virtual void load(AbstractEventFilter *eventFilter);

private:
    Ui::CimrexEventFilterWidget *ui;
};

#endif // CIMREXEVENTFILTERWIDGET_H
