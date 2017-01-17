#ifndef SOUNDSETTINGSWIDGETPRIVATE_H
#define SOUNDSETTINGSWIDGETPRIVATE_H

#include <QObject>

namespace Ui {
    class SoundSettingsWidget;
}

class SoundSettingsWidgetPrivate : public QObject
{
    Q_OBJECT
    friend class SoundSettingsWidget;

public:
    explicit SoundSettingsWidgetPrivate(QWidget *parent = 0);
    virtual ~SoundSettingsWidgetPrivate();

private slots:
    void on_toolButtonSelectAlarmSound_clicked();

private:
    Ui::SoundSettingsWidget *ui;
};

#endif // SOUNDSETTINGSWIDGETPRIVATE_H
