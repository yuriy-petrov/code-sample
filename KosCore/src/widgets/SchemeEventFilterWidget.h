#ifndef SCHEMEEVENTFILTERWIDGET_H
#define SCHEMEEVENTFILTERWIDGET_H

#include "AbstractEventFilterWidget.h"

namespace Ui
{
    class SchemeEventFilterWidget;
}

class SchemeEventFilterWidget : public AbstractEventFilterWidget
{

    Q_OBJECT

public:

    SchemeEventFilterWidget(QWidget * parent = 0);
    ~SchemeEventFilterWidget();

    virtual bool isValid();
    virtual QString errorText();

public slots:

    virtual void save(AbstractEventFilter * eventFilter);
    virtual void load(AbstractEventFilter * eventFilter);

private slots:

    void on_cbActionType_currentIndexChanged(int index);

private:

    Ui::SchemeEventFilterWidget * ui;

};

#endif // SCHEMEEVENTFILTERWIDGET_H
