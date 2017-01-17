#include "SchemeScene.h"

#include "CanvasSchemeItem.h"
#include "AbstractSchemeItemContainer.h"
#include "SchemeView.h"

#include <StringsKeys.h>
#include <SettingsStorage.h>
#include <QGraphicsScene>

SchemeScene::SchemeScene(SettingsStorage * settingsStorage,
                         QObject * parent) :
    QObject(parent),
    m_settingsStorage(settingsStorage),
    m_canvasSchemeItem(NULL),
    m_zoomMinimum(0.1),
    m_zoomMaximum(10),
    m_zoomDelta(0.1),
    m_zoom(1),
    m_schemeView(0)
{
    m_scene = new QGraphicsScene(this);
}

QGraphicsScene * SchemeScene::scene() const
{
    return m_scene;
}

CanvasSchemeItem * SchemeScene::canvasSchemeItem() const
{
    return m_canvasSchemeItem;
}

SchemeView * SchemeScene::schemeView() const
{
    return m_schemeView;
}

QSet<AbstractSchemeItemContainer *> SchemeScene::schemeItemContainers() const
{
    return m_schemeItemContainers;
}

qreal SchemeScene::zoomDelta() const
{
    return m_zoomDelta;
}

qreal SchemeScene::zoom() const
{
    return m_zoom;
}

void SchemeScene::setSchemeView(SchemeView * schemeView)
{
    m_schemeView = schemeView;
    canvasElementChanged();
}

void SchemeScene::setCanvasSchemeItem(CanvasSchemeItem * canvasSchemeItem)
{
    m_canvasSchemeItem = canvasSchemeItem;

    m_scene->addItem(m_canvasSchemeItem);

    QObject::connect(m_canvasSchemeItem, SIGNAL(boundigRectChanged(QRectF)),
                     this, SLOT(canvasElementChanged()));
}

void SchemeScene::setZoom(const qreal & zoom)
{
    m_zoom = zoom;

    if (m_zoom < m_zoomMinimum)
    {
        m_zoom = m_zoomMinimum;
    }
    else if (m_zoom > m_zoomMaximum)
    {
        m_zoom = m_zoomMaximum;
    }

    m_canvasSchemeItem->updateZoom();
    foreach (AbstractSchemeItemContainer * schemeItemContainer, m_schemeItemContainers)
    {
        schemeItemContainer->updateZoom();
    }
}

void SchemeScene::insertItemContainer(AbstractSchemeItemContainer * schemeItemContainer)
{
    m_schemeItemContainers.insert(schemeItemContainer);
}

void SchemeScene::canvasElementChanged()
{
    if (m_schemeView)
    {
        m_schemeView->setSceneRect(m_canvasSchemeItem->boundingRect());
        m_schemeView->centerOn( QPointF(m_canvasSchemeItem->boundingRect().width() / 2.0, m_canvasSchemeItem->boundingRect().height() / 2.0) );
    }
}
