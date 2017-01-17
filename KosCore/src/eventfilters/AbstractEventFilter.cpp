#include "AbstractEventFilter.h"

#include "SnapshotCondition.h"
#include "SchemeEventFilter.h"
#include "modeleventfilter.h"
#include "CimrexEventFilter.h"

AbstractEventFilter::AbstractEventFilter(AbstractEventLogElement::EventLogType type)
    : m_eventLogType(type)
{
    m_snapshotCondition = new SnapshotCondition;
}

AbstractEventFilter::~AbstractEventFilter()
{
    delete m_snapshotCondition;
}

QJsonObject AbstractEventFilter::toJsonObject() const
{
    QJsonObject jsonObject;
    jsonObject.insert("type", m_eventLogType);
    jsonObject.insert("title", m_title);
    jsonObject.insert("snapshot_condition", m_snapshotCondition->toJsonObject());
    return jsonObject;
}

void AbstractEventFilter::fromJsonObject(const QJsonObject & jsonObject)
{
    m_title = jsonObject.value("title").toString();
    m_snapshotCondition->fromJsonObject(jsonObject.value("snapshot_condition").toObject());
}

AbstractEventLogElement::EventLogType AbstractEventFilter::eventLogType() const
{
    return m_eventLogType;
}

SnapshotCondition * AbstractEventFilter::snapshotCondition() const
{
    return m_snapshotCondition;
}

QString AbstractEventFilter::title() const
{
    return m_title;
}

void AbstractEventFilter::setTitle(const QString &title)
{
    m_title = title;
}

QString AbstractEventFilter::fullDescription() const
{
    if(m_snapshotCondition != NULL) {
        QString conditionsDescription = m_snapshotCondition->description();
        if(conditionsDescription.isEmpty()) {
            return description();
        } else {
            QStringList result;
            result << description()
                   << m_snapshotCondition->description();
            return result.join(QChar('\n'));
        }
    } else {
        return description();
    }
}

AbstractEventFilter * AbstractEventFilter::createByEventLogType(AbstractEventLogElement::EventLogType eventLogType)
{
    switch (eventLogType)
    {
        case AbstractEventLogElement::EventLogType::Scheme:
        {
            return new SchemeEventFilter();
        }
        case AbstractEventLogElement::Model:
        {
            return new ModelEventFilter();
        }
        case AbstractEventLogElement::Cimrex:
        {
            return new CimrexEventFilter();
        }
        default:
        {
            return NULL;
        }
    }
}

AbstractEventFilter * AbstractEventFilter::createByJsonObject(const QJsonObject & jsonObject)
{
    AbstractEventFilter * eventFilter = AbstractEventFilter::createByEventLogType((AbstractEventLogElement::EventLogType)jsonObject.value("type").toInt(AbstractEventLogElement::EventLogType::Invalid));

    if (eventFilter != NULL)
    {
        eventFilter->fromJsonObject(jsonObject);
    }

    return eventFilter;
}

