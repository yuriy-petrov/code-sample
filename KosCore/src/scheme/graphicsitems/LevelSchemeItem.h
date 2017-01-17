#ifndef LEVELSCHEMEITEM_H
#define LEVELSCHEMEITEM_H

class SettingsStorage;
class SchemeScene;
class LevelSchemeElement;

#include <KosTypes.h>

#include <AbstractSchemeItem.h>
#include <QGraphicsPixmapItem>

class LevelSchemeItem : public AbstractSchemeItem, public QGraphicsPixmapItem
{

    Q_OBJECT

public:

    LevelSchemeItem(SchemeItemHelper * schemeItemHelper,
                    LevelSchemeElement * levelSchemeElement,
                    QGraphicsItem * parentItem = NULL);

    static QPixmap levelPixmap(LevelSchemeElement * levelSchemeElement, qreal factor);

public slots:

    virtual void updateZoom();

protected slots:

    virtual void elementChanged();

protected:

    LevelSchemeElement * m_levelSchemeElement;

};

#endif // LEVELSCHEMEITEM_H
