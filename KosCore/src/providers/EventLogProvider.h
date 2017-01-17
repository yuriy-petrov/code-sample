#ifndef EVENTLOGPROVIDER_H
#define EVENTLOGPROVIDER_H

class AbstractEventLogElement;

#include <QObject>

class EventLogProvider : public QObject
{

    Q_OBJECT

public:

    explicit EventLogProvider(QObject * parent = 0);
    virtual ~EventLogProvider();

    QString lastError() const;

    void fromJsonObject(const QJsonObject & jsonObject);
    QJsonObject toJsonObject() const;

    QList<AbstractEventLogElement*> eventLogElements() const;

public slots:

    void clear();

    bool load(const QString & filepath);
    bool save(const QString & filepath);

    void appendEventLogElement(AbstractEventLogElement * eventLogElement);

signals:

    void changed();

private:

    QList<AbstractEventLogElement*> m_eventLogElements;

    QString m_lastError;

};

#endif // EVENTLOGPROVIDER_H
