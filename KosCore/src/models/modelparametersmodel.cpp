#include "modelparametersmodel.h"

ModelParametersModel::ModelParametersModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void ModelParametersModel::setKeys(const QStringList &keys)
{
    beginResetModel();

    m_Keys = keys;

    foreach(const QString& key, m_Keys) {
        if(!m_Parameters.contains(key)) {
            m_Parameters.insert(key, 0.0);
        }
    }

    endResetModel();
}

void ModelParametersModel::setParameters(const Model::Parameters::Type &parameters)
{
    beginResetModel();
    m_Parameters = parameters;
    endResetModel();
}


int ModelParametersModel::rowCount(const QModelIndex &parent) const
{
    return size();
}

int ModelParametersModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant ModelParametersModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const Model::Parameters::Type::key_type& valueKey = key(index.row());

    switch(index.column()) {
    case COL_VALUE:
    {
        switch(role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            return m_Parameters[valueKey];
        }
        default: break;
        }

        break;
    }
    }

    return QVariant();
}

bool ModelParametersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole) {
        switch(index.column()) {
        case COL_VALUE:
        {
            const QString& valueKey = key(index.row());
            m_Parameters.remove(valueKey);
            m_Parameters.insert(valueKey, value.toDouble());
            emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
            return true;
        }
        }
    }

    return false;
}

QVariant ModelParametersModel::headerData(int section, Qt::Orientation orientation, int role) const
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
        default : break;
        }

        break;
    }
    case Qt::Vertical:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
        return key(section);
        }
        default : break;
        }
    }
    }

    return QVariant();
}

Qt::ItemFlags ModelParametersModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}

int ModelParametersModel::size() const
{
    return m_Keys.isEmpty() ?
                m_Parameters.size() :
                m_Keys.size();
}

const QString& ModelParametersModel::key(int row) const
{
    return m_Keys.isEmpty() ?
                m_Parameters.keys().at(row) :
                m_Keys.at(row);
}
