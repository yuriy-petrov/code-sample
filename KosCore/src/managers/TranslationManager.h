#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

class QTranslator;

#include "SettingsStorage.h"

#include <QObject>
#include <QSet>

class TranslationManager : public QObject
{

    Q_OBJECT

public:

    TranslationManager(SettingsStorage * settingsStorage,
                       QObject * parent = 0);

    QStringList languages() const;

private slots:

    void init();

private:

    SettingsStorage * m_settingsStorage;

    QString m_language;

    QSet<QTranslator*> m_translators;

};

#endif // TRANSLATIONMANAGER_H
