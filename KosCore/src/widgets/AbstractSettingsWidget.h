#ifndef ABSTRACTSETTINGSWIDGET_H
#define ABSTRACTSETTINGSWIDGET_H

#include "SettingsStorage.h"

#include <QWidget>

class AbstractSettingsWidget : public QWidget
{

    Q_OBJECT

public:

    explicit AbstractSettingsWidget(QWidget * parent = 0);

    virtual bool isSettingsValid() = 0;
    virtual QString settingsInvalidText() = 0;

public slots:

    virtual void setSettingsStorage(SettingsStorage * settingsStorage);

    virtual void settingsLoad() = 0;
    virtual void settingsSave() = 0;

protected:

    SettingsStorage * m_settingsStorage;

};

#endif // ABSTRACTSETTINGSWIDGET_H
