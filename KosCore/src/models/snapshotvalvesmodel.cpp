#include "snapshotvalvesmodel.h"
#include "valve.h"

QHash<Model::Valve::Status, QString> initValveStatusNames()
{
    QHash<Model::Valve::Status, QString> names;
    names.insert(Model::Valve::Normal, QObject::tr("Normal"));
    names.insert(Model::Valve::Faulted, QObject::tr("Faulted"));
    return names;
}

QHash<bool, QString> initValvePositionNames()
{
    QHash<bool, QString> names;
    names.insert(true, QObject::tr("Opened"));
    names.insert(false, QObject::tr("Closed"));
    return names;
}

static QHash<Model::Valve::Status, QString> VALVE_STATUS_NAMES = initValveStatusNames();
static QHash<bool, QString> VALVE_POSITION_NAMES = initValvePositionNames();


SnapshotValvesModel::SnapshotValvesModel(QObject *parent)
    : SnapshotTableModel(parent)
{
}

void SnapshotValvesModel::setSnapshot(Snapshot *snapshot)
{
    foreach(const Snapshot::Key& key, m_Values) {
        if(!snapshot->contains(key)) {
            snapshot->setValue(key, Model::Valve::closed(KosTypes::Nothing).toVariant(), 0);
        }
    }

    SnapshotTableModel::setSnapshot(snapshot);
}

int SnapshotValvesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )
    return 3;
}

QVariant SnapshotValvesModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const Snapshot::Key& value = m_Values.at(index.row());
    const Model::Valve valve = m_Snapshot->value(value).value<Model::Valve>();

    switch(index.column()) {
    case COL_POSITION:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            return VALVE_POSITION_NAMES[valve.isOpen()];
        }
        case Qt::EditRole:
        {
            return QStringList(VALVE_POSITION_NAMES.values());
        }
        default: break;
        }

        break;
    }
    case COL_CLOSING_LEVEL:
    {
        switch(role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            return valve.closingLevel();
        }
        default: break;
        }

        break;
    }
    case COL_STATUS:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            return VALVE_STATUS_NAMES[valve.status()];
        }
        case Qt::EditRole:
        {
            return QStringList(VALVE_STATUS_NAMES.values());
        }
        default: break;
        }

        break;
    }
    }

    return QVariant();
}

bool SnapshotValvesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) {
        return false;
    }

    const QString data = value.toString();
    const Snapshot::Key& valueKey = m_Values.at(index.row());
    Model::Valve valve = m_Snapshot->value(valueKey).value<Model::Valve>();

    switch(index.column()) {
    case COL_POSITION:
    {
        foreach(bool key, VALVE_POSITION_NAMES.keys()) {
            if(data == VALVE_POSITION_NAMES[key]) {
                key ? valve.open() : valve.close();
                m_Snapshot->setValue(valueKey, valve.toVariant(), 0);
                emit dataChanged(index.model()->index(index.row(), COL_POSITION),
                                 index.model()->index(index.row(), COL_CLOSING_LEVEL),
                                 QVector<int>() << Qt::DisplayRole);
                return true;
            }
        }

        break;
    }
    case COL_CLOSING_LEVEL:
    {
        valve.setClosingLevel(value.toDouble());
        m_Snapshot->setValue(valueKey, valve.toVariant(), 0);
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
        return true;
    }
    case COL_STATUS:
    {
        foreach(Model::Valve::Status key, VALVE_STATUS_NAMES.keys()) {
            if(data == VALVE_STATUS_NAMES[key]) {
                valve.setStatus(key);
                m_Snapshot->setValue(valueKey, valve.toVariant(), 0);
                emit dataChanged(index.model()->index(index.row(), COL_POSITION),
                                 index.model()->index(index.row(), COL_CLOSING_LEVEL),
                                 QVector<int>() << Qt::DisplayRole);
                return true;
            }
        }

        break;
    }
    }

    return false;
}

QVariant SnapshotValvesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation) {
    case Qt::Horizontal:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            switch(section) {
            case COL_POSITION:
            {
                return tr("Position");
            }
            case COL_CLOSING_LEVEL:
            {
                return tr("Closing level");
            }
            case COL_STATUS:
            {
                return tr("Status");
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
        default: break;
        }

        break;
    }
    }

    return QVariant();
}


Qt::ItemFlags SnapshotValvesModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}
