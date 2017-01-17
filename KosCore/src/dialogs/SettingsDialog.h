#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "SettingsStorage.h"

#include <AbstractSettingsWidget.h>

#include <QDialog>
#include <QSet>

namespace Ui
{
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{

    Q_OBJECT

public:

    explicit SettingsDialog(SettingsStorage * settingsStorage,
                            QWidget * parent = 0);
    ~SettingsDialog();

public slots:

    void insertSettingsWidget(AbstractSettingsWidget * settingsWidget);
    void settingsLoad();
    void settingsSave();

private slots:

    void restoreState();
    void saveState();

    void on_buttonBox_accepted();

private:

    Ui::SettingsDialog * ui;

    SettingsStorage * m_settingsStorage;

    QSet<AbstractSettingsWidget*> m_settingsWidgets;

};

#endif // SETTINGSDIALOG_H
