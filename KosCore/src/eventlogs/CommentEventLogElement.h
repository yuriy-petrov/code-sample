#ifndef COMMENTEVENTLOGELEMENT_H
#define COMMENTEVENTLOGELEMENT_H

#include "AbstractEventLogElement.h"

class CommentEventLogElement : public AbstractEventLogElement
{

public:

    CommentEventLogElement();
    CommentEventLogElement(const QJsonObject & jsonObject);

    virtual QString description();
    virtual QJsonObject toJsonObject() const;

    QString text() const;
    void setText(const QString & text);

private:

    QString m_text;

};

#endif // COMMENTEVENTLOGELEMENT_H
