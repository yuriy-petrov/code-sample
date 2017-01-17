#ifndef ABSTRACTSCHEMEITEM_H
#define ABSTRACTSCHEMEITEM_H

class SchemeItemHelper;
class AbstractSchemeElement;
class QPainter;
class QGraphicsItem;
class QGraphicsPixmapItem;

#include <QObject>

class AbstractSchemeItem : public QObject
{

    Q_OBJECT

public:

    AbstractSchemeItem(SchemeItemHelper * schemeItemHelper,
                       AbstractSchemeElement * element,
                       QObject * parent = 0);

    SchemeItemHelper * schemeItemHelper() const;
    AbstractSchemeElement * element() const;

signals:

    void changed();

protected:

    void setGraphicsItem(QGraphicsItem * graphicsItem);

    static void drawSelectRect(QPainter * painter, AbstractSchemeElement * element);

protected slots:

    virtual void elementChanged();

private:

    void updateForm();

protected:

    SchemeItemHelper * m_schemeItemHelper;
    AbstractSchemeElement * m_element;
    QGraphicsItem * m_graphicsItem;

    QGraphicsPixmapItem * m_formTextItem;

};

#endif // ABSTRACTSCHEMEITEM_H
