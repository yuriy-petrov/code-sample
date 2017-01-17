#ifndef EXERCISE_H
#define EXERCISE_H

class EventFilterProvider;

#include <QString>
#include <QByteArray>
#include <QJsonObject>
#include <QSharedPointer>
#include <QObject>

#include <snapshot.h>

class Exercise : public QObject
{
    Q_OBJECT

public:

    typedef QSharedPointer<Exercise> Pointer;
    virtual ~Exercise();

public:

    static Exercise::Pointer create();

    bool load(const QString & filepath);
    bool save(const QString & filepath);
    void clear();

    EventFilterProvider * stagesEventFilterProvider() const;
    EventFilterProvider * modesEventFilterProvider() const;

    QString lastError() const;

    bool isEmpty() const;

    bool isModified();

    QString filePath() const;

    QString title() const;
    void setTitle(const QString& title);

    Snapshot initialValues() const;
    void setInitialValues(const Snapshot& snapshot);

    QString defaultSchemeKey() const;
    void setDefaultSchemeKey(const QString &defaultSchemeKey);

    QJsonObject toJsonObject();
    static Exercise::Pointer fromJsonObject(const QJsonObject & jsonObject);

signals:

    void changed();

protected:

    Exercise(QObject * parent = 0);

private:
    void loadFromJsonObject(const QJsonObject & jsonObject);

private:

    EventFilterProvider * m_stagesEventFilterProvider;
    EventFilterProvider * m_modesEventFilterProvider;

    bool m_isModified;

    QString m_filePath;

    QString m_title;

    Snapshot m_InitialValues;

    QString m_defaultSchemeKey;

    QString m_lastError;


};

#endif // EXERCISE_H
