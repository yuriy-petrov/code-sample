#ifndef SNAPSHOTCONDITION_H
#define SNAPSHOTCONDITION_H

class FileDataStorage;

#include <QObject>
#include <QVariant>
#include <QJsonObject>

class SnapshotCondition: public QObject
{

public:

    struct Condition
    {
        enum Type {
            Range,
            Equality
        };

        Type type;
        QString key;
        QVariant valueMin;
        QVariant valueMax;
        bool inverse;

        Condition()
        {
            type = Range;
            inverse = false;
        }

    };

    SnapshotCondition(QObject * parent = 0);
    ~SnapshotCondition();

    SnapshotCondition & operator = (SnapshotCondition & other);

    QJsonObject toJsonObject() const;
    void fromJsonObject(const QJsonObject & jsonObject);

    QList<SnapshotCondition::Condition> conditions() const;
    void setConditions(const QList<SnapshotCondition::Condition> & conditions);

    bool check(FileDataStorage * fileDataStorage, const QDateTime & datetime, QString & errorText);

    QString description() const;

    static QStringList typeNames();
    static const QString typeToString(Condition::Type type);
    static Condition::Type stringToType(const QString& string);

private:

    QList<SnapshotCondition::Condition> m_conditions;

};

#endif // SNAPSHOTCONDITION_H
