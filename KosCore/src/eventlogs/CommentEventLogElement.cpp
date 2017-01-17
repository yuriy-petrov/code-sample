#include "CommentEventLogElement.h"

CommentEventLogElement::CommentEventLogElement() :
    AbstractEventLogElement(AbstractEventLogElement::EventLogType::Comment)
{
}

CommentEventLogElement::CommentEventLogElement(const QJsonObject & jsonObject) :
    AbstractEventLogElement(AbstractEventLogElement::EventLogType::Comment)
{
    m_text = jsonObject.value("text").toString();
}

QString CommentEventLogElement::description()
{
    return m_text;
}

QJsonObject CommentEventLogElement::toJsonObject() const
{
    QJsonObject jsonObject = AbstractEventLogElement::toJsonObject();
    jsonObject.insert("text", m_text);
    return jsonObject;
}

QString CommentEventLogElement::text() const
{
    return m_text;
}

void CommentEventLogElement::setText(const QString & text)
{
    m_text = text;
}
