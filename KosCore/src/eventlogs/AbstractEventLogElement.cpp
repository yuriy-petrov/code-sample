#include "AbstractEventLogElement.h"

#include "SchemeEventLogElement.h"
#include "modeleventlogelement.h"
#include "CommentEventLogElement.h"
#include "CimrexLogElement.h"

AbstractEventLogElement::AbstractEventLogElement(EventLogType type) :
    m_eventLogType(type),
    m_checkedState(Unchecked)
{
}

QJsonObject AbstractEventLogElement::toJsonObject() const
{
    QJsonObject jsonObject;
    jsonObject.insert("type", m_eventLogType);
    jsonObject.insert("real_datetime", (qint64)m_realDatetime.toTime_t());
    jsonObject.insert("model_datetime", (qint64)m_modelDatetime.toTime_t());
    jsonObject.insert("checked_state", m_checkedState);
    return jsonObject;
}

AbstractEventLogElement::EventLogType AbstractEventLogElement::eventLogType() const
{
    return m_eventLogType;
}

QDateTime AbstractEventLogElement::realDatetime() const
{
    return m_realDatetime;
}

void AbstractEventLogElement::setRealDatetime(const QDateTime & realDatetime)
{
    m_realDatetime = realDatetime;
}

QDateTime AbstractEventLogElement::modelDatetime() const
{
    return m_modelDatetime;
}

void AbstractEventLogElement::setModelDatetime(const QDateTime & modelDatetime)
{
    m_modelDatetime = modelDatetime;
}

AbstractEventLogElement::CheckedState AbstractEventLogElement::checkedState() const
{
    return m_checkedState;
}

void AbstractEventLogElement::setCheckedState(const AbstractEventLogElement::CheckedState & checkedState)
{
    m_checkedState = checkedState;
}

AbstractEventLogElement * AbstractEventLogElement::fromJsonObject(const QJsonObject & jsonObject)
{
    AbstractEventLogElement * eventLogElement = NULL;

    switch (jsonObject.value("type").toInt(Invalid))
    {
        case Scheme:
        {
            eventLogElement = new SchemeEventLogElement(jsonObject);
            break;
        }
        case Cimrex:
        {
            eventLogElement = new CimrexLogElement(jsonObject);
            break;
        }
        case Model:
        {
            eventLogElement = new ModelEventLogElement(jsonObject);
            break;
        }
        case Comment:
        {
            eventLogElement = new CommentEventLogElement(jsonObject);
            break;
        }
    }

    if (eventLogElement)
    {
        eventLogElement->m_realDatetime = QDateTime::fromTime_t(jsonObject.value("real_datetime").toInt());
        eventLogElement->m_modelDatetime = QDateTime::fromTime_t(jsonObject.value("model_datetime").toInt());
        eventLogElement->m_checkedState = (AbstractEventLogElement::CheckedState)jsonObject.value("checked_state").toInt();
    }
    return eventLogElement;
}


