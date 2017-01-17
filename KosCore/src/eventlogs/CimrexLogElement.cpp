#include "CimrexLogElement.h"

#include <QObject>

CimrexLogElement::CimrexLogElement() :
    AbstractEventLogElement(AbstractEventLogElement::EventLogType::Cimrex)
{
}

CimrexLogElement::CimrexLogElement(const QJsonObject & jsonObject) :
    AbstractEventLogElement(AbstractEventLogElement::EventLogType::Cimrex)
{
    m_displayId = jsonObject.value("display_id").toString();
}

QString CimrexLogElement::description()
{
    return QObject::tr("Switch to screen '%1'").arg(m_displayId);
}

QJsonObject CimrexLogElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractEventLogElement::toJsonObject();

    jsonObject.insert("display_id", m_displayId);

    return jsonObject;
}

QString CimrexLogElement::displayId() const
{
    return m_displayId;
}

void CimrexLogElement::setDisplayId(const QString & displayIdentifier )
{
    m_displayId = displayIdentifier;
}
