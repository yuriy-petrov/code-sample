#include "BlockEventFilter.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QObject>
#include <QMap>

BlockEventFilter::BlockEventFilter() :
    m_logicType(BlockEventFilter::LogicType::And),
    m_timeIntervalType(BlockEventFilter::TimeIntervalType::Ignore),
    m_timeInterval(0)
{
}

BlockEventFilter::~BlockEventFilter()
{
    clear();
}

void BlockEventFilter::fromJsonObject(const QJsonObject & jsonObject)
{
    clear();

    m_logicType = (BlockEventFilter::LogicType)jsonObject.value("logic_type").toInt();
    m_title = jsonObject.value("title").toString();
    m_timeIntervalType = (BlockEventFilter::TimeIntervalType)jsonObject.value("time_interval_type").toInt(BlockEventFilter::TimeIntervalType::Ignore);
    m_timeInterval = jsonObject.value("time_interval").toInt();
    foreach (QJsonValue jsonFilter, jsonObject.value("event_filter_list").toArray())
    {
        AbstractEventFilter * eventFilter = AbstractEventFilter::createByJsonObject( jsonFilter.toObject() );
        Q_ASSERT(eventFilter != NULL);
        m_eventFilterList.append(eventFilter);
    }
}

QJsonObject BlockEventFilter::toJsonObject() const
{
    QJsonObject jsonObject;
    jsonObject.insert("logic_type", m_logicType);
    jsonObject.insert("title", m_title);
    jsonObject.insert("time_interval_type", m_timeIntervalType);
    jsonObject.insert("time_interval", m_timeInterval);

    QJsonArray jsonFilters;
    foreach (AbstractEventFilter * filter, m_eventFilterList)
    {
        jsonFilters.append(filter->toJsonObject());
    }
    jsonObject.insert("event_filter_list", jsonFilters);

    return jsonObject;
}

QString BlockEventFilter::title() const
{
    return m_title;
}

void BlockEventFilter::setTitle(const QString & title)
{
    m_title = title;
}

BlockEventFilter::LogicType BlockEventFilter::logicType() const
{
    return m_logicType;
}

void BlockEventFilter::setLogicType(const BlockEventFilter::LogicType & logicType)
{
    m_logicType = logicType;
}

const QString &BlockEventFilter::logicTypeName() const
{
    return logicTypeNames()[logicType()];
}

BlockEventFilter::TimeIntervalType BlockEventFilter::timeIntervalType() const
{
    return m_timeIntervalType;
}

void BlockEventFilter::setTimeIntervalType(const BlockEventFilter::TimeIntervalType & timeIntervalType)
{
    m_timeIntervalType = timeIntervalType;
}

int BlockEventFilter::timeInterval() const
{
    return m_timeInterval;
}

void BlockEventFilter::setTimeInterval(int timeInterval)
{
    m_timeInterval = timeInterval;
}

QList<AbstractEventFilter *> BlockEventFilter::eventFilterList() const
{
    return m_eventFilterList;
}

void BlockEventFilter::insertEventFilter(AbstractEventFilter * eventFilter, int index)
{
    Q_ASSERT(index >= 0 && index <= m_eventFilterList.count());
    m_eventFilterList.insert(index, eventFilter);
}

void BlockEventFilter::removeEventFilter(AbstractEventFilter * eventFilter)
{
    Q_ASSERT(m_eventFilterList.contains(eventFilter));
    m_eventFilterList.removeOne(eventFilter);
    delete eventFilter;
}

void BlockEventFilter::replaceEventFilter(AbstractEventFilter * eventFilter, int index)
{
    Q_ASSERT(index >= 0 && index < m_eventFilterList.count());
    m_eventFilterList[index] = eventFilter;
}

QMap<BlockEventFilter::LogicType, QString> _initLogicTypeNames()
{
    QMap<BlockEventFilter::LogicType, QString> names;
    names.insert(BlockEventFilter::And, QObject::tr(("And")));
    names.insert(BlockEventFilter::Or, QObject::tr(("Or")));
    names.insert(BlockEventFilter::Not, QObject::tr(("Not")));
    return names;
}

const QMap<BlockEventFilter::LogicType, QString> &BlockEventFilter::logicTypeNames()
{
    static const QMap<BlockEventFilter::LogicType, QString> names = _initLogicTypeNames();
    return names;
}

QMap<BlockEventFilter::TimeIntervalType, QString> _initTimeIntervalTypeNames()
{
    QMap<BlockEventFilter::TimeIntervalType, QString> names;
    names.insert(BlockEventFilter::Ignore, QObject::tr(("Ignore")));
    names.insert(BlockEventFilter::Less, QObject::tr(("<")));
    names.insert(BlockEventFilter::More, QObject::tr((">")));
    return names;
}

const QMap<BlockEventFilter::TimeIntervalType, QString> &BlockEventFilter::timeIntervalTypeNames()
{
    static const QMap<BlockEventFilter::TimeIntervalType, QString> names = _initTimeIntervalTypeNames();
    return names;
}

void BlockEventFilter::clear()
{
    qDeleteAll(m_eventFilterList);
    m_eventFilterList.clear();
}
