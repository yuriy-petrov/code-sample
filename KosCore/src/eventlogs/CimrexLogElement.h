#ifndef CIMREXLOGELEMENT_H
#define CIMREXLOGELEMENT_H

#include "AbstractEventLogElement.h"

class CimrexLogElement : public AbstractEventLogElement
{

public:

    CimrexLogElement();
    CimrexLogElement(const QJsonObject & jsonObject);

    virtual QString description();

    virtual QJsonObject toJsonObject() const;

    QString displayId() const;
    void setDisplayId(const QString & displayIdentifier );

private:
    QString m_displayId;

};

#endif // CIMREXLOGELEMENT_H
