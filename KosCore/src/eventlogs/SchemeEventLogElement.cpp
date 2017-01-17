#include "SchemeEventLogElement.h"

#include <ValveSchemeElement.h>
#include <LevelSchemeElement.h>

SchemeEventLogElement::SchemeEventLogElement() :
    AbstractEventLogElement(AbstractEventLogElement::EventLogType::Scheme)
{
}

SchemeEventLogElement::SchemeEventLogElement(const QJsonObject & jsonObject) :
    AbstractEventLogElement(AbstractEventLogElement::EventLogType::Scheme)
{
    m_actionType = (SchemeEventLogElement::ActionType)jsonObject.value("action_type").toInt();
    m_jsonDetails = jsonObject.value("details").toObject();
}

QString SchemeEventLogElement::description()
{
    switch (m_actionType)
    {
        case SchemeEventLogElement::ActionType::Invalid:
        {
            return QObject::tr("invalid type of action");
        }
        case SchemeEventLogElement::ActionType::ValveClosePercentageChanged:
        {
            ValveSchemeElement valveElement;
            valveElement.fromJsonObject(m_jsonDetails);
            if(valveElement.closePercentage() == 0) {
                return QObject::tr("valve %1 was opened").arg(valveElement.nodeKey());
            } else if(valveElement.closePercentage() == 100) {
                return QObject::tr("valve %1 was closed").arg(valveElement.nodeKey());
            } else {
                return QObject::tr("valve %1 close percentage was setted to %2%").arg(valveElement.nodeKey()).arg(valveElement.closePercentage());
            }
        }
        case SchemeEventLogElement::ActionType::LevelCheckNormal:
        {
            LevelSchemeElement levelElement;
            levelElement.fromJsonObject(m_jsonDetails);
            return QObject::tr("level %1 was checked - normal").arg(levelElement.nodeKey());
        }
        case SchemeEventLogElement::ActionType::LevelCheckOverfill:
        {
            LevelSchemeElement levelElement;
            levelElement.fromJsonObject(m_jsonDetails);
            return QObject::tr("level %1 was checked - overfill").arg(levelElement.nodeKey());
        }
    }

    return QString();
}

QJsonObject SchemeEventLogElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractEventLogElement::toJsonObject();

    jsonObject.insert("action_type", m_actionType);
    jsonObject.insert("details", m_jsonDetails);

    return jsonObject;
}

SchemeEventLogElement::ActionType SchemeEventLogElement::actionType() const
{
    return m_actionType;
}

void SchemeEventLogElement::setActionType(SchemeEventLogElement::ActionType actionType)
{
    m_actionType = actionType;
}

QJsonObject SchemeEventLogElement::jsonDetails() const
{
    return m_jsonDetails;
}

void SchemeEventLogElement::setJsonDetails(const QJsonObject & jsonDetails)
{
    m_jsonDetails = jsonDetails;
}

