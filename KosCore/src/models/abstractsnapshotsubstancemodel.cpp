#include <StringsKeys.h>

#include "abstractsnapshotsubstancemodel.h"

QMap<KosTypes::SubstanceType, QString> initSubstanceNames()
{
    QMap<KosTypes::SubstanceType, QString> map;

    map.insert(KosTypes::Nothing, QObject::tr("Nothing"));
    map.insert(KosTypes::Oxygen, QObject::tr("Oxygen"));
    map.insert(KosTypes::Hydrogen, QObject::tr("Hydrogen"));
    map.insert(KosTypes::Nitrogen, QObject::tr("Nitrogen"));
    map.insert(KosTypes::Water, QObject::tr("Water"));
    map.insert(KosTypes::Alkali, QObject::tr("Electrolyte"));

    return map;
}

const QMap<KosTypes::SubstanceType, QString> AbstractSnapshotSubstanceModel::m_SubstanceNamesMap = initSubstanceNames();

AbstractSnapshotSubstanceModel::AbstractSnapshotSubstanceModel(QObject *parent)
    : SnapshotTableModel(parent)
{
}

QStringList AbstractSnapshotSubstanceModel::substanceNames()
{
    return m_SubstanceNamesMap.values();

}

QString AbstractSnapshotSubstanceModel::substanceName(KosTypes::SubstanceType substance)
{
    return m_SubstanceNamesMap.contains(substance) ?
                m_SubstanceNamesMap[substance] :
                QString();
}

KosTypes::SubstanceType AbstractSnapshotSubstanceModel::substanceByName(const QString& name)
{
    foreach(const KosTypes::SubstanceType substance, m_SubstanceNamesMap.keys()) {
        if(m_SubstanceNamesMap[substance] == name) {
            return substance;
        }
    }

    return KosTypes::Nothing;
}

void AbstractSnapshotSubstanceModel::setSnapshot(Snapshot *snapshot)
{
    foreach(const Snapshot::Key& key, m_Values) {
        if(!snapshot->contains(key)) {
            snapshot->setValue(key, newTypedValue(), 0);
        }
    }

    SnapshotTableModel::setSnapshot(snapshot);
}

QVariant AbstractSnapshotSubstanceModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const Snapshot::Key& value = m_Values.at(index.row());

    if(index.column() == substanceColumn()) {
        switch(role) {
        case Qt::DisplayRole:
        {
            return substanceName(substance(value));
        }
        case Qt::EditRole:
        {
            return substanceNames();
        }
        default: break;
        }
    }

    return QVariant();
}

bool AbstractSnapshotSubstanceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) {
        return false;
    }

    const QString data = value.toString();
    const Snapshot::Key& valueKey = m_Values.at(index.row());

    if(index.column() == substanceColumn()) {
        setSubstance(valueKey, substanceByName(data));
        emit dataChanged(index.model()->index(index.row(), 0),
                         index.model()->index(index.row(), columnCount() - 1),
                         QVector<int>() << Qt::DisplayRole);
    }

    return false;
}

QVariant AbstractSnapshotSubstanceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(
            (role == Qt::DisplayRole) &&
            (orientation == Qt::Horizontal) &&
            (section == substanceColumn())
            )
    {
        return tr("Substance");
    } else {
        return SnapshotTableModel::headerData(section, orientation, role);
    }
}

Qt::ItemFlags AbstractSnapshotSubstanceModel::flags(const QModelIndex &index) const
{
    if(index.column() == substanceColumn()) {
        return
                Qt::ItemIsEnabled |
                Qt::ItemIsSelectable |
                Qt::ItemIsEditable;
    } else {
        return SnapshotTableModel::flags(index);
    }
}
