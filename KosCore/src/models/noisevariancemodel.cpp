#include <StringsKeys.h>

#include "noisevariancemodel.h"

NoiseVarianceModel::NoiseVarianceModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_EditableValues(Model::noiseableKeys())
{
    qSort(m_EditableValues);
}

void NoiseVarianceModel::setNoiseVariance(const Model::NoiseVariance &nv)
{
    beginResetModel();
    m_NoiseVariance = nv;
    m_Values = m_NoiseVariance.keys();
    qSort(m_Values);
    endResetModel();
}

Model::NoiseVariance NoiseVarianceModel::noiseVariance() const
{
    return m_NoiseVariance;
}

bool NoiseVarianceModel::isFull() const
{
    return m_Values.size() == m_EditableValues.size();
}

QStringList NoiseVarianceModel::woNoiseValues() const
{
    QStringList keys = m_EditableValues;
    foreach(const Model::NoiseVariance::key_type& key, m_Values) {
        keys.removeOne(key);
    }
    return keys;
}


int NoiseVarianceModel::rowCount(const QModelIndex &parent) const
{
    return m_Values.size();
}

int NoiseVarianceModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant NoiseVarianceModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const Model::NoiseVariance::key_type& value = m_Values.at(index.row());

    switch(index.column()) {
    case COL_VALUE:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            return value;
        }
        case Qt::EditRole:
        {
            return woNoiseValues() << value;
        }
        default:
        {
            break;
        }
        }

        break;
    }
    case COL_VARIANCE:
    {
        switch(role) {
        case Qt::EditRole:
        case Qt::DisplayRole:
        {
            return m_NoiseVariance.value(value);
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

bool NoiseVarianceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(index.column()) {
    case COL_VALUE:
    {
        double variance = m_NoiseVariance.value(m_Values.at(index.row()));
        m_NoiseVariance.remove(m_Values.at(index.row()));
        m_NoiseVariance.insert(value.toString(), variance);
        m_Values.removeAt(index.row());
        m_Values.insert(index.row(), value.toString());
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
        return true;
    }
    case COL_VARIANCE:
    {
        bool isOk;
        double val = value.toDouble(&isOk);

        if(!isOk) {
            return false;
        }

        m_NoiseVariance.insert(m_Values.at(index.row()), val);
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);

        return true;
    }
    }

    return false;
}

QVariant NoiseVarianceModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            case COL_VARIANCE:
            {
                return tr("Variance");
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

Qt::ItemFlags NoiseVarianceModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}


bool NoiseVarianceModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginResetModel();

    for(int i = 0; i < count; ++i) {
        if(woNoiseValues().isEmpty()) {
            break;
        }
        m_Values << woNoiseValues().first();
        m_NoiseVariance.insert(m_Values.last(), 0.001);
    }

    endResetModel();
}

bool NoiseVarianceModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginResetModel();

    for(int i = 0; i < count; ++i) {
        m_NoiseVariance.remove(m_Values.at(row));
        m_Values.removeAt(row);
    }

    endResetModel();
}
