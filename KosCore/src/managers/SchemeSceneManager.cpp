#include "SchemeSceneManager.h"

#include <SchemeDataProvider.h>
#include <StringsKeys.h>
#include <SettingsStorage.h>
#include <SchemeItemContainer.h>
#include <SchemeScene.h>
#include <SchemeItemHelper.h>
#include <CanvasSchemeElement.h>
#include <SchemeView.h>

#include <CanvasSchemeItem.h>
#include <BasicSchemeItem.h>
#include <PipelineSchemeItem.h>
#include <ValveSchemeItem.h>
#include <TextSchemeItem.h>
#include <TankSchemeItem.h>
#include <LevelSchemeItem.h>

SchemeSceneManager::SchemeSceneManager(SettingsStorage * settingsStorage,
                                           QObject * parent) :
    QObject(parent),
    m_settingsStorage(settingsStorage),
    m_schemeItemHelper(NULL)
{
    m_schemeDataProvider = new SchemeDataProvider(this);
    m_schemeDataProvider->canvasSchemeElement()->setGridStep(m_settingsStorage->value(SettingsKeys::SCHEME_DEFAULT_GRID_STEP).toReal());
    m_schemeDataProvider->canvasSchemeElement()->setSize(m_settingsStorage->value(SettingsKeys::SCHEME_DEFAULT_SIZE).toSize());

    m_schemeScene = new SchemeScene(m_settingsStorage,
                                    this);

    QObject::connect(m_schemeDataProvider->canvasSchemeElement(), SIGNAL(changed()),
                     this, SLOT(adjustZoomByCanvas()));
}

SchemeSceneManager::~SchemeSceneManager()
{
    delete m_schemeScene;
    delete m_schemeDataProvider;
}


SchemeDataProvider * SchemeSceneManager::schemeDataProvider() const
{
    return m_schemeDataProvider;
}

SchemeScene * SchemeSceneManager::schemeScene() const
{
    return m_schemeScene;
}

AbstractSchemeItemContainer * SchemeSceneManager::basicSchemeItemContainer() const
{
    return m_basicSchemeItemContainer;
}

AbstractSchemeItemContainer * SchemeSceneManager::pipelineSchemeItemContainer() const
{
    return m_pipelineSchemeItemContainer;
}

AbstractSchemeItemContainer * SchemeSceneManager::valveSchemeItemContainer() const
{
    return m_valveSchemeItemContainer;
}

AbstractSchemeItemContainer * SchemeSceneManager::textSchemeItemContainer() const
{
    return m_textSchemeItemContainer;
}

AbstractSchemeItemContainer * SchemeSceneManager::tankSchemeItemContainer() const
{
    return m_tankSchemeItemContainer;
}

AbstractSchemeItemContainer * SchemeSceneManager::levelSchemeItemContainer() const
{
    return m_levelSchemeItemContainer;
}

void SchemeSceneManager::setSchemeView(SchemeView * schemeView)
{
    m_schemeScene->setSchemeView(schemeView);
}

void SchemeSceneManager::adjustZoomByCanvas()
{
    SchemeView * schemeView = m_schemeScene->schemeView();
    CanvasSchemeElement * canvasSchemeElement = m_schemeDataProvider->canvasSchemeElement();

    if (schemeView)
    {
        qreal xZoom = (qreal)schemeView->width() / (qreal)canvasSchemeElement->size().width();
        qreal yZoom = (qreal)schemeView->height() / (qreal)canvasSchemeElement->size().height();
        qreal zoom = qMin(xZoom, yZoom);

        m_schemeScene->setZoom(zoom);
    }
}

void SchemeSceneManager::createSchemeItemContainers()
{
    m_schemeItemHelper = new SchemeItemHelper(m_settingsStorage, m_schemeScene, this);

    m_schemeScene->setCanvasSchemeItem(new CanvasSchemeItem(m_schemeItemHelper, m_schemeDataProvider->canvasSchemeElement()));

    m_basicSchemeItemContainer = new SchemeItemContainer<BasicSchemeElement, BasicSchemeItem>(m_schemeItemHelper, m_schemeDataProvider->basicElementContainer(), m_schemeScene->canvasSchemeItem());
    m_schemeScene->insertItemContainer(m_basicSchemeItemContainer);

    m_pipelineSchemeItemContainer = new SchemeItemContainer<PipelineSchemeElement, PipelineSchemeItem>(m_schemeItemHelper, m_schemeDataProvider->pipelineElementContainer(), m_schemeScene->canvasSchemeItem());
    m_schemeScene->insertItemContainer(m_pipelineSchemeItemContainer);

    m_valveSchemeItemContainer = new SchemeItemContainer<ValveSchemeElement, ValveSchemeItem>(m_schemeItemHelper, m_schemeDataProvider->valveElementContainer(), m_schemeScene->canvasSchemeItem());
    m_schemeScene->insertItemContainer(m_valveSchemeItemContainer);

    m_textSchemeItemContainer = new SchemeItemContainer<TextSchemeElement, TextSchemeItem>(m_schemeItemHelper, m_schemeDataProvider->textSchemeElementContainer(), m_schemeScene->canvasSchemeItem());
    m_schemeScene->insertItemContainer(m_textSchemeItemContainer);

    m_tankSchemeItemContainer = new SchemeItemContainer<TankSchemeElement, TankSchemeItem>(m_schemeItemHelper, m_schemeDataProvider->tankSchemeElementContainer(), m_schemeScene->canvasSchemeItem());
    m_schemeScene->insertItemContainer(m_tankSchemeItemContainer);

    m_levelSchemeItemContainer = new SchemeItemContainer<LevelSchemeElement, LevelSchemeItem>(m_schemeItemHelper, m_schemeDataProvider->levelSchemeElementContainer(), m_schemeScene->canvasSchemeItem());
    m_schemeScene->insertItemContainer(m_levelSchemeItemContainer);
}

