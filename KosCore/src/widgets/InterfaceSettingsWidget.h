#ifndef INTERFACESETTINGSWIDGET_H
#define INTERFACESETTINGSWIDGET_H

#include <AbstractSettingsWidget.h>
#include <TranslationManager.h>

namespace Ui
{
    class InterfaceSettingsWidget;
}

class InterfaceSettingsWidget : public AbstractSettingsWidget
{

    Q_OBJECT

public:

    InterfaceSettingsWidget(TranslationManager * translationManager,
                            QWidget * parent = 0);
    virtual ~InterfaceSettingsWidget();

    virtual bool isSettingsValid() override;
    virtual QString settingsInvalidText() override;

public slots:

    virtual void settingsLoad() override;
    virtual void settingsSave() override;

private slots:
    void on_tbTranslationsDir_clicked();

private:

    Ui::InterfaceSettingsWidget * ui;

    TranslationManager * m_translationManager;

};

#endif // INTERFACESETTINGSWIDGET_H
