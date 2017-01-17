#include "TranslationManager.h"

#include "StringsKeys.h"
#include "SettingsStorage.h"

#include <QDir>
#include <QFileInfo>
#include <QTranslator>
#include <QApplication>
#include <QLibraryInfo>

TranslationManager::TranslationManager(SettingsStorage * settingsStorage,
                                       QObject * parent) :
    QObject(parent),
    m_settingsStorage(settingsStorage)
{
    init();
    m_settingsStorage->setHandler(SettingsKeys::LANGUAGE, this, SLOT(init()));
}

QStringList TranslationManager::languages() const
{
    QString translationsDirpath = m_settingsStorage->value(SettingsKeys::TRANSLATION_DIR).toString();
    return translationsDirpath.isEmpty() ? QStringList() : QDir(translationsDirpath).entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
}

void TranslationManager::init()
{
    QString translationsDirpath = m_settingsStorage->value(SettingsKeys::TRANSLATION_DIR).toString();
    m_language = m_settingsStorage->value(SettingsKeys::LANGUAGE).toString();

    qDeleteAll(m_translators);
    m_translators.clear();

    if (
            !translationsDirpath.isEmpty() &&
            !m_language.isEmpty() &&
            m_language != SettingsKeys::LANGUAGE_DEFAULT &&
            languages().contains(m_language)
        )
    {
        // KOS translations
        foreach (QFileInfo fi, QDir(QString("%1/%2").arg(translationsDirpath).arg(m_language)).entryInfoList(QStringList() << "*.qm", QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot))
        {
            QTranslator * translator = new QTranslator(this);

            if (translator->load(fi.absoluteFilePath()))
            {
                qApp->installTranslator(translator);
                m_translators.insert(translator);
            }
            else
            {
                delete translator;
            }
        }

        // System translations
        QTranslator * translator = new QTranslator(this);
        if (translator->load("qt_" + m_language, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        {
            m_translators.insert(translator);
            qApp->installTranslator(translator);
        }
        else
        {
            delete translator;
        }
    }
}
