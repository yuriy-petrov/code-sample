#include "Trouble.h"

Trouble::Trouble()
{
}

Trouble::Trouble(QString key, QString description) :
    m_key(key),
    m_description(description)
{
}

QString Trouble::key() const
{
    return m_key;
}

QString Trouble::description() const
{
    return m_description;
}

void Trouble::setDescription(const QString & description)
{
    m_description = description;
}

void Trouble::fromJsonObject(const QJsonObject & jsonObject)
{
    m_key = jsonObject.value("key").toString();
    m_description = jsonObject.value("description").toString();
}

QJsonObject Trouble::toJsonObject()
{
    QJsonObject jsonObject;
    jsonObject.insert("key", m_key);
    jsonObject.insert("description", m_description);
    return jsonObject;
}

QList<Trouble> Trouble::troubleListFromJsonArray(const QJsonArray & jsonArray)
{
    QList<Trouble> troubles;
    foreach (QJsonValue value, jsonArray)
    {
        Trouble trouble;
        trouble.fromJsonObject(value.toObject());
        troubles.append(trouble);
    }
    return troubles;
}

QJsonArray Trouble::troubleListToJsonArray(const QList<Trouble> & troubleList)
{
    QJsonArray jsonArray;
    foreach (Trouble trouble, troubleList)
    {
        jsonArray.append(trouble.toJsonObject());
    }
    return jsonArray;
}

