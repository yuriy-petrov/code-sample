#ifndef MODELSETTINGSWIDGET_H
#define MODELSETTINGSWIDGET_H

#include "AbstractSettingsWidget.h"

class ModelSettingsWidgetPrivate;

class ModelSettingsWidget : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    explicit ModelSettingsWidget(bool isInterfaceEditable,
                                 QWidget *parent = 0);
    virtual ~ModelSettingsWidget();

    // AbstractSettingsWidget interface
public:
    bool isSettingsValid();
    QString settingsInvalidText();

public slots:
    void settingsLoad();
    void settingsSave();

private:
    ModelSettingsWidgetPrivate* m_Private;
};

#endif // MODELSETTINGSWIDGET_H
