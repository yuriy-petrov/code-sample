#ifndef CIMREXEVENTFILTER_H
#define CIMREXEVENTFILTER_H

#include "AbstractEventFilter.h"

class CimrexEventFilter : public AbstractEventFilter
{
public:
    CimrexEventFilter();
    CimrexEventFilter( const QString & displayIdentifier );

    virtual QJsonObject toJsonObject() const;
    virtual void fromJsonObject(const QJsonObject &jsonObject);

    void setSelectedDisplayId(const QString & displayIdentifier);
    QString selectedDisplayId() const;

    virtual bool check(AbstractEventLogElement *eventLogElement) const;
    virtual QString description() const;

private:
    QString m_selectedDisplayId;
};

#endif // CIMREXEVENTFILTER_H
