#include "AbstractSchemeElementContainer.h"

#include <AbstractSchemeElement.h>

AbstractSchemeElementContainer::AbstractSchemeElementContainer(const QString & name,
                                                               QObject * parent) :
    QObject(parent)
{
    m_name = name;
}

QString AbstractSchemeElementContainer::name() const
{
    return m_name;
}

QList<AbstractSchemeElement *> AbstractSchemeElementContainer::abstractElements() const
{
    return m_abstractElements;
}

AbstractSchemeElement * AbstractSchemeElementContainer::abstractElement(const QString & nodeKey) const
{
    foreach (AbstractSchemeElement * abstractElement, m_abstractElements)
    {
        if (abstractElement->nodeKey() == nodeKey)
        {
            return abstractElement;
        }
    }
    return NULL;
}

