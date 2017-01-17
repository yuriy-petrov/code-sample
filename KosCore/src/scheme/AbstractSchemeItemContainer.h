#ifndef ABSTRACTSCHEMEITEMCONTAINER_H
#define ABSTRACTSCHEMEITEMCONTAINER_H

class SettingsStorage;
class SchemeScene;
class SchemeItemHelper;
class AbstractSchemeElementContainer;

#include <QObject>
#include <QGraphicsItemGroup>

class AbstractSchemeItemContainer: public QObject
{

    Q_OBJECT

public:

    AbstractSchemeItemContainer(AbstractSchemeElementContainer * abstractElementContainer,
                                SchemeItemHelper * schemeItemHelper,
                                QGraphicsItem * parentItem,
                                QObject * parent = 0);

    AbstractSchemeElementContainer * abstractElementContainer() const;
    virtual bool isVisible() const;
    virtual QString name() = 0;
    virtual void updateZoom() = 0;

public slots:

    virtual void setVisible(bool isVisible);
    void setZValue(qreal zValue);

signals:

    void itemChanged(const QString & nodeKey);

protected slots:

    virtual void clear() = 0;
    virtual void updateItems() = 0;
    virtual void itemChangedEvent() = 0;

protected:

    AbstractSchemeElementContainer * m_abstractElementContainer;
    SchemeItemHelper * m_schemeItemHelper;
    QGraphicsItem * m_parentItem;
    QGraphicsItemGroup * m_itemGroup;

};

#endif // ABSTRACTSCHEMEITEMCONTAINER_H
