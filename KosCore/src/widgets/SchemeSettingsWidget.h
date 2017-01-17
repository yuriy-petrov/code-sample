#ifndef SCHEMESETTINGSWIDGET_H
#define SCHEMESETTINGSWIDGET_H

#include "AbstractSettingsWidget.h"

namespace Ui
{
    class SchemeSettingsWidget;
}

class SchemeSettingsWidget : public AbstractSettingsWidget
{

    Q_OBJECT

public:

    explicit SchemeSettingsWidget(QWidget * parent = 0);
    ~SchemeSettingsWidget();

    virtual bool isSettingsValid();
    virtual QString settingsInvalidText();

public slots:

    virtual void settingsLoad();
    virtual void settingsSave();

private:

    Ui::SchemeSettingsWidget * ui;

};

#endif // SCHEMESETTINGSWIDGET_H
