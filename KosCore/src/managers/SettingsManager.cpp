#include "SettingsManager.h"
#include "SettingsStorage.h"
#include "StringsKeys.h"

#include <FileSettingsStorage.h>
#include <log.h>

#include <QApplication>
#include <QColor>
#include <QFont>

SettingsManager::SettingsManager(QObject * parent, const QString& filename) :
    QObject(parent)
{
    FileSettingsStorage * fileSettingsStorage = new FileSettingsStorage(this);
    // FIXME: Продумать как и где хранить настройки
    if(filename.isEmpty()) {
        fileSettingsStorage->createSettings(QApplication::organizationName(), QApplication::applicationName());
    } else {
        QStringList path = QCoreApplication::instance()->applicationDirPath().split(QChar('/'));
        path.removeLast();
        fileSettingsStorage->createSettings(QString("%1/%2").arg(path.join("/")).arg(filename));
    }
    fileSettingsStorage->setAutoSave(true);

    m_settingsStorage = fileSettingsStorage;
    createDefaultSettings();
}

SettingsStorage * SettingsManager::settingsStorage() const
{
    return m_settingsStorage;
}

void SettingsManager::createDefaultSettings()
{
    m_settingsStorage->setDefaultValue(SettingsKeys::SCHEME_DEFAULT_SIZE, QSize(600, 800));
    m_settingsStorage->setDefaultValue(SettingsKeys::SCHEME_DEFAULT_GRID_STEP, 32);

    m_settingsStorage->setDefaultValue(SettingsKeys::SCHEME_PIPELINE_HIGHLIGHT_WIDTH_DELTA, 1);
    m_settingsStorage->setDefaultValue(SettingsKeys::SCHEME_PIPELINE_POINT_SIZE, 6);
    m_settingsStorage->setDefaultValue(SettingsKeys::SCHEME_PIPELINE_POINT_HIGHLIGHT_SIZE, 8);

    m_settingsStorage->setDefaultValue(SettingsKeys::OXYGEN_COLOR, QColor(0, 0, 255));
    m_settingsStorage->setDefaultValue(SettingsKeys::HYDROGEN_COLOR, QColor(255, 0, 0));
    m_settingsStorage->setDefaultValue(SettingsKeys::ELECTROLYTE_COLOR, QColor(128, 0, 255));

    m_settingsStorage->setDefaultValue(SettingsKeys::SCHEME_FONT_FAMILY, QApplication::font().family());
    m_settingsStorage->setDefaultValue(SettingsKeys::SCHEME_FONT_SIZE, QApplication::font().pointSize());
}
