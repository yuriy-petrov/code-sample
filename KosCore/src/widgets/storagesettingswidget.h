#ifndef STORAGESETTINGSWIDGET_H
#define STORAGESETTINGSWIDGET_H

class GroupSchemeSceneManager;

#include "AbstractSettingsWidget.h"

#include <QWidget>
#include <QToolButton>
#include <QLineEdit>

namespace Ui
{
    class StorageSettingsWidget;
}

class StorageSettingsWidget : public AbstractSettingsWidget
{

    Q_OBJECT

public:

    StorageSettingsWidget(bool isInterfaceEditable,
                          GroupSchemeSceneManager * groupSchemeSceneManager,
                          QWidget *parent = 0);
    ~StorageSettingsWidget();

public:

    bool isSettingsValid();
    QString settingsInvalidText();

public slots:

    void settingsLoad();
    void settingsSave();

private slots:

    void toolButtonScheme_clicked();
    void on_toolButtonStorageRoot_clicked();
    void on_toolButtonExercisesRoot_clicked();

private:

    Ui::StorageSettingsWidget * ui;

    GroupSchemeSceneManager * m_groupSchemeSceneManager;

    QHash<QString,QLineEdit*> m_schemeLineEdits;
    QHash<QString,QToolButton*> m_schemeToolButtons;
};

#endif // STORAGESETTINGSWIDGET_H
