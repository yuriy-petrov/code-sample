#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "SettingsStorage.h"

#include <QObject>

class SettingsManager : public QObject
{

    Q_OBJECT

public:

    SettingsManager(QObject * parent = 0, const QString &filename = QString());

    SettingsStorage * settingsStorage() const;

private:

    void createDefaultSettings();

private:

    SettingsStorage * m_settingsStorage;

};

#endif // SETTINGSMANAGER_H
