#ifndef SCHEMESCENEMANAGER_H
#define SCHEMESCENEMANAGER_H

class AbstractSchemeItemContainer;
class SchemeDataProvider;
class SchemeScene;
class SchemeView;
class SettingsStorage;
class SchemeItemHelper;

#include <QObject>

class SchemeSceneManager: public QObject
{

    Q_OBJECT

public:

    SchemeSceneManager(SettingsStorage * settingsStorage,
                       QObject * parent = 0);
    ~SchemeSceneManager();

    SchemeDataProvider * schemeDataProvider() const;
    SchemeScene * schemeScene() const;

    AbstractSchemeItemContainer * basicSchemeItemContainer() const;
    AbstractSchemeItemContainer * pipelineSchemeItemContainer() const;
    AbstractSchemeItemContainer * valveSchemeItemContainer() const;
    AbstractSchemeItemContainer * textSchemeItemContainer() const;
    AbstractSchemeItemContainer * tankSchemeItemContainer() const;
    AbstractSchemeItemContainer * levelSchemeItemContainer() const;

public slots:

    void setSchemeView(SchemeView * schemeView);
    void adjustZoomByCanvas();

public:

    virtual void createSchemeItemContainers();

protected:

    SettingsStorage * m_settingsStorage;
    SchemeDataProvider * m_schemeDataProvider;
    SchemeScene * m_schemeScene;

    SchemeItemHelper * m_schemeItemHelper;

    AbstractSchemeItemContainer * m_basicSchemeItemContainer;
    AbstractSchemeItemContainer * m_pipelineSchemeItemContainer;
    AbstractSchemeItemContainer * m_valveSchemeItemContainer;
    AbstractSchemeItemContainer * m_textSchemeItemContainer;
    AbstractSchemeItemContainer * m_tankSchemeItemContainer;
    AbstractSchemeItemContainer * m_levelSchemeItemContainer;

};

#endif // SCHEMESCENEMANAGER_H
