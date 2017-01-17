#ifndef SCHEMEITEMCONTAINER_H
#define SCHEMEITEMCONTAINER_H

class SchemeItemHelper;
class SettingsStorage;
class QGraphicsItem;

#include "SchemeElementContainer.h"
#include "AbstractSchemeItemContainer.h"

#include <QHash>
#include <QGraphicsItemGroup>

template< class T, class I >
class SchemeItemContainer: public AbstractSchemeItemContainer
{

public:

    SchemeItemContainer(SchemeItemHelper * schemeItemHelper,
                        SchemeElementContainer<T> * elementContainer,
                        QGraphicsItem * parentItem) :
        AbstractSchemeItemContainer(elementContainer,
                                    schemeItemHelper,
                                    parentItem),
        m_elementContainer(elementContainer)
    {
        QObject::connect(m_elementContainer, SIGNAL(changed()),
                         this, SLOT(updateItems()));

        updateItems();
    }

    virtual QString name()
    {
        return T::schemeElementName();
    }

    virtual void updateZoom()
    {
        foreach (I * item, m_items)
        {
            item->updateZoom();
        }
    }

protected slots:

    virtual void clear()
    {
        qDeleteAll(m_items);
        m_items.clear();
    }

    virtual void updateItems()
    {
        foreach (T * element, m_elementContainer->elements())
        {
            if (!m_items.keys().contains(element))
            {
                I * i = new I(m_schemeItemHelper, element, m_itemGroup);
                QObject::connect(i, SIGNAL(changed()),
                                 this, SLOT(itemChangedEvent()));
                m_items.insert(element, i);
            }
        }

        foreach (T * element, m_items.keys())
        {
            if (!m_elementContainer->elements().contains(element))
            {
                delete m_items.value(element);
                m_items.remove(element);
            }
        }
    }

    virtual void itemChangedEvent()
    {
        I * i = dynamic_cast<I*>(sender());
        if (i)
        {
            if (!i->element()->nodeKey().isEmpty())
            {
                emit itemChanged(i->element()->nodeKey());
            }
        }
    }

private:

    SchemeElementContainer<T> * m_elementContainer;

    QHash<T*,I*> m_items;

};

#endif // SCHEMEITEMCONTAINER_H
