#ifndef SERVERSETTINGSWIDGET_H
#define SERVERSETTINGSWIDGET_H

#include "AbstractSettingsWidget.h"

namespace Ui
{
    class ServerSettingsWidget;
}

class ServerSettingsWidget : public AbstractSettingsWidget
{

    Q_OBJECT

public:

    explicit ServerSettingsWidget(bool isInterfaceEditable,
                                  QWidget * parent = 0);
    ~ServerSettingsWidget();

    virtual bool isSettingsValid() override;
    virtual QString settingsInvalidText() override;

public slots:

    virtual void settingsLoad() override;
    virtual void settingsSave() override;

private slots:

    void on_tbHostAddress_clicked();

private:

    Ui::ServerSettingsWidget * ui;

};

#endif // SERVERSETTINGSWIDGET_H
