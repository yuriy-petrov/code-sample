#include <QColor>

#include "conditionsmodel.h"

ConditionsModel::ConditionsModel(QObject *parent)
    : SnapshotTableModel(parent)
{
}

bool ConditionsModel::checkConditions()
{
    if(m_Snapshot == NULL) {
        return false;
    }

    bool isFulfilled = true;

    foreach(const Snapshot::Key& key, m_Values) {
        if(!m_Snapshot->value(key).toBool()) {
            isFulfilled = false;
            break;
        }
    }

    return isFulfilled;
}

void ConditionsModel::setSnapshot(Snapshot *snapshot)
{
    SnapshotTableModel::setSnapshot(snapshot);
    emit conditionsFullfilled(checkConditions());
}

void ConditionsModel::setValues(const QList<Snapshot::Key> &values)
{
    SnapshotTableModel::setValues(values);
    emit conditionsFullfilled(checkConditions());
}

QVariant ConditionsModel::data(const QModelIndex &index, int role) const
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
//    case Qt::BackgroundColorRole:
//    {
//        switch(index.column()) {
//        case COL_VALUE:
//        {
//            return m_Snapshot->value(value).toBool() ?
//                        QVariant::fromValue(QColor("green")) :
//                        QVariant::fromValue(QColor("red"));
//        }
//        }

//        break;
//    }
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

QVariant ConditionsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation) {
    case Qt::Vertical:
    {
        switch(role) {
        case Qt::ForegroundRole:
        {
            return m_Snapshot->value(m_Values.at(section)).toBool() ?
                        QVariant::fromValue(QColor("green")) :
                        QVariant::fromValue(QColor("red"));
        }
        default:
        {
            break;
        }
        }

        break;
    }
    }

    return SnapshotTableModel::headerData(section, orientation, role);
}

bool ConditionsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!value.canConvert<bool>()) {
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
        return false;
    }

    m_Snapshot->setValue(m_Values.at(index.row()), value.toBool(), 0);
    emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
    emit headerDataChanged(Qt::Vertical, index.row(), index.row());

    emit conditionsFullfilled(checkConditions());

    return true;
}


Qt::ItemFlags ConditionsModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsUserCheckable;
}
