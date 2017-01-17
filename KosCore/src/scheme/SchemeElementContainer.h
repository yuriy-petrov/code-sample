#ifndef SCHEMEELEMENTCONTAINER_H
#define SCHEMEELEMENTCONTAINER_H

#include <QList>
#include <QJsonObject>

#include "AbstractSchemeElementContainer.h"

template< class T >
class SchemeElementContainer: public AbstractSchemeElementContainer
{

public:

    SchemeElementContainer(const QString & name) :
        AbstractSchemeElementContainer(name)
    {
    }

    T * element(const QString & nodeKey) const
    {
        foreach (T * t, m_elements)
        {
            if (t->nodeKey() == nodeKey)
            {
                return t;
            }
        }

        return NULL;
    }

    QList<T*> elements() const
    {
        return m_elements;
    }

    void insert(T * element)
    {
        Q_ASSERT(!m_elements.contains(element));

        m_abstractElements.append(element);
        m_elements.append(element);
        emit changed();
    }

    void remove(T * element)
    {
        Q_ASSERT(m_abstractElements.contains(element));
        Q_ASSERT(m_elements.contains(element));

        delete element;
        m_abstractElements.removeOne(element);
        m_elements.removeOne(element);
        emit changed();
    }

    virtual void clear()
    {
        qDeleteAll(m_elements);
        m_abstractElements.clear();
        m_elements.clear();
        emit changed();
    }

    virtual QJsonArray toJsonArray()
    {
        QJsonArray jsonArray;
        foreach (T * t, m_elements)
        {
            jsonArray.append(t->toJsonObject());
        }
        return jsonArray;
    }

    virtual void fromJsonArray(const QJsonArray & jsonArray)
    {
        qDeleteAll(m_elements);
        m_abstractElements.clear();
        m_elements.clear();

        foreach (QJsonValue jsonValue, jsonArray)
        {
            T * t = new T(this);
            t->fromJsonObject(jsonValue.toObject());
            m_abstractElements.append(t);
            m_elements.append(t);

            QObject::connect(t, SIGNAL(changed()),
                             this, SLOT(elementChangedEvent()));

        }
        emit changed();
    }

protected slots:

    virtual void elementChangedEvent()
    {
        T * t = dynamic_cast<T*>(sender());
        if (t)
        {
            if (!t->nodeKey().isEmpty())
            {
                emit elementChanged(t->nodeKey());
            }
        }
    }

private:

    QList<T*> m_elements;

};

#endif // SCHEMEELEMENTCONTAINER_H
