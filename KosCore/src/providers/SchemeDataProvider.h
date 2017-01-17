#ifndef SCHEMEDATAPROVIDER_H
#define SCHEMEDATAPROVIDER_H

class CanvasSchemeElement;

#include "SchemeElementContainer.h"
#include "BasicSchemeElement.h"
#include "PipelineSchemeElement.h"
#include "ValveSchemeElement.h"
#include "TextSchemeElement.h"
#include "TankSchemeElement.h"
#include "LevelSchemeElement.h"

#include <QSet>
#include <QSize>
#include <QObject>

class SchemeDataProvider : public QObject
{

    Q_OBJECT

public:

    explicit SchemeDataProvider(QObject * parent = 0);

    QJsonObject toJsonObject() const;
    QString lastError() const;

    CanvasSchemeElement * canvasSchemeElement() const;

    QSet<AbstractSchemeElementContainer*> elementContainers() const;

    SchemeElementContainer<BasicSchemeElement> * basicElementContainer() const;
    SchemeElementContainer<PipelineSchemeElement> * pipelineElementContainer() const;
    SchemeElementContainer<ValveSchemeElement> * valveElementContainer() const;
    SchemeElementContainer<TextSchemeElement> * textSchemeElementContainer() const;
    SchemeElementContainer<TankSchemeElement> * tankSchemeElementContainer() const;
    SchemeElementContainer<LevelSchemeElement> * levelSchemeElementContainer() const;

public slots:

    void fromJsonObject(const QJsonObject & jsonObject);

    bool load(const QString & filepath);
    bool save(const QString & filepath);

private:

    void insertContainer(AbstractSchemeElementContainer * container);

private:

    CanvasSchemeElement * m_canvasSchemeElement;

    QSet<AbstractSchemeElementContainer*> m_elementContainers;

    SchemeElementContainer<BasicSchemeElement> * m_basicElementContainer;
    SchemeElementContainer<PipelineSchemeElement> * m_pipelineElementContainer;
    SchemeElementContainer<ValveSchemeElement> * m_valveElementContainer;
    SchemeElementContainer<TextSchemeElement> * m_textSchemeElementContainer;
    SchemeElementContainer<TankSchemeElement> * m_tankSchemeElementContainer;
    SchemeElementContainer<LevelSchemeElement> * m_levelSchemeElementContainer;

    QString m_lastError;

};

#endif // SCHEMEDATAPROVIDER_H
