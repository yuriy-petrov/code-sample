#ifndef MODELEVENTLOGELEMENT_H
#define MODELEVENTLOGELEMENT_H

#include <AbstractEventLogElement.h>
#include <QVariant>

class ModelEventLogElement : public AbstractEventLogElement
{
public:

    ModelEventLogElement();
    ModelEventLogElement(const QString& key, const QVariant& value);
    ModelEventLogElement(const QJsonObject & jsonObject);

    void setKey(const QString& value);
    inline const QString& key() const;

    void setValue(const QVariant& value);
    inline const QVariant& value() const;

    // EventLogElement interface
public:

    virtual QString description();
    virtual QJsonObject toJsonObject() const;

private:

    QString m_key;
    QVariant m_value;

};

const QString &ModelEventLogElement::key() const
{
    return m_key;
}

const QVariant &ModelEventLogElement::value() const
{
    return m_value;
}

#endif // MODELEVENTLOGELEMENT_H
