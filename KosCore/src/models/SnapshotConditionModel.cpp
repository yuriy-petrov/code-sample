#include "SnapshotConditionModel.h"

#include "SnapshotCondition.h"
#include "StringsKeys.h"
#include "modeltypeshelper.h"

SnapshotConditionModel::SnapshotConditionModel(QObject * parent) :
    QAbstractTableModel(parent),
    m_snapshotCondition(NULL)
{
    m_columnTitles.insert(SnapshotConditionModel::Column::Key, tr("Key"));
    m_columnTitles.insert(SnapshotConditionModel::Column::Type, tr("Type"));
    m_columnTitles.insert(SnapshotConditionModel::Column::ValueMin, tr("Value min"));
    m_columnTitles.insert(SnapshotConditionModel::Column::ValueMax, tr("Value max"));
    m_columnTitles.insert(SnapshotConditionModel::Column::Inverse, tr("Inverse"));
}

SnapshotConditionModel::~SnapshotConditionModel()
{
}

int SnapshotConditionModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_snapshotCondition ? m_snapshotCondition->conditions().size() : 0;
}

int SnapshotConditionModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_columnTitles.size();
}

QVariant SnapshotConditionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (orientation)
    {
        case Qt::Horizontal:
        {
            switch (role)
            {
                case Qt::DisplayRole:
                {
                    return m_columnTitles.value((SnapshotConditionModel::Column)section, tr("unknown"));
                }
            }
            break;
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant SnapshotConditionModel::data(const QModelIndex & index, int role) const
{
    if (index.isValid() || m_snapshotCondition)
    {
        SnapshotCondition::Condition condition = m_snapshotCondition->conditions()[index.row()];

        switch (role)
        {
            case Qt::DisplayRole:
            {
                switch (index.column())
                {
                    case SnapshotConditionModel::Column::Key:
                    {
                        return condition.key;
                    }
                    case SnapshotConditionModel::Column::Type:
                    {
                        return SnapshotCondition::typeToString(condition.type);
                    }
                    case SnapshotConditionModel::Column::ValueMin:
                    {
                        return Model::TypesHelper::toString(condition.key, condition.valueMin);
                    }
                    case SnapshotConditionModel::Column::ValueMax:
                    {
                        return Model::TypesHelper::toString(condition.key, condition.valueMax);
                    }
                    case SnapshotConditionModel::Column::Inverse:
                    {
                        return condition.inverse;
                    }
                }
                break;
            }
            case Qt::EditRole:
            {
                switch(index.column())
                {
                    case SnapshotConditionModel::Column::Key:
                    {
                        return QStringList()
                                << Model::ChartsValues::keys()
                                << Model::Purge::N2_PRESSURE
                                << Model::CellStack::Enable::keys()
                                   ;
                    }
                    case SnapshotConditionModel::Column::Type:
                    {
                        return SnapshotCondition::typeNames();
                    }
                    case SnapshotConditionModel::Column::ValueMin:
                    {
                        return condition.valueMin;
                    }
                    case SnapshotConditionModel::Column::ValueMax:
                    {
                        return condition.valueMax;
                    }
                    case SnapshotConditionModel::Column::Inverse:
                    {
                        return QStringList() << "false" << "true";
                    }
                }
                break;
            }
            case Model::TypesHelper::ModelKeyRole:
            {
                return condition.key;
            }
        }
    }

    return QVariant();
}

bool SnapshotConditionModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (m_snapshotCondition)
    {
        QList<SnapshotCondition::Condition> conditions = m_snapshotCondition->conditions();
        SnapshotCondition::Condition condition = conditions[index.row()];

        switch (index.column())
        {
            case SnapshotConditionModel::Column::Key:
            {
                QString oldKey = condition.key;
                condition.key = value.toString();

                if(!Model::TypesHelper::sameTypes(condition.key, oldKey)) {
                    condition.valueMin = Model::TypesHelper::initValue(condition.key);
                    condition.valueMax = condition.valueMin;
                }

                break;
            }
            case SnapshotConditionModel::Column::Type:
            {
                condition.type = SnapshotCondition::stringToType(value.toString());
                break;
            }
            case SnapshotConditionModel::Column::ValueMin:
            {
                condition.valueMin = value;
                break;
            }
            case SnapshotConditionModel::Column::ValueMax:
            {
                condition.valueMax = value;
                break;
            }
            case SnapshotConditionModel::Column::Inverse:
            {
                condition.inverse = value.toBool();
                break;
            }
        }

        conditions[index.row()] = condition;
        m_snapshotCondition->setConditions(conditions);
        return true;
    }

    return false;
}

bool SnapshotConditionModel::insertRows(int row, int count, const QModelIndex & parent)
{
    if (count <= 0 || !m_snapshotCondition)
    {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);
    QList<SnapshotCondition::Condition> conditions = m_snapshotCondition->conditions();
    for (int i = 0; i < count; ++i)
    {
        SnapshotCondition::Condition condition;
        conditions.insert(row + i, condition);
    }
    m_snapshotCondition->setConditions(conditions);
    endInsertRows();
    return true;
}

bool SnapshotConditionModel::removeRows(int row, int count, const QModelIndex & parent)
{
    if (count <= 0 || !m_snapshotCondition)
    {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    QList<SnapshotCondition::Condition> conditions = m_snapshotCondition->conditions();
    for (int i = row; i < row + count; ++i)
    {
        conditions.removeAt(row);
    }
    m_snapshotCondition->setConditions(conditions);
    endRemoveRows();
    return true;
}

Qt::ItemFlags SnapshotConditionModel::flags(const QModelIndex & index) const
{
    Q_UNUSED( index )

    SnapshotCondition::Condition condition = m_snapshotCondition->conditions()[index.row()];

    switch(condition.type) {
        case SnapshotCondition::Condition::Range:
        {
            return
                    Qt::ItemIsEnabled |
                    Qt::ItemIsSelectable |
                    Qt::ItemIsEditable;
        }
        case SnapshotCondition::Condition::Equality:
        {
            return
                    index.column() == ValueMax ?
                        Qt::NoItemFlags
                      :
                        Qt::ItemIsEnabled |
                        Qt::ItemIsSelectable |
                        Qt::ItemIsEditable;
        }
    }
}

SnapshotCondition * SnapshotConditionModel::snapshotCondition() const
{
    return m_snapshotCondition;
}

void SnapshotConditionModel::setSnapshotCondition(SnapshotCondition * snapshotCondition)
{
    beginResetModel();
    m_snapshotCondition = snapshotCondition;
    endResetModel();
}
