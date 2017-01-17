#ifndef CELLSTACKEVENTFILTERWIDGET_H
#define CELLSTACKEVENTFILTERWIDGET_H

#include <AbstractEventFilterWidget.h>

namespace Ui {
    class CellStackEventFilterWidget;
}

class CellStackEventFilterWidget : public AbstractEventFilterWidget
{
    Q_OBJECT

public:
    explicit CellStackEventFilterWidget(QWidget *parent = 0);
    ~CellStackEventFilterWidget();

    // AbstractEventFilterWidget interface
public:
    virtual bool isValid();
    virtual QString errorText();

public slots:
    virtual void save(AbstractEventFilter *eventFilter);
    virtual void load(AbstractEventFilter *eventFilter);

private:
    Ui::CellStackEventFilterWidget *ui;
};

#endif // CELLSTACKEVENTFILTERWIDGET_H
