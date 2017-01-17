#ifndef TROUBLELISTSETTINGSWIDGET_H
#define TROUBLELISTSETTINGSWIDGET_H

class TroubleListModel;

#include <AbstractSettingsWidget.h>

namespace Ui
{
    class TroubleListSettingsWidget;
}

class TroubleListSettingsWidget : public AbstractSettingsWidget
{

    Q_OBJECT

public:

    explicit TroubleListSettingsWidget(QWidget * parent = 0);
    ~TroubleListSettingsWidget();

    virtual bool isSettingsValid();
    virtual QString settingsInvalidText();

public slots:

    virtual void settingsLoad();
    virtual void settingsSave();

private:

    Ui::TroubleListSettingsWidget * ui;

    TroubleListModel * m_troubleListModel;

};

#endif // TROUBLELISTSETTINGSWIDGET_H
