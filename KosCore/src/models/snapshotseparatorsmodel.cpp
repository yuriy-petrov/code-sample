#include "snapshotseparatorsmodel.h"
#include "abstractsnapshotsubstancemodel.h"
#include "modeltypes.h"

SnapshotSeparatorsModel::SnapshotSeparatorsModel(QObject *parent)
    : SnapshotTableModel(parent)
{
}

void SnapshotSeparatorsModel::setSnapshot(Snapshot *snapshot)
{
    foreach(const Snapshot::Key& key, m_Values) {
        if(!snapshot->contains(key)) {
            snapshot->setValue(key, Model::Separator().toVariant(), 0);
        }
    }

    SnapshotTableModel::setSnapshot(snapshot);
}

int SnapshotSeparatorsModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant SnapshotSeparatorsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const Snapshot::Key& value = m_Values.at(index.row());
    const Model::Separator separator = m_Snapshot->value(value).value<Model::Separator>();

    switch(index.column()) {
    case COL_FLUID_SUBSTANCE:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            return AbstractSnapshotSubstanceModel::substanceName(separator.fluid());
        }
        case Qt::EditRole:
        {
            return AbstractSnapshotSubstanceModel::substanceNames();
        }
        default: break;
        }
        break;
    }
    case COL_GAS_SUBSTANCE:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            return AbstractSnapshotSubstanceModel::substanceName(separator.gas());
        }
        case Qt::EditRole:
        {
            return AbstractSnapshotSubstanceModel::substanceNames();
        }
        default: break;
        }
        break;
    }
    case COL_FLUID_LEVEL:
    {
        switch(role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            return separator.fluidLevel();
        }
        default: break;
        }
        break;
    }
    }

    return QVariant();
}

bool SnapshotSeparatorsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) {
        return false;
    }

    const QString data = value.toString();
    const Snapshot::Key& valueKey = m_Values.at(index.row());
    Model::Separator separator = m_Snapshot->value(valueKey).value<Model::Separator>();

    switch(index.column()) {
    case COL_FLUID_SUBSTANCE:
    {
        separator.setFluid(AbstractSnapshotSubstanceModel::substanceByName(data));
        m_Snapshot->setValue(valueKey, separator.toVariant());
        emit dataChanged(index.model()->index(index.row(), index.column()),
                         index.model()->index(index.row(), index.column()),
                         QVector<int>() << Qt::DisplayRole);
        return true;
    }
    case COL_GAS_SUBSTANCE:
    {
        separator.setGas(AbstractSnapshotSubstanceModel::substanceByName(data));
        m_Snapshot->setValue(valueKey, separator.toVariant());
        emit dataChanged(index.model()->index(index.row(), index.column()),
                         index.model()->index(index.row(), index.column()),
                         QVector<int>() << Qt::DisplayRole);
    }
    case COL_FLUID_LEVEL:
    {
        separator.setFluidLevel(value.toInt());
        m_Snapshot->setValue(valueKey, separator.toVariant());
        emit dataChanged(index.model()->index(index.row(), index.column()),
                         index.model()->index(index.row(), index.column()),
                         QVector<int>() << Qt::DisplayRole);
        return true;
    }
    }

    return false;
}

QVariant SnapshotSeparatorsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation) {
    case Qt::Horizontal:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            switch(section) {
            case COL_FLUID_LEVEL:
            {
                return tr("Fluid level");
            }
            case COL_FLUID_SUBSTANCE:
            {
                return tr("Fluid");
            }
            case COL_GAS_SUBSTANCE:
            {
                return tr("Gas");
            }
            }
            break;
        }
        default:
        {
            break;
        }
        }

        break;
    }
    case Qt::Vertical:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            return m_Values.at(section);
        }
        default:
        {
            break;
        }
        }

        break;
    }
    }

    return QVariant();
}

Qt::ItemFlags SnapshotSeparatorsModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}
