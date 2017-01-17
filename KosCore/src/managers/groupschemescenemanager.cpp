#include "GroupSchemeSceneManager.h"

#include <SchemeSceneManager.h>

GroupSchemeSceneManager::GroupSchemeSceneManager(SettingsStorage * settingsStorage,
                                                 QObject * parent) :
        QObject(parent),
        m_settingsStorage(settingsStorage)
{
}

GroupSchemeSceneManager::~GroupSchemeSceneManager()
{
    qDeleteAll(m_schemeSceneManagers);
}

QStringList GroupSchemeSceneManager::schemeKeys() const
{
    return m_schemeKeys;
}

SchemeSceneManager * GroupSchemeSceneManager::schemeSceneManager(const QString & key) const
{
    Q_ASSERT(m_schemeSceneManagers.contains(key));
    return m_schemeSceneManagers.value(key);
}

QString GroupSchemeSceneManager::schemeTitle(const QString & key) const
{
    Q_ASSERT(m_schemeTitles.contains(key));
    return m_schemeTitles.value(key);
}

void GroupSchemeSceneManager::initialize()
{
    registerScheme("electrolyser_1", tr("Electrolyser 1"));
    registerScheme("electrolyser_2", tr("Electrolyser 2"));
    registerScheme("receivers", tr("Receivers"));
}

SchemeSceneManager * GroupSchemeSceneManager::registerScheme(const QString & key, const QString & title)
{
    Q_ASSERT(!m_schemeSceneManagers.contains(key));
    Q_ASSERT(!m_schemeTitles.contains(key));

    SchemeSceneManager * schemeSceneManager = createScheme();
    schemeSceneManager->createSchemeItemContainers();
    m_schemeKeys.append(key);
    m_schemeSceneManagers.insert(key, schemeSceneManager);
    m_schemeTitles.insert(key, title);
    return schemeSceneManager;
}

SchemeSceneManager * GroupSchemeSceneManager::createScheme()
{
    return new SchemeSceneManager(m_settingsStorage, this);
}
