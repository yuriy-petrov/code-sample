#include "modeleventfilter.h"
#include "modeleventlogelement.h"
#include "modeleventloghelper.h"
#include "modeltypeshelper.h"
#include "StringsKeys.h"

ModelEventFilter::ModelEventFilter()
    : AbstractEventFilter(AbstractEventLogElement::EventLogType::Model)
    , m_key(Model::HYSTAT_Mode)
{
}

void ModelEventFilter::setValue(const QVariant &value)
{
    m_value = value;
}


QJsonObject ModelEventFilter::toJsonObject() const
{
    QJsonObject jsonObject = AbstractEventFilter::toJsonObject();

    jsonObject.insert("model_key", m_key);
    jsonObject.insert("model_value", ModelEventLogHelper::toJsonValue(m_key, m_value));

    return jsonObject;
}

void ModelEventFilter::fromJsonObject(const QJsonObject &jsonObject)
{
    AbstractEventFilter::fromJsonObject(jsonObject);

    m_key = jsonObject.value("model_key").toString();
    m_value = ModelEventLogHelper::fromJsonValue(m_key, jsonObject.value("model_value"));
}

bool ModelEventFilter::check(AbstractEventLogElement *eventLogElement) const
{
    ModelEventLogElement* logElement = dynamic_cast<ModelEventLogElement*>(eventLogElement);

    if(!logElement) {
        return false;
    }

    return
            (logElement->key() == m_key) &&
            (logElement->value() == m_value);
}

QString ModelEventFilter::description() const
{
    return ModelEventLogHelper::filterDescription(m_key, m_value);
}

void ModelEventFilter::setKey(const QString &key)
{
    m_key = key;
}
