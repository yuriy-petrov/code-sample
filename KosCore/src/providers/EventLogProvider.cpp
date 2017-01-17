#include "EventLogProvider.h"

#include <AbstractEventLogElement.h>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>

EventLogProvider::EventLogProvider(QObject * parent) :
    QObject(parent)
{
}

EventLogProvider::~EventLogProvider()
{
    clear();
}

QString EventLogProvider::lastError() const
{
    return m_lastError;
}

void EventLogProvider::fromJsonObject(const QJsonObject & jsonObject)
{
    clear();

    foreach (QJsonValue jsonValue, jsonObject.value("events").toArray())
    {
        AbstractEventLogElement * eventLogElement = AbstractEventLogElement::fromJsonObject(jsonValue.toObject());
        if (eventLogElement)
        {
            m_eventLogElements.append(eventLogElement);
        }
    }

    emit changed();
}

QJsonObject EventLogProvider::toJsonObject() const
{
    QJsonObject jsonObject;
    QJsonArray jsonArray;
    foreach (AbstractEventLogElement * eventLogElement, m_eventLogElements)
    {
        jsonArray.append(eventLogElement->toJsonObject());
    }
    jsonObject.insert("events", jsonArray);
    return jsonObject;
}

QList<AbstractEventLogElement *> EventLogProvider::eventLogElements() const
{
    return m_eventLogElements;
}

void EventLogProvider::clear()
{
    qDeleteAll(m_eventLogElements);
    m_eventLogElements.clear();
    emit changed();
}

bool EventLogProvider::load(const QString & filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly))
    {
        fromJsonObject(QJsonDocument().fromJson(file.readAll()).object());
        return true;
    }
    else
    {
        m_lastError = file.errorString();
        return false;
    }
}

bool EventLogProvider::save(const QString & filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(QJsonDocument(toJsonObject()).toJson());
        return true;
    }
    else
    {
        m_lastError = file.errorString();
        return false;
    }
}

void EventLogProvider::appendEventLogElement(AbstractEventLogElement * eventLogElement)
{
    m_eventLogElements.append(eventLogElement);
    emit changed();
}
