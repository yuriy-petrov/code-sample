#ifndef GROUPSCHEMESCENEMANAGER_H
#define GROUPSCHEMESCENEMANAGER_H

class SchemeSceneManager;
class SettingsStorage;

#include <QHash>
#include <QObject>
#include <QStringList>

class GroupSchemeSceneManager : public QObject
{

    Q_OBJECT

public:

    GroupSchemeSceneManager(SettingsStorage * settingsStorage,
                            QObject * parent = 0);
    ~GroupSchemeSceneManager();

    QStringList schemeKeys() const;
    SchemeSceneManager * schemeSceneManager(const QString & key) const;
    QString schemeTitle(const QString & key) const;

public slots:

    virtual void initialize();

protected:

    SchemeSceneManager * registerScheme(const QString & key, const QString & title);
    virtual SchemeSceneManager * createScheme();

protected:

    SettingsStorage * m_settingsStorage;

private:

    QStringList m_schemeKeys;
    QHash<QString,SchemeSceneManager*> m_schemeSceneManagers;
    QHash<QString,QString> m_schemeTitles;

};

#endif // GROUPSCHEMESCENEMANAGER_H
