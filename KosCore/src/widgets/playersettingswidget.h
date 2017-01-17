#ifndef PLAYERSETTINGSWIDGET_H
#define PLAYERSETTINGSWIDGET_H

#include <QWidget>
#include <AbstractSettingsWidget.h>

class PlayerSettingsWidgetPrivate;

class PlayerSettingsWidget : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    explicit PlayerSettingsWidget(bool isInterfaceEditable,
                                  QWidget *parent = 0);
    virtual ~PlayerSettingsWidget();

    // AbstractSettingsWidget interface
public:
    bool isSettingsValid();
    QString settingsInvalidText();

public slots:
    void settingsLoad();
    void settingsSave();

private:
    PlayerSettingsWidgetPrivate* m_private;
};

#endif // PLAYERSETTINGSWIDGET_H
