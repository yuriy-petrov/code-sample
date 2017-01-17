#include "SnapshotCondition.h"
#include "StringsKeys.h"
#include "modeltypeshelper.h"

#include <filedatastorage.h>
#include <QJsonArray>
#include <QMap>

SnapshotCondition::SnapshotCondition(QObject * parent) :
    QObject(parent)
{

}

SnapshotCondition::~SnapshotCondition()
{

}

SnapshotCondition & SnapshotCondition::operator = (SnapshotCondition & other)
{
    m_conditions = other.m_conditions;
    return *this;
}

QJsonObject SnapshotCondition::toJsonObject() const
{
    QJsonObject jsonObject;

    QJsonArray jsonArrayConditions;
    foreach (SnapshotCondition::Condition condition, m_conditions)
    {
        QJsonObject jsonObjectCondition;
        jsonObjectCondition.insert("key", condition.key);
        jsonObjectCondition.insert("type", condition.type);
        jsonObjectCondition.insert("value_min", Model::TypesHelper::toJsonValue(condition.key, condition.valueMin));
        jsonObjectCondition.insert("value_max", Model::TypesHelper::toJsonValue(condition.key, condition.valueMax));
        jsonObjectCondition.insert("inverse", condition.inverse);
        jsonArrayConditions.append(jsonObjectCondition);
    }
    jsonObject.insert("conditions", jsonArrayConditions);

    return jsonObject;
}

void SnapshotCondition::fromJsonObject(const QJsonObject & jsonObject)
{
    m_conditions.clear();
    foreach (QJsonValue jsonValueCondition, jsonObject.value("conditions").toArray())
    {
        QJsonObject jsonObjectCondition = jsonValueCondition.toObject();
        SnapshotCondition::Condition condition;
        condition.key = jsonObjectCondition.value("key").toString();
        condition.type = static_cast<Condition::Type>(jsonObjectCondition.value("type").toInt());
        condition.valueMin = Model::TypesHelper::fromJsonValue(condition.key, jsonObjectCondition.value("value_min"));
        condition.valueMax = Model::TypesHelper::fromJsonValue(condition.key, jsonObjectCondition.value("value_max"));
        condition.inverse = jsonObjectCondition.value("inverse").toBool();
        m_conditions.append(condition);
    }
}

QList<SnapshotCondition::Condition> SnapshotCondition::conditions() const
{
    return m_conditions;
}

void SnapshotCondition::setConditions(const QList<SnapshotCondition::Condition> & conditions)
{
    m_conditions = conditions;
}

bool SnapshotCondition::check(FileDataStorage * fileDataStorage, const QDateTime & datetime, QString & errorText)
{
    if (m_conditions.isEmpty())
    {
        return true;
    }

    QList<Snapshot::Key> keys;
    foreach (SnapshotCondition::Condition condition, m_conditions)
    {
        keys.append(condition.key);
    }

    QList<Snapshot> snapshots = fileDataStorage->load(datetime.toMSecsSinceEpoch(), datetime.toMSecsSinceEpoch(), keys);
    if (snapshots.isEmpty())
    {
        errorText = tr("snapshots not found");
        return false;
    }

    Snapshot snapshot = snapshots.last();
    foreach (SnapshotCondition::Condition condition, m_conditions)
    {
        bool result = false;

        switch(condition.type) {
            case Condition::Range:
            {
                QVariant value = snapshot.value(condition.key);
                result = (value > condition.valueMin && value < condition.valueMax);
                break;
            }
            case Condition::Equality:
            {
                result = (snapshot.value(condition.key) == condition.valueMin);
                break;
            }
        }

        QString str1 = tr("Possible");
        if (condition.inverse)
        {
            str1 = tr("Impossible");
            result = !result;
        }

        if (!result)
        {
            switch(condition.type) {
                case Condition::Range:
                {
                    errorText = tr("Value %1 is %2. %3 range %4-%5.")
                                .arg(condition.key)
                                .arg(Model::TypesHelper::toString(condition.key, snapshot.value(condition.key)))
                                .arg(str1)
                                .arg(Model::TypesHelper::toString(condition.key, condition.valueMin))
                                .arg(Model::TypesHelper::toString(condition.key, condition.valueMax));
                    break;
                }
                case Condition::Equality:
                {
                    errorText = tr("Value %1 is %2. %3 is %4.")
                                .arg(condition.key)
                                .arg(Model::TypesHelper::toString(condition.key, snapshot.value(condition.key)))
                                .arg(str1)
                                .arg(Model::TypesHelper::toString(condition.key, condition.valueMin));
                    break;
                }
            }

            return false;
        }
    }

    return true;
}

QString SnapshotCondition::description() const
{
    QStringList result;

    foreach(const Condition& cond, m_conditions) {
        QString descr;
        QString opStr = cond.inverse ?
                            "!=" :
                            "=";
        switch(cond.type) {
            case Condition::Equality:
            {
                descr = tr("%1 %2 %3")
                        .arg(cond.key)
                        .arg(opStr)
                        .arg(Model::TypesHelper::toString(cond.key, cond.valueMin));
                break;
            }
            case Condition::Range:
            {
                descr = tr("%1 %2 (%3..%4)")
                        .arg(cond.key)
                        .arg(opStr)
                        .arg(Model::TypesHelper::toString(cond.key, cond.valueMin))
                        .arg(Model::TypesHelper::toString(cond.key, cond.valueMax));
                break;
            }
        }

        result << descr;
    }

    return result.join(QChar('\n'));
}

QMap<SnapshotCondition::Condition::Type, QString> _initTypeNames()
{
    QMap<SnapshotCondition::Condition::Type, QString> names;

    names.insert(SnapshotCondition::Condition::Type::Range, QObject::tr("Range"));
    names.insert(SnapshotCondition::Condition::Type::Equality, QObject::tr("Equality"));

    return names;
}

static QMap<SnapshotCondition::Condition::Type, QString> TYPE_NAMES = _initTypeNames();

QStringList SnapshotCondition::typeNames()
{
    return TYPE_NAMES.values();
}

const QString SnapshotCondition::typeToString(SnapshotCondition::Condition::Type type)
{
    return TYPE_NAMES.value(type);
}

SnapshotCondition::Condition::Type SnapshotCondition::stringToType(const QString &string)
{
    return TYPE_NAMES.key(string);
}

