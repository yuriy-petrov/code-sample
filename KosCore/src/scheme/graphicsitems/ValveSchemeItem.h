 #ifndef VALVESCHEMEITEM_H
#define VALVESCHEMEITEM_H

class SettingsStorage;
class SchemeScene;
class ValveSchemeElement;

#include <AbstractSchemeItem.h>
#include <QGraphicsPixmapItem>

class ValveSchemeItem : public AbstractSchemeItem, public QGraphicsPixmapItem
{

    Q_OBJECT

public:

    ValveSchemeItem(SchemeItemHelper * schemeItemHelper,
                    ValveSchemeElement * valveSchemeElement,
                    QGraphicsItem * parentItem = NULL);

    static QPixmap valvePixmap(ValveSchemeElement * valveSchemeElement, qreal factor, const QFont & font);

public slots:

    virtual void updateZoom();

protected slots:

    virtual void elementChanged();

    static void drawInvalid(ValveSchemeElement * valveSchemeElement, QPaintDevice * device);
    static QPixmap drawClosePercentage(ValveSchemeElement * valveSchemeElement, const QPixmap & pixmap, const QFont & font);

protected:

    ValveSchemeElement * m_valveSchemeElement;

};

#endif // VALVESCHEMEITEM_H
