#ifndef TANKSCHEMEITEM_H
#define TANKSCHEMEITEM_H

class SettingsStorage;
class SchemeScene;
class TankSchemeElement;

#include <AbstractSchemeItem.h>
#include <QGraphicsPixmapItem>

class TankSchemeItem : public AbstractSchemeItem, public QGraphicsPixmapItem
{

    Q_OBJECT

public:

    TankSchemeItem(SchemeItemHelper * schemeItemHelper,
                   TankSchemeElement * tankSchemeElement,
                   QGraphicsItem * parentItem = NULL);

    static QPixmap tankPixmap(TankSchemeElement * tankSchemeElement, qreal factor);

public slots:

    virtual void updateZoom();

protected slots:

    virtual void elementChanged();

protected:

    TankSchemeElement * m_tankSchemeElement;

};

#endif // TANKSCHEMEITEM_H
