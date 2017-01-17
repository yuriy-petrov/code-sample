#include "cellstackenablemodel.h"

CellStackEnableModel::CellStackEnableModel(QObject *parent)
    : SnapshotTableModel(parent)
{
}


QVariant CellStackEnableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const Snapshot::Key& value = m_Values.at(index.row());

    switch(role) {
    case Qt::DisplayRole:
    {
        return QVariant();
    }
    case Qt::CheckStateRole:
    {
        switch(index.column()) {
        case COL_VALUE:
        {
            return m_Snapshot->value(value).toBool() ?
                        Qt::Checked :
                        Qt::Unchecked;
        }
        }

        break;
    }
    default:
    {
        break;
    }
    }

    return SnapshotTableModel::data(index, role);
}

bool CellStackEnableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!value.canConvert<bool>()) {
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
        return false;
    }

    m_Snapshot->setValue(m_Values.at(index.row()), value.toBool(), 0);
    emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
    emit headerDataChanged(Qt::Vertical, index.row(), index.row());

    return true;
}

Qt::ItemFlags CellStackEnableModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsUserCheckable;
}
