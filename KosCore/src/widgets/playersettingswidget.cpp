#include <log.h>
#include "playersettingswidget.h"
#include "playersettingswidgetprivate.h"
#include "StringsKeys.h"
#include "ui_playersettingswidget.h"

PlayerSettingsWidget::PlayerSettingsWidget(bool isInterfaceEditable,
                                           QWidget *parent)
    : AbstractSettingsWidget(parent)
    , m_private(new PlayerSettingsWidgetPrivate(this))
{

}

PlayerSettingsWidget::~PlayerSettingsWidget()
{
    LOG << "DESTROY:" << this;
}


bool PlayerSettingsWidget::isSettingsValid()
{
    return true;
}

QString PlayerSettingsWidget::settingsInvalidText()
{
    return QString();
}

void PlayerSettingsWidget::settingsLoad()
{
    m_private->m_stagesPath = m_settingsStorage->value(SettingsKeys::PLAYER_STAGES_DIR).toString();

    m_private->m_stages = Player::Stages::fromString(
                m_settingsStorage->value(SettingsKeys::PLAYER_STAGES).toString());
    m_private->m_stagesModel.setStages(m_private->m_stages);
    m_private->ui->tableView->resizeColumnsToContents();

    LOG << "LOAD:" << m_private->m_stages;
}

void PlayerSettingsWidget::settingsSave()
{
    LOG << "SAVE:" << m_private->m_stagesPath;
    m_settingsStorage->setValue(SettingsKeys::PLAYER_STAGES_DIR, m_private->m_stagesPath);

    LOG << "SAVE:" << m_private->m_stagesModel.stages();
    m_settingsStorage->setValue(SettingsKeys::PLAYER_STAGES, m_private->m_stagesModel.stages().toString());
}
