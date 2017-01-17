#ifndef TROUBLE_H
#define TROUBLE_H

#include <QString>
#include <QJsonObject>
#include <QList>
#include <QJsonArray>

class Trouble
{

public:

    Trouble();
    Trouble(QString key, QString description);

    QString key() const;
    QString description() const;
    void setDescription(const QString & description);

    void fromJsonObject(const QJsonObject & jsonObject);
    QJsonObject toJsonObject();

    static QList<Trouble> troubleListFromJsonArray(const QJsonArray & jsonArray);
    static QJsonArray troubleListToJsonArray(const QList<Trouble> & troubleList);

private:

    QString m_key;
    QString m_description;

};

#endif // TROUBLE_H
