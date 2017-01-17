#include "CimrexEventFilter.h"
#include "CimrexLogElement.h"

CimrexEventFilter::CimrexEventFilter() :
    AbstractEventFilter(AbstractEventLogElement::EventLogType::Cimrex)
{

}

CimrexEventFilter::CimrexEventFilter( const QString & displayIdentifier ) :
    AbstractEventFilter(AbstractEventLogElement::EventLogType::Cimrex),
    m_selectedDisplayId(displayIdentifier)
{

}

QJsonObject CimrexEventFilter::toJsonObject() const
{
    QJsonObject jsonObject = AbstractEventFilter::toJsonObject();

    jsonObject.insert("display_id", m_selectedDisplayId);

    return jsonObject;
}

void CimrexEventFilter::fromJsonObject(const QJsonObject &jsonObject)
{
    AbstractEventFilter::fromJsonObject(jsonObject);

    m_selectedDisplayId = jsonObject.value("display_id").toString();
}

bool CimrexEventFilter::check(AbstractEventLogElement *eventLogElement) const
{
    CimrexLogElement* logElement = dynamic_cast<CimrexLogElement*>(eventLogElement);

    if(!logElement) {
        return false;
    }

    return logElement->displayId() == m_selectedDisplayId;
}

QString CimrexEventFilter::description() const
{
    return QString("Selected display = %1").arg(m_selectedDisplayId);
}

void CimrexEventFilter::setSelectedDisplayId(const QString &displayIdentifier)
{
    m_selectedDisplayId = displayIdentifier;
}

QString CimrexEventFilter::selectedDisplayId() const
{
    return m_selectedDisplayId;
}
