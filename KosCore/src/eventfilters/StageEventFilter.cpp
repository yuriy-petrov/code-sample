#include "StageEventFilter.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

StageEventFilter::StageEventFilter() :
    m_eventFilter(NULL)
{

}

StageEventFilter::~StageEventFilter()
{
    clear();
}

void StageEventFilter::fromJsonObject(const QJsonObject & jsonObject)
{
    clear();

    //

    m_title = jsonObject.value("title").toString();
    m_eventFilter = AbstractEventFilter::createByJsonObject(jsonObject.value("event_filter").toObject());

    foreach (QJsonValue jsonBlockEventFilter, jsonObject.value("block_event_filter_list").toArray())
    {
        BlockEventFilter * blockEventFilter = new BlockEventFilter();
        blockEventFilter->fromJsonObject( jsonBlockEventFilter.toObject() );
        m_blockEventFilterList.append( blockEventFilter );
    }
}

QJsonObject StageEventFilter::toJsonObject() const
{
    QJsonObject jsonObject;
    jsonObject.insert("title", m_title);
    if (m_eventFilter)
    {
        jsonObject.insert("event_filter", m_eventFilter->toJsonObject());
    }

    QJsonArray jsonBlockEventFilters;
    foreach (BlockEventFilter * blockEventFilter, m_blockEventFilterList)
    {
        jsonBlockEventFilters.append(blockEventFilter->toJsonObject());
    }
    jsonObject.insert("block_event_filter_list", jsonBlockEventFilters);

    return jsonObject;
}

QString StageEventFilter::title() const
{
    return m_title;
}

void StageEventFilter::setTitle(const QString & title)
{
    m_title = title;
}

AbstractEventFilter * StageEventFilter::eventFilter() const
{
    return m_eventFilter;
}

void StageEventFilter::setEventFilter(AbstractEventFilter * eventFilter)
{
    if (m_eventFilter)
    {
        delete m_eventFilter;
    }
    m_eventFilter = eventFilter;
}

QList<BlockEventFilter *> StageEventFilter::blockEventFilterList() const
{
    return m_blockEventFilterList;
}

void StageEventFilter::insertBlockEventFilter(BlockEventFilter * blockEventFilter, int index)
{
    Q_ASSERT(index >= 0 && index <= m_blockEventFilterList.count());
    m_blockEventFilterList.insert(index, blockEventFilter);
}

void StageEventFilter::removeBlockEventFilter(BlockEventFilter * blockEventFilter)
{
    Q_ASSERT(m_blockEventFilterList.contains(blockEventFilter));
    m_blockEventFilterList.removeOne(blockEventFilter);
    delete blockEventFilter;
}

void StageEventFilter::clear()
{
    if (m_eventFilter)
    {
        delete m_eventFilter;
    }
    m_eventFilter = NULL;

    qDeleteAll(m_blockEventFilterList);
    m_blockEventFilterList.clear();
}




