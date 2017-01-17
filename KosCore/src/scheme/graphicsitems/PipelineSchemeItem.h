#ifndef PIPELINESCHEMEITEM_H
#define PIPELINESCHEMEITEM_H

class SettingsStorage;
class SchemeScene;
class PipelineSchemeElement;
class QGraphicsEllipseItem;

#include <AbstractSchemeItem.h>
#include <QSet>
#include <QGraphicsItemGroup>

class PipelineSchemeItem : public AbstractSchemeItem, public QGraphicsItemGroup
{

    Q_OBJECT

public:

    PipelineSchemeItem(SchemeItemHelper * schemeItemHelper,
                       PipelineSchemeElement * pipelineSchemeElement,
                       QGraphicsItem * parentItem = NULL);

public slots:

    virtual void updateZoom();

protected slots:

    virtual void configureLines();

protected:

    PipelineSchemeElement * m_pipelineSchemeElement;

    QList< QList<QGraphicsLineItem*> > m_pipeLines;
    QSet<QGraphicsEllipseItem*> m_crossItems;

};

#endif // PIPELINESCHEMEITEM_H
