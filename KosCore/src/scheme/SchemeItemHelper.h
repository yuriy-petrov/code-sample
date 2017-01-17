#ifndef SCHEMEITEMHELPER_H
#define SCHEMEITEMHELPER_H

class SettingsStorage;
class SchemeScene;

#include <QObject>

class SchemeItemHelper : public QObject
{

    Q_OBJECT

public:

    SchemeItemHelper(SettingsStorage * settingsStorage,
                     SchemeScene * schemeScene,
                     QObject * parent = 0);
    virtual ~SchemeItemHelper();

    SettingsStorage * settingsStorage() const;
    SchemeScene * schemeScene() const;

protected:

    SettingsStorage * m_settingsStorage;
    SchemeScene * m_schemeScene;

};

#endif // SCHEMEITEMHELPER_H
