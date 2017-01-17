#include "soundsettingswidget.h"
#include "ui_soundsettingswidget.h"
#include "soundsettingswidgetprivate.h"
#include "StringsKeys.h"

SoundSettingsWidget::SoundSettingsWidget(bool isInterfaceEditable, QWidget *parent)
    : AbstractSettingsWidget(parent)
    , m_private(new SoundSettingsWidgetPrivate(this))
{

}

SoundSettingsWidget::~SoundSettingsWidget()
{
}


bool SoundSettingsWidget::isSettingsValid()
{
    return settingsInvalidText().isEmpty();
}

QString SoundSettingsWidget::settingsInvalidText()
{
    return m_private->ui->lineEditAlarmSound->text().isEmpty() ?
                tr("Alarm sound file must be specified!") :
                QString();
}

void SoundSettingsWidget::settingsLoad()
{
    m_private->ui->lineEditAlarmSound->setText(m_settingsStorage->value(SettingsKeys::ALARM_SOUND).toString());
    m_private->ui->horizontalSliderVolume->setValue(m_settingsStorage->value(SettingsKeys::ALARM_SOUND_VOLUME).toInt());
}

void SoundSettingsWidget::settingsSave()
{
    m_settingsStorage->setValue(SettingsKeys::ALARM_SOUND,
                                m_private->ui->lineEditAlarmSound->text());
    m_settingsStorage->setValue(SettingsKeys::ALARM_SOUND_VOLUME,
                                m_private->ui->horizontalSliderVolume->value());
}
