#include "EventFilterProvider.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>

EventFilterProvider::EventFilterProvider()
{
}

EventFilterProvider::~EventFilterProvider()
{
    clear();
}

QString EventFilterProvider::lastError() const
{
    return m_lastError;
}

void EventFilterProvider::fromJsonObject(const QJsonObject & jsonObject)
{
    clear();

    foreach (QJsonValue jsonStageEventFilter, jsonObject.value("stage_event_filter_list").toArray())
    {
        StageEventFilter * stageEventFilter = new StageEventFilter();
        stageEventFilter->fromJsonObject( jsonStageEventFilter.toObject() );
        m_stageEventFilterList.append( stageEventFilter );
    }
}

QJsonObject EventFilterProvider::toJsonObject() const
{
    QJsonObject jsonObject;

    QJsonArray jsonStageEventFilters;
    foreach (StageEventFilter * stageEventFilter, m_stageEventFilterList)
    {
        jsonStageEventFilters.append(stageEventFilter->toJsonObject());
    }
    jsonObject.insert("stage_event_filter_list", jsonStageEventFilters);

    return jsonObject;
}

QList<StageEventFilter*> EventFilterProvider::stageEventFilterList() const
{
    return m_stageEventFilterList;
}

void EventFilterProvider::insertStageEventFilter(StageEventFilter * stageEventFilter, int index)
{
    Q_ASSERT(index >= 0 && index <= m_stageEventFilterList.count());
    m_stageEventFilterList.insert(index, stageEventFilter);
}

void EventFilterProvider::removeStageEventFilter(StageEventFilter * stageEventFilter)
{
    Q_ASSERT(m_stageEventFilterList.contains(stageEventFilter));
    m_stageEventFilterList.removeOne(stageEventFilter);
    delete stageEventFilter;
}

bool EventFilterProvider::load(const QString & filepath)
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

bool EventFilterProvider::save(const QString & filepath)
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

void EventFilterProvider::clear()
{
    qDeleteAll(m_stageEventFilterList);
    m_stageEventFilterList.clear();
}

