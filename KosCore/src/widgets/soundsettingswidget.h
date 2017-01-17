#ifndef SOUNDSETTINGSWIDGET_H
#define SOUNDSETTINGSWIDGET_H

#include <AbstractSettingsWidget.h>

class SoundSettingsWidgetPrivate;

class SoundSettingsWidget : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    explicit SoundSettingsWidget(bool isInterfaceEditable,
                                 QWidget *parent = 0);
    ~SoundSettingsWidget();

    // AbstractSettingsWidget interface
public:
    virtual bool isSettingsValid();
    virtual QString settingsInvalidText();

public slots:
    virtual void settingsLoad();
    virtual void settingsSave();

private:
    SoundSettingsWidgetPrivate * m_private;
};

#endif // SOUNDSETTINGSWIDGET_H
