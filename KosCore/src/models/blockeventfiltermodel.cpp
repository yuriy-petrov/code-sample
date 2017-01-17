#include "blockeventfiltermodel.h"

BlockEventFilterModel::BlockEventFilterModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void BlockEventFilterModel::setStageEventFilter(StageEventFilter *stageEventFilter)
{
    beginResetModel();
    m_stageEventFilter = stageEventFilter;
    endResetModel();
}

int BlockEventFilterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )

    return m_stageEventFilter ?
                m_stageEventFilter->blockEventFilterList().size() :
                0;
}

int BlockEventFilterModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant BlockEventFilterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation) {
    case Qt::Horizontal:
    {
        switch(role) {
        case Qt::DisplayRole:
        {
            switch(section) {
            case COL_TITLE:
            {
                return tr("Title");
            }
            case COL_OPERATION:
            {
                return tr("Operation");
            }
            case COL_TIME_INTERVAL_TYPE:
            {
                return tr("Time interval type");
            }
            case COL_TIME_INTERVAL:
            {
                return tr("Time interval");
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

    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant BlockEventFilterModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !m_stageEventFilter) {
        return QVariant();
    }

    const BlockEventFilter * blockEventFilter = m_stageEventFilter->blockEventFilterList().at(index.row());

    switch(role) {
        case Qt::DisplayRole:
        {
            switch(index.column())
            {
                case COL_TITLE:
                {
                    return blockEventFilter->title();
                }
                case COL_OPERATION:
                {
                    return blockEventFilter->logicTypeName();
                }
                case COL_TIME_INTERVAL_TYPE:
                {
                    switch (blockEventFilter->timeIntervalType())
                    {
                        case BlockEventFilter::TimeIntervalType::Ignore: return tr("ignore");
                        case BlockEventFilter::TimeIntervalType::More: return tr(">");
                        case BlockEventFilter::TimeIntervalType::Less: return tr("<");
                        default: return tr("unknown");
                    }
                }
                case COL_TIME_INTERVAL:
                {
                    return blockEventFilter->timeInterval();
                }
            }

            break;
        }
        case Qt::EditRole:
        {
            switch(index.column())
            {
                case COL_OPERATION:
                {
                    return QStringList(blockEventFilter->logicTypeNames().values());
                }
                case COL_TIME_INTERVAL_TYPE:
                {
                    return QStringList(blockEventFilter->timeIntervalTypeNames().values());
                }
            }

            break;
        }
    }

    return QVariant();
}

bool BlockEventFilterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!m_stageEventFilter) {
        return false;
    }

    BlockEventFilter * blockEventFilter = m_stageEventFilter->blockEventFilterList().at(index.row());

    switch(index.column()) {
        case COL_TITLE:
        {
            blockEventFilter->setTitle(value.toString());
            break;
        }
        case COL_OPERATION:
        {
            blockEventFilter->setLogicType(BlockEventFilter::logicTypeNames().key(value.toString()));
            break;
        }
        case COL_TIME_INTERVAL_TYPE:
        {
            blockEventFilter->setTimeIntervalType(BlockEventFilter::timeIntervalTypeNames().key(value.toString()));
            break;
        }
        case COL_TIME_INTERVAL:
        {
            bool ok = false;
            int timeInterval = value.toInt(&ok);
            if (ok)
            {
                blockEventFilter->setTimeInterval(timeInterval);
            }
        }
    }

    return true;
}

bool BlockEventFilterModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(count <= 0 || !m_stageEventFilter) {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);

    for(int i = 0; i < count; ++i) {
        BlockEventFilter * blockEventFilter = new BlockEventFilter();
        blockEventFilter->setTitle(tr("enter block title ..."));
        m_stageEventFilter->insertBlockEventFilter(blockEventFilter, row + i);
    }

    endInsertRows();

    return true;
}

bool BlockEventFilterModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(count <= 0 || !m_stageEventFilter) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);

    for(int i = row; i < row + count; ++i) {
        BlockEventFilter * blockEventFilter = m_stageEventFilter->blockEventFilterList().at(row);
        m_stageEventFilter->removeBlockEventFilter(blockEventFilter);
    }

    endRemoveRows();

    return true;
}

Qt::ItemFlags BlockEventFilterModel::flags(const QModelIndex &index) const
{
    Q_UNUSED( index )

    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}
