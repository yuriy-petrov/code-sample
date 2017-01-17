#include "AbstractEventFilterWidget.h"

#include "SchemeEventFilterWidget.h"
#include "modeleventfilterwidget.h"
#include "CimrexEventFilterWidget.h"

AbstractEventFilterWidget::AbstractEventFilterWidget(QWidget * parent) :
    QWidget(parent)
{
}

AbstractEventFilterWidget::~AbstractEventFilterWidget()
{
}

AbstractEventFilterWidget * AbstractEventFilterWidget::createByEventLogType(AbstractEventLogElement::EventLogType eventLogType, QWidget * parent)
{
    switch (eventLogType)
    {
        case AbstractEventLogElement::EventLogType::Scheme:
        {
            return new SchemeEventFilterWidget(parent);
        }
        case AbstractEventLogElement::EventLogType::Cimrex:
        {
            return new CimrexEventFilterWidget(parent);
        }
        case AbstractEventLogElement::EventLogType::Model:
        {
            return new ModelEventFilterWidget(parent);
        }
        default:
        {
            return NULL;
        }
    }
}

