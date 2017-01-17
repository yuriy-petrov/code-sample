#ifndef PLAYERSETTINGSWIDGETPRIVATE_H
#define PLAYERSETTINGSWIDGETPRIVATE_H

#include <QObject>

#include "stages.h"
#include "stagesmodel.h"

namespace Ui {
class PlayerSettingsWidget;
}

class PlayerSettingsWidgetPrivate : public QObject
{
    Q_OBJECT
    friend class PlayerSettingsWidget;

public:
    explicit PlayerSettingsWidgetPrivate(QWidget *parent = 0);
    virtual ~PlayerSettingsWidgetPrivate();

private slots:
    void on_toolButtonAdd_clicked();
    void on_toolButtonRemove_clicked();

private:


private:
    Ui::PlayerSettingsWidget *ui;
    Player::Stages m_stages;
    QString m_stagesPath;
    StagesModel m_stagesModel;
};

#endif // PLAYERSETTINGSWIDGETPRIVATE_H
