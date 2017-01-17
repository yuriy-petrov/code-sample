#ifndef SCHEMEEVENTFILTER_H
#define SCHEMEEVENTFILTER_H

#include "AbstractEventFilter.h"
#include "SchemeEventLogElement.h"

class SchemeEventFilter : public AbstractEventFilter
{

public:

    SchemeEventFilter();

    virtual QJsonObject toJsonObject() const;
    virtual void fromJsonObject(const QJsonObject & jsonObject);

    virtual bool check(AbstractEventLogElement * eventLogElement) const;
    virtual QString description() const;

    SchemeEventLogElement::ActionType actionType() const;
    void setActionType(const SchemeEventLogElement::ActionType & actionType);

    QString nodeKey() const;
    void setNodeKey(const QString & nodeKey);

    int valveMinValue() const;
    void setValveMinValue(int valveMinValue);

    int valveMaxValue() const;
    void setValveMaxValue(int valveMaxValue);

private:

    SchemeEventLogElement::ActionType m_actionType;
    QString m_nodeKey;
    int m_valveMinValue;
    int m_valveMaxValue;

};

#endif // SCHEMEEVENTFILTER_H
