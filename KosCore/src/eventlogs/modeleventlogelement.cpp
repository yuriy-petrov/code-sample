#include "modeleventlogelement.h"
#include "modeleventloghelper.h"

#include <QObject>

ModelEventLogElement::ModelEventLogElement()
    : AbstractEventLogElement(AbstractEventLogElement::EventLogType::Model)
{
}

ModelEventLogElement::ModelEventLogElement(const QString &key, const QVariant &value)
    : AbstractEventLogElement(AbstractEventLogElement::EventLogType::Model)
    , m_key(key)
    , m_value(value)
{
}

ModelEventLogElement::ModelEventLogElement(const QJsonObject &jsonObject)
    : AbstractEventLogElement(AbstractEventLogElement::EventLogType::Model)
{
    m_key = jsonObject.value("key").toString();
    m_value = ModelEventLogHelper::fromJsonValue(m_key, jsonObject.value("value"));
}

void ModelEventLogElement::setKey(const QString &value)
{
    m_key = value;
}

void ModelEventLogElement::setValue(const QVariant &value)
{
    m_value = value;
}

QString ModelEventLogElement::description()
{
    return ModelEventLogHelper::eventDescription(m_key, m_value);
}

QJsonObject ModelEventLogElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractEventLogElement::toJsonObject();

    jsonObject.insert("key", m_key);
    jsonObject.insert("value", ModelEventLogHelper::toJsonValue(m_key, m_value));

    return jsonObject;
}
