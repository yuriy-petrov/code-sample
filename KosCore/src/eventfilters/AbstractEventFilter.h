#ifndef ABSTRACTEVENTFILTER_H
#define ABSTRACTEVENTFILTER_H

class SnapshotCondition;

#include "AbstractEventLogElement.h"

class AbstractEventFilter
{

public:

    AbstractEventFilter(AbstractEventLogElement::EventLogType type);
    virtual ~AbstractEventFilter();

    virtual QJsonObject toJsonObject() const;
    virtual void fromJsonObject(const QJsonObject & jsonObject);

    AbstractEventLogElement::EventLogType eventLogType() const;
    SnapshotCondition * snapshotCondition() const;

    QString title() const;
    void setTitle(const QString & title);

    virtual bool check(AbstractEventLogElement * eventLogElement) const = 0;
    QString fullDescription() const;

    static AbstractEventFilter * createByEventLogType(AbstractEventLogElement::EventLogType eventLogType);
    static AbstractEventFilter * createByJsonObject(const QJsonObject & jsonObject);

protected:

    virtual QString description() const = 0;

protected:

    AbstractEventLogElement::EventLogType m_eventLogType;
    SnapshotCondition * m_snapshotCondition;
    QString m_title;

};

#endif // ABSTRACTEVENTFILTER_H
