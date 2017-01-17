#ifndef CHARTSSETTINGSWIDGET_H
#define CHARTSSETTINGSWIDGET_H

#include "AbstractSettingsWidget.h"

class ChartsSettingsWidgetPrivate;

class ChartsSettingsWidget : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    explicit ChartsSettingsWidget(bool isInterfaceEditable,
                                  QWidget *parent = 0);
    virtual ~ChartsSettingsWidget();

    void setCustomValues(const QStringList& values);

    // AbstractSettingsWidget interface
public:
    bool isSettingsValid();
    QString settingsInvalidText();

public slots:
    void settingsLoad();
    void settingsSave();

private:
    ChartsSettingsWidgetPrivate* m_Private;
};

#endif // CHARTSSETTINGSWIDGET_H
