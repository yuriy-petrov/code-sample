#ifndef TEXTSCHEMEITEM_H
#define TEXTSCHEMEITEM_H

class SettingsStorage;
class SchemeScene;
class TextSchemeElement;

#include <AbstractSchemeItem.h>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class TextSchemeItem : public AbstractSchemeItem, public QGraphicsItem
{

    Q_OBJECT

public:

    TextSchemeItem(SchemeItemHelper * schemeItemHelper,
                   TextSchemeElement * textSchemeElement,
                   QGraphicsItem * parentItem = NULL);

    static QPixmap textPixmap(TextSchemeElement * textSchemeElement, const QFont & font);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

public slots:

    virtual void updateZoom();

protected slots:

    virtual void elementChanged();

protected:

    QGraphicsPixmapItem * m_pixmapItem;

    TextSchemeElement * m_textSchemeElement;
};

#endif // TEXTSCHEMEITEM_H
