#ifndef SCHEMEEVENTLOGELEMENT_H
#define SCHEMEEVENTLOGELEMENT_H

#include "AbstractEventLogElement.h"
#include "ValveSchemeElement.h"

class SchemeEventLogElement : public AbstractEventLogElement
{

public:

    enum ActionType
    {
        Invalid = -1,
        ValveClosePercentageChanged = 0,
        LevelCheckNormal = 1,
        LevelCheckOverfill = 2
    };

    SchemeEventLogElement();
    SchemeEventLogElement(const QJsonObject & jsonObject);

    virtual QString description();

    virtual QJsonObject toJsonObject() const;

    SchemeEventLogElement::ActionType actionType() const;
    void setActionType(SchemeEventLogElement::ActionType actionType);

    QJsonObject jsonDetails() const;
    void setJsonDetails(const QJsonObject & jsonDetails);

private:

    ActionType m_actionType;
    QJsonObject m_jsonDetails;

};

#endif // SCHEMEEVENTLOGELEMENT_H
