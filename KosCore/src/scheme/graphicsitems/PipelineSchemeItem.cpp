#include "PipelineSchemeItem.h"

#include "PipelineSchemeElement.h"
#include "SchemeScene.h"
#include "SchemeItemHelper.h"

#include <KosTypesHelper.h>
#include <StringsKeys.h>
#include <SettingsStorage.h>
#include <SchemeItemHelper.h>
#include <SchemeKeys.h>

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QDebug>

PipelineSchemeItem::PipelineSchemeItem(SchemeItemHelper * schemeItemHelper,
                                       PipelineSchemeElement * pipelineSchemeElement,
                                       QGraphicsItem * parentItem) :
    AbstractSchemeItem(schemeItemHelper, pipelineSchemeElement),
    QGraphicsItemGroup(parentItem),
    m_pipelineSchemeElement(pipelineSchemeElement)
{
    this->setAcceptHoverEvents(true);
    this->setZValue(-1);

    configureLines();

    QObject::connect(m_pipelineSchemeElement, SIGNAL(changed()),
                     this, SLOT(configureLines()));

    this->setGraphicsItem(this);
}

void PipelineSchemeItem::updateZoom()
{
    configureLines();
}

void PipelineSchemeItem::configureLines()
{
    this->setToolTip(m_pipelineSchemeElement->tooltip());

    for (int i = 0; i < m_pipeLines.count(); ++i)
    {
        for (int j = 0; j < m_pipeLines[i].count(); ++j)
        {
            delete m_pipeLines[i][j];
        }
    }
    m_pipeLines.clear();

    KosTypes::SubstanceType substanceType = m_pipelineSchemeElement->substanceType();

    QPen pen;
    pen.setWidth(m_pipelineSchemeElement->width());
    pen.setColor(substanceType == KosTypes::SubstanceType::Nothing ? QColor(Qt::black) : KosTypesHelper::instance()->substanceTypeColors().value(m_pipelineSchemeElement->substanceType()));

    if (m_pipelineSchemeElement->isHighlighted())
    {
        pen.setColor(KosConsts::HIGHLIGHT_PEN_COLOR);
    }

    switch (m_pipelineSchemeElement->state())
    {
        case KosTypes::PipelineState::Normal: pen.setStyle(Qt::SolidLine); break;
        case KosTypes::PipelineState::Corked: pen.setStyle(Qt::DashLine); break;
        case KosTypes::PipelineState::Teared: pen.setStyle(Qt::DashDotDotLine); break;
    }

    foreach (PipelineSchemeElement::Pipe pipe, m_pipelineSchemeElement->pipes())
    {
        QList<QGraphicsLineItem*> pipeLines;
        for (int i = 0; i < pipe.count() - 1; ++i)
        {
            QGraphicsLineItem * lineItem = new QGraphicsLineItem(QLineF(pipe[i] * m_schemeItemHelper->schemeScene()->zoom(), pipe[i+1] * m_schemeItemHelper->schemeScene()->zoom()), this);
            lineItem->setPen(pen);
            pipeLines.append(lineItem);

            lineItem->installSceneEventFilter(this);
            lineItem->setAcceptHoverEvents(true);
        }
        m_pipeLines.append(pipeLines);
    }


    qDeleteAll(m_crossItems);
    m_crossItems.clear();

    for (int i = 0; i < m_pipelineSchemeElement->pipes().size(); ++i)
    {
        for (int j = 0; j < m_pipelineSchemeElement->pipes().size(); ++j)
        {
            for ( int ii = 0; ii < m_pipelineSchemeElement->pipes()[i].size() - 1; ++ii)
            {
                for ( int jj = 0; jj < m_pipelineSchemeElement->pipes()[j].size() - 1; ++jj)
                {
                    if (!(i == j && ii == jj))
                    {
                        QPointF pi1 = m_pipelineSchemeElement->pipes()[i][ii];
                        QPointF pi2 = m_pipelineSchemeElement->pipes()[i][ii + 1];

                        QPointF pj1 = m_pipelineSchemeElement->pipes()[j][jj];
                        QPointF pj2 = m_pipelineSchemeElement->pipes()[j][jj + 1];

                        if (pi1 != pj1 && pi1 != pj2 && pi2 != pj1 && pi2 != pj2)
                        {
                            QPointF point;
                            if (QLineF(pi1, pi2).intersect(QLineF(pj1, pj2), &point) == QLineF::BoundedIntersection)
                            {
                                QBrush brush(Qt::SolidPattern);
                                brush.setColor(QColor(Qt::black));

                                QGraphicsEllipseItem * crossItem = new QGraphicsEllipseItem(this);
                                crossItem->setBrush(brush);
                                crossItem->setRect(-3, -3, 7, 7);
                                crossItem->setPos(point * m_schemeItemHelper->schemeScene()->zoom());
                                m_crossItems.insert(crossItem);
                            }
                        }
                    }
                }
            }
        }
    }
}
