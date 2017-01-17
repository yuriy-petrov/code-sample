#ifndef ABSTRACTEVENTFILTERWIDGET_H
#define ABSTRACTEVENTFILTERWIDGET_H

#include "AbstractEventFilter.h"

#include <QWidget>

class AbstractEventFilterWidget : public QWidget
{

    Q_OBJECT

public:

    AbstractEventFilterWidget(QWidget * parent = 0);
    ~AbstractEventFilterWidget();

    static AbstractEventFilterWidget * createByEventLogType(AbstractEventLogElement::EventLogType eventLogType, QWidget * parent = 0);

    virtual bool isValid() = 0;
    virtual QString errorText() = 0;

public slots:

    virtual void save(AbstractEventFilter * eventFilter) = 0;
    virtual void load(AbstractEventFilter * eventFilter) = 0;

};

#endif // ABSTRACTEVENTFILTERWIDGET_H
