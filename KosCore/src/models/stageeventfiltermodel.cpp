#include "stageeventfiltermodel.h"

StageEventFilterModel::StageEventFilterModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void StageEventFilterModel::setEventFilterProvider(EventFilterProvider *eventFilterProvider)
{
    beginResetModel();
    m_eventFilterProvider = eventFilterProvider;
    endResetModel();
}


int StageEventFilterModel::rowCount(const QModelIndex &parent) const
{
    return m_eventFilterProvider ?
                m_eventFilterProvider->stageEventFilterList().size() :
                0;
}

int StageEventFilterModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant StageEventFilterModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                        case COL_FILTER_DESCR:
                        {
                            return tr("Checkpoint filter");
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

QVariant StageEventFilterModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !m_eventFilterProvider) {
        return QVariant();
    }

    const StageEventFilter* stage = m_eventFilterProvider->stageEventFilterList().at(index.row());

    switch(role) {
        case Qt::DisplayRole:
        {
            switch(index.column()) {
                case COL_TITLE:
                {
                    return stage->title();
                }
                case COL_FILTER_DESCR:
                {
                    return stage->eventFilter() ? stage->eventFilter()->fullDescription() : tr("none");
                }
            }
        }
    }

    return QVariant();
}

bool StageEventFilterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!m_eventFilterProvider) {
        return false;
    }

    StageEventFilter * stage = m_eventFilterProvider->stageEventFilterList().at(index.row());

    switch(index.column()) {
        case COL_TITLE:
        {
            m_eventFilterProvider->stageEventFilterList().at(index.row())->setTitle(value.toString());
        }
    }

    return true;
}

bool StageEventFilterModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(count <= 0 || !m_eventFilterProvider) {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);

    for(int i = 0; i < count; ++i) {
        StageEventFilter * stageEventFilter = new StageEventFilter();
        stageEventFilter->setTitle(tr("enter stage title ..."));
        m_eventFilterProvider->insertStageEventFilter(stageEventFilter, row + i);
    }

    endInsertRows();

    return true;
}

bool StageEventFilterModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(count <= 0 || !m_eventFilterProvider) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);

    for(int i = row; i < row + count; ++i) {
        StageEventFilter * stageEventFilter = m_eventFilterProvider->stageEventFilterList().at(row);
        m_eventFilterProvider->removeStageEventFilter(stageEventFilter);
    }

    endRemoveRows();

    return true;
}


Qt::ItemFlags StageEventFilterModel::flags(const QModelIndex &index) const
{
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}
