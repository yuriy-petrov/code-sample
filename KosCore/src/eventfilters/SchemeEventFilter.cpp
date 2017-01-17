#include "SchemeEventFilter.h"

#include "ValveSchemeElement.h"
#include "LevelSchemeElement.h"

SchemeEventFilter::SchemeEventFilter() :
    AbstractEventFilter(AbstractEventLogElement::EventLogType::Scheme),
    m_actionType(SchemeEventLogElement::ActionType::Invalid),
    m_valveMinValue(0),
    m_valveMaxValue(0)
{
    m_eventLogType = AbstractEventLogElement::EventLogType::Scheme;
}

QJsonObject SchemeEventFilter::toJsonObject() const
{
    QJsonObject jsonObject = AbstractEventFilter::toJsonObject();

    jsonObject.insert("action_type", m_actionType);
    jsonObject.insert("node_key", m_nodeKey);
    jsonObject.insert("valve_min_value", m_valveMinValue);
    jsonObject.insert("valve_max_value", m_valveMaxValue);

    return jsonObject;
}

void SchemeEventFilter::fromJsonObject(const QJsonObject &jsonObject)
{
    AbstractEventFilter::fromJsonObject(jsonObject);

    m_actionType = (SchemeEventLogElement::ActionType)jsonObject.value("action_type").toInt(SchemeEventLogElement::ActionType::Invalid);
    m_nodeKey = jsonObject.value("node_key").toString();
    m_valveMinValue = jsonObject.value("valve_min_value").toInt();
    m_valveMaxValue = jsonObject.value("valve_max_value").toInt();
}

bool SchemeEventFilter::check(AbstractEventLogElement * eventLogElement) const
{
    if (eventLogElement->eventLogType() == m_eventLogType)
    {
        SchemeEventLogElement * schemeEventLogElement = dynamic_cast<SchemeEventLogElement*>(eventLogElement);
        if (schemeEventLogElement)
        {
            if (schemeEventLogElement->actionType() == m_actionType)
            {
                switch (m_actionType)
                {
                    case SchemeEventLogElement::ActionType::Invalid:
                    {
                        return false;
                    }
                    case SchemeEventLogElement::ActionType::ValveClosePercentageChanged:
                    {
                        ValveSchemeElement valveElement;
                        valveElement.fromJsonObject(schemeEventLogElement->jsonDetails());
                        if (valveElement.nodeKey() == m_nodeKey && valveElement.closePercentage() >= m_valveMinValue && valveElement.closePercentage() <= m_valveMaxValue)
                        {
                            return true;
                        }
                        break;
                    }
                    case SchemeEventLogElement::ActionType::LevelCheckNormal:
                    {
                        LevelSchemeElement levelElement;
                        levelElement.fromJsonObject(schemeEventLogElement->jsonDetails());
                        if (levelElement.nodeKey() == m_nodeKey)
                        {
                            return true;
                        }
                        break;
                    }
                    case SchemeEventLogElement::ActionType::LevelCheckOverfill:
                    {
                        LevelSchemeElement levelElement;
                        levelElement.fromJsonObject(schemeEventLogElement->jsonDetails());
                        if (levelElement.nodeKey() == m_nodeKey)
                        {
                            return true;
                        }
                        break;
                    }
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return false;
}

QString SchemeEventFilter::description() const
{
    switch (m_actionType)
    {
        case SchemeEventLogElement::ActionType::Invalid:
        {
            return QObject::tr("invalid type of action");
        }
        case SchemeEventLogElement::ActionType::ValveClosePercentageChanged:
        {
            if(m_valveMinValue == m_valveMaxValue) {
                if(m_valveMinValue == 0) {
                    return QObject::tr("open valve %1").arg(m_nodeKey);
                } else if(m_valveMinValue == 100) {
                    return QObject::tr("close valve %1").arg(m_nodeKey);
                } else {
                    return QObject::tr("sets the close percentage of valve %1 to (%2)%").arg(m_nodeKey).arg(m_valveMinValue);
                }
            }
            return QObject::tr("sets the close percentage of valve %1 to (%2~%3)%").arg(m_nodeKey).arg(m_valveMinValue).arg(m_valveMaxValue);
        }
        case SchemeEventLogElement::ActionType::LevelCheckNormal:
        {
            return QObject::tr("check the level %1 - normal").arg(m_nodeKey);
        }
        case SchemeEventLogElement::ActionType::LevelCheckOverfill:
        {
            return QObject::tr("check the level %1 - overfill").arg(m_nodeKey);
        }
    }

    return QString();
}

SchemeEventLogElement::ActionType SchemeEventFilter::actionType() const
{
    return m_actionType;
}

void SchemeEventFilter::setActionType(const SchemeEventLogElement::ActionType & actionType)
{
    m_actionType = actionType;
}
QString SchemeEventFilter::nodeKey() const
{
    return m_nodeKey;
}

void SchemeEventFilter::setNodeKey(const QString &nodeKey)
{
    m_nodeKey = nodeKey;
}
int SchemeEventFilter::valveMinValue() const
{
    return m_valveMinValue;
}

void SchemeEventFilter::setValveMinValue(int valveMinValue)
{
    m_valveMinValue = valveMinValue;
}
int SchemeEventFilter::valveMaxValue() const
{
    return m_valveMaxValue;
}

void SchemeEventFilter::setValveMaxValue(int valveMaxValue)
{
    m_valveMaxValue = valveMaxValue;
}




