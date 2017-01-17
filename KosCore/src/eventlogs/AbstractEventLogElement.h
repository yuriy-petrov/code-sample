#ifndef ABSTRACTEVENTLOGELEMENT_H
#define ABSTRACTEVENTLOGELEMENT_H

#include <QJsonObject>
#include <QDateTime>

class AbstractEventLogElement
{

public:

    enum EventLogType
    {
        Invalid = -1,
        Scheme = 0,
        Cimrex = 1,
        Model = 3,
        Comment = 4
    };

    enum CheckedState
    {
        Unchecked = 0,
        CheckedPass = 1,
        CheckedFail = 2
    };

    AbstractEventLogElement(EventLogType type);

    virtual QString description() = 0;

    virtual QJsonObject toJsonObject() const;

    AbstractEventLogElement::EventLogType eventLogType() const;

    QDateTime realDatetime() const;
    void setRealDatetime(const QDateTime & realDatetime);

    QDateTime modelDatetime() const;
    void setModelDatetime(const QDateTime &modelDatetime);

    AbstractEventLogElement::CheckedState checkedState() const;
    void setCheckedState(const AbstractEventLogElement::CheckedState & checkedState);

    static AbstractEventLogElement * fromJsonObject(const QJsonObject & jsonObject);

protected:

    AbstractEventLogElement::EventLogType m_eventLogType;
    AbstractEventLogElement::CheckedState m_checkedState;

    QDateTime m_realDatetime;
    QDateTime m_modelDatetime;

};

#endif // ABSTRACTEVENTLOGELEMENT_H
