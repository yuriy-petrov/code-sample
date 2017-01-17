#include <QFileDialog>
#include "soundsettingswidgetprivate.h"
#include "ui_soundsettingswidget.h"


SoundSettingsWidgetPrivate::SoundSettingsWidgetPrivate(QWidget *parent)
    : QObject(parent)
    , ui(new Ui::SoundSettingsWidget)
{
    ui->setupUi(parent);

    connect(ui->toolButtonSelectAlarmSound, &QToolButton::clicked,
            this, &SoundSettingsWidgetPrivate::on_toolButtonSelectAlarmSound_clicked);
}

SoundSettingsWidgetPrivate::~SoundSettingsWidgetPrivate()
{
    delete ui;
}

void SoundSettingsWidgetPrivate::on_toolButtonSelectAlarmSound_clicked()
{
    QString file = QFileDialog::getOpenFileName(qobject_cast<QWidget*>(parent()),
                                                tr("Select alarm sound"),
                                                "../sound",
                                                QString(),
                                                0,
                                                QFileDialog::ReadOnly);

    if(!file.isEmpty()) {
        ui->lineEditAlarmSound->setText(file);
    }
}
