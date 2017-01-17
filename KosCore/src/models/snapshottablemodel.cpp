#include "snapshottablemodel.h"

SnapshotTableModel::SnapshotTableModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_Snapshot(NULL)
{
}

void SnapshotTableModel::setSnapshot(Snapshot *snapshot)
{
    beginResetModel();
    m_Snapshot = snapshot;
    endResetModel();
}

void SnapshotTableModel::setValues(const QList<Snapshot::Key> &values)
{
    beginResetModel();
    m_Values = values;
    qSort(m_Values);
    endResetModel();
}


int SnapshotTableModel::rowCount(const QModelIndex &parent) const
{
    return m_Values.size();
}

int SnapshotTableModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant SnapshotTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const Snapshot::Key& value = m_Values.at(index.row());

    switch(role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
    {
        switch(index.column()) {
        case COL_VALUE:
        {
            return m_Snapshot->value(value);
            break;
        }
        }

        break;
    }
    default:
    {
        break;
    }
    }

    return QVariant();
}

bool SnapshotTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!value.canConvert<double>()) {
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
        return false;
    }

    m_Snapshot->setValue(m_Values.at(index.row()), value.toDouble(), 0);
    emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);

    return true;
}

QVariant SnapshotTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation) {
    case Qt::Horizontal:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            switch(section) {
            case COL_VALUE:
            {
                return tr("Value");
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

Qt::ItemFlags SnapshotTableModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}
