#ifndef BASICSCHEMEITEM_H
#define BASICSCHEMEITEM_H

class SettingsStorage;
class SchemeScene;
class BasicSchemeElement;

#include <AbstractSchemeItem.h>
#include <QGraphicsPixmapItem>

class BasicSchemeItem : public AbstractSchemeItem, public QGraphicsPixmapItem
{

    Q_OBJECT

public:

    BasicSchemeItem(SchemeItemHelper * schemeItemHelper,
                    BasicSchemeElement * basicSchemeElement,
                    QGraphicsItem * parentItem = NULL);

    static QPixmap basicPixmap(BasicSchemeElement * basicSchemeElement, qreal factor);

public slots:

    virtual void updateZoom();

protected slots:

    virtual void elementChanged();

protected:

    BasicSchemeElement * m_basicSchemeElement;

};

#endif // BASICSCHEMEITEM_H
