#include "AbstractSchemeItemContainer.h"

AbstractSchemeItemContainer::AbstractSchemeItemContainer(AbstractSchemeElementContainer * abstractElementContainer,
                                                         SchemeItemHelper * schemeItemHelper,
                                                         QGraphicsItem * parentItem,
                                                         QObject * parent) :
    QObject(parent),
    m_abstractElementContainer(abstractElementContainer),
    m_schemeItemHelper(schemeItemHelper),
    m_parentItem(parentItem),
    m_itemGroup(new QGraphicsItemGroup(parentItem))
{
    m_itemGroup->setHandlesChildEvents(false);
}

AbstractSchemeElementContainer * AbstractSchemeItemContainer::abstractElementContainer() const
{
    return m_abstractElementContainer;
}

bool AbstractSchemeItemContainer::isVisible() const
{
    return m_itemGroup->isVisible();
}

void AbstractSchemeItemContainer::setVisible(bool isVisible)
{
    m_itemGroup->setVisible(isVisible);
}

void AbstractSchemeItemContainer::setZValue(qreal zValue)
{
    m_itemGroup->setZValue(zValue);
}
