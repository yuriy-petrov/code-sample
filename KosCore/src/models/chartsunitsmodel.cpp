#include "chartsunitsmodel.h"

ChartsUnitsModel::ChartsUnitsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void ChartsUnitsModel::setUnits(const ChartsUnits &units)
{
    beginResetModel();

    m_Units = units;

    m_Names = m_Units.keys();
    qSort(m_Names);

    endResetModel();
}


int ChartsUnitsModel::rowCount(const QModelIndex &parent) const
{
    return m_Names.size();
}

int ChartsUnitsModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant ChartsUnitsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const QString name = m_Names.at(index.row());

    switch(index.column())
    {
    case COL_NAME:
    {
        switch(role) {
        case Qt::EditRole:
        case Qt::DisplayRole:
        {
            return name;
        }
        default: break;
        }

        break;
    }
    case COL_LOWER:
    {
        switch(role) {
        case Qt::EditRole:
        {
            return m_Units[name].lower();
        }
        case Qt::DisplayRole:
        {
            return QString::number(m_Units[name].lower(), 'f');
        }
        default: break;
        }

        break;
    }
    case COL_UPPER:
    {
        switch(role) {
        case Qt::EditRole:
        {
            return m_Units[name].upper();
        }
        case Qt::DisplayRole:
        {
            return QString::number(m_Units[name].upper(), 'f');
        }
        default: break;
        }

        break;
    }
    }

    return QVariant();
}

bool ChartsUnitsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    const QString name = m_Names.at(index.row());

    switch(index.column()) {
    case COL_NAME:
    {
        if(value.toString().isEmpty()) {
            return false;
        }
        ChartsUnit unit = m_Units[name];
        m_Units.remove(name);
        unit.setName(value.toString());
        m_Units.setUnit(unit);
        m_Names.replace(m_Names.indexOf(name), unit.name());
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
        return true;
    }
    case COL_LOWER:
    {
        bool isOk;
        double val = value.toDouble(&isOk);

        if(!isOk) {
            return false;
        }

        m_Units[name].setLower(val);
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);

        return true;
    }
    case COL_UPPER:
    {
        bool isOk;
        double val = value.toDouble(&isOk);

        if(!isOk) {
            return false;
        }

        m_Units[name].setUpper(val);
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);

        return true;
    }
    }

    return false;
}

QVariant ChartsUnitsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation) {
    case Qt::Horizontal:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            switch(section) {
            case COL_NAME:
            {
                return tr("Name");
            }
            case COL_LOWER:
            {
                return tr("Lower limit");
            }
            case COL_UPPER:
            {
                return tr("Upper limit");
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
        break;
    }
    }

    return QVariant();
}

Qt::ItemFlags ChartsUnitsModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}


bool ChartsUnitsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    for(int i = 0; i < count; ++i) {
        ChartsUnit unit(tr("enter units..."), 0, 0);
        m_Units.setUnit(unit);
        m_Names.insert(row, unit.name());
    }

    endInsertRows();

    return true;
}

bool ChartsUnitsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    for(int i = row; i < row + count; ++i) {
        m_Units.remove(m_Names.at(i));
    }

    foreach(const QString& name, m_Names) {
        if(!m_Units.contains(name)) {
            m_Names.removeOne(name);
        }
    }

    endRemoveRows();
}
