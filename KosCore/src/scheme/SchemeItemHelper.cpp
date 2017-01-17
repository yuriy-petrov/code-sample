#include "SchemeItemHelper.h"

SchemeItemHelper::SchemeItemHelper(SettingsStorage * settingsStorage,
                                   SchemeScene * schemeScene,
                                   QObject * parent) :
    QObject(parent),
    m_settingsStorage(settingsStorage),
    m_schemeScene(schemeScene)
{
}

SchemeItemHelper::~SchemeItemHelper()
{
}

SettingsStorage * SchemeItemHelper::settingsStorage() const
{
    return m_settingsStorage;
}

SchemeScene * SchemeItemHelper::schemeScene() const
{
    return m_schemeScene;
}
