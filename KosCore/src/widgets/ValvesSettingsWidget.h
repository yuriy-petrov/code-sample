#ifndef VALVESSETTINGSWIDGET_H
#define VALVESSETTINGSWIDGET_H

#include "AbstractSettingsWidget.h"

#include <QStringListModel>

namespace Ui
{
    class ValvesSettingsWidget;
}

class ValvesSettingsWidget : public AbstractSettingsWidget
{

    Q_OBJECT

public:

    ValvesSettingsWidget(bool isInterfaceEditable,
                         QWidget * parent = 0);
    ~ValvesSettingsWidget();

    virtual bool isSettingsValid();
    virtual QString settingsInvalidText();

public slots:

    virtual void settingsLoad();
    virtual void settingsSave();

private slots:
    void on_tbRemove_clicked();

    void on_tbAdd_clicked();

private:

    Ui::ValvesSettingsWidget * ui;

    QStringListModel * m_currentValvesModel;
    QStringListModel * m_availabelValvesModel;

};

#endif // VALVESSETTINGSWIDGET_H
