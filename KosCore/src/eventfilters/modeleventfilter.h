#ifndef MODELEVENTFILTER_H
#define MODELEVENTFILTER_H

#include <AbstractEventFilter.h>
#include <QVariant>

class ModelEventFilter : public AbstractEventFilter
{
public:
    ModelEventFilter();

    void setKey(const QString& key);
    inline const QString& key() const;

    void setValue(const QVariant& value);
    inline const QVariant& value() const;

    // AbstractEventFilter interface
public:
    virtual QJsonObject toJsonObject() const;
    virtual void fromJsonObject(const QJsonObject &jsonObject);
    virtual bool check(AbstractEventLogElement *eventLogElement) const;
    virtual QString description() const;

private:
    QString m_key;
    QVariant m_value;
};

const QString &ModelEventFilter::key() const
{
    return m_key;
}

const QVariant &ModelEventFilter::value() const
{
    return m_value;
}

#endif // MODELEVENTFILTER_H
