#include "SchemeDataProvider.h"

#include "CanvasSchemeElement.h"

#include <QFile>
#include <QJsonDocument>

SchemeDataProvider::SchemeDataProvider(QObject * parent) :
    QObject(parent)
{
    m_canvasSchemeElement = new CanvasSchemeElement(this);

    insertContainer(m_basicElementContainer = new SchemeElementContainer<BasicSchemeElement>("basic_element_container"));
    insertContainer(m_pipelineElementContainer = new SchemeElementContainer<PipelineSchemeElement>("pipeline_element_container"));
    insertContainer(m_valveElementContainer = new SchemeElementContainer<ValveSchemeElement>("valve_element_container"));
    insertContainer(m_textSchemeElementContainer = new SchemeElementContainer<TextSchemeElement>("text_element_container"));
    insertContainer(m_tankSchemeElementContainer = new SchemeElementContainer<TankSchemeElement>("tank_element_container"));
    insertContainer(m_levelSchemeElementContainer = new SchemeElementContainer<LevelSchemeElement>("level_element_container"));
}

QJsonObject SchemeDataProvider::toJsonObject() const
{
    QJsonObject jsonObject;
    foreach (AbstractSchemeElementContainer * container, m_elementContainers)
    {
        jsonObject.insert(container->name(), container->toJsonArray());
    }
    jsonObject.insert("canvas", m_canvasSchemeElement->toJsonObject());
    return jsonObject;
}

QString SchemeDataProvider::lastError() const
{
    return m_lastError;
}

CanvasSchemeElement * SchemeDataProvider::canvasSchemeElement() const
{
    return m_canvasSchemeElement;
}

QSet<AbstractSchemeElementContainer*> SchemeDataProvider::elementContainers() const
{
    return m_elementContainers;
}

SchemeElementContainer<BasicSchemeElement> * SchemeDataProvider::basicElementContainer() const
{
    return m_basicElementContainer;
}

SchemeElementContainer<PipelineSchemeElement> * SchemeDataProvider::pipelineElementContainer() const
{
    return m_pipelineElementContainer;
}

SchemeElementContainer<ValveSchemeElement> * SchemeDataProvider::valveElementContainer() const
{
    return m_valveElementContainer;
}

SchemeElementContainer<TextSchemeElement> * SchemeDataProvider::textSchemeElementContainer() const
{
    return m_textSchemeElementContainer;
}

SchemeElementContainer<TankSchemeElement> * SchemeDataProvider::tankSchemeElementContainer() const
{
    return m_tankSchemeElementContainer;
}

SchemeElementContainer<LevelSchemeElement> * SchemeDataProvider::levelSchemeElementContainer() const
{
    return m_levelSchemeElementContainer;
}

void SchemeDataProvider::fromJsonObject(const QJsonObject & jsonObject)
{
    foreach (AbstractSchemeElementContainer * container, m_elementContainers)
    {
        container->clear();
        container->fromJsonArray(jsonObject.value( container->name() ).toArray());
    }
    m_canvasSchemeElement->fromJsonObject(jsonObject.value("canvas").toObject());
}

bool SchemeDataProvider::load(const QString & filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly))
    {
        fromJsonObject(QJsonDocument().fromJson(file.readAll()).object());
        return true;
    }
    else
    {
        m_lastError = file.errorString();
        return false;
    }
}

bool SchemeDataProvider::save(const QString & filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(QJsonDocument(toJsonObject()).toJson());
        return true;
    }
    else
    {
        m_lastError = file.errorString();
        return false;
    }
}

void SchemeDataProvider::insertContainer(AbstractSchemeElementContainer * container)
{
    m_elementContainers.insert(container);
}

