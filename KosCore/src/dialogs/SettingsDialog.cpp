#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

#include "StringsKeys.h"

#include <QMessageBox>

SettingsDialog::SettingsDialog(SettingsStorage * settingsStorage,
                               QWidget * parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    m_settingsStorage(settingsStorage)
{
    ui->setupUi(this);

    connect(this, &SettingsDialog::accepted, this, &SettingsDialog::saveState);
    connect(this, &SettingsDialog::rejected, this, &SettingsDialog::saveState);

    restoreState();
}

SettingsDialog::~SettingsDialog()
{
    saveState();
    delete ui;
}

void SettingsDialog::insertSettingsWidget(AbstractSettingsWidget * settingsWidget)
{
    settingsWidget->setSettingsStorage(m_settingsStorage);
    m_settingsWidgets.insert(settingsWidget);

    ui->twSettingsWidgets->insertTab(ui->twSettingsWidgets->count(), settingsWidget, settingsWidget->windowTitle());
}

void SettingsDialog::settingsLoad()
{
    foreach (AbstractSettingsWidget * settingsWidget, m_settingsWidgets)
    {
        settingsWidget->settingsLoad();
    }
}

void SettingsDialog::settingsSave()
{
    foreach (AbstractSettingsWidget * settingsWidget, m_settingsWidgets)
    {
        settingsWidget->settingsSave();
    }
}

void SettingsDialog::restoreState()
{
    resize(m_settingsStorage->rawValue("size", size(), objectName()).toSize());
}

void SettingsDialog::saveState()
{
    m_settingsStorage->setRawValue("size", size(), objectName());
}

void SettingsDialog::on_buttonBox_accepted()
{
    foreach (AbstractSettingsWidget * settingsWidget, m_settingsWidgets)
    {
        if (!settingsWidget->isSettingsValid())
        {
            QMessageBox::warning(this, tr("Warning..."), settingsWidget->settingsInvalidText());
            return;
        }
    }

    settingsSave();
    accept();
}
