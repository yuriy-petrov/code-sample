#include "eventfiltermodel.h"

#include <SchemeEventFilter.h>

EventFilterModel::EventFilterModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void EventFilterModel::setBlockEventFilter(BlockEventFilter *blockEventFilter)
{
    beginResetModel();
    m_blockEventFilter = blockEventFilter;
    endResetModel();
}

int EventFilterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )

    return m_blockEventFilter ?
                m_blockEventFilter->eventFilterList().size() :
                0;
}

int EventFilterModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant EventFilterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(orientation) {
        case Qt::Horizontal:
        {
            switch(role) {
                case Qt::DisplayRole:
                {
                    switch(section) {
                        case COL_FILTER_DESCR:
                        {
                            return tr("Description");
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

QVariant EventFilterModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !m_blockEventFilter) {
        return QVariant();
    }

    const AbstractEventFilter * eventFilter = m_blockEventFilter->eventFilterList().at(index.row());

    switch(role) {
        case Qt::DisplayRole:
        {
            switch(index.column()) {
                case COL_FILTER_DESCR:
                {
                    return eventFilter->fullDescription();
                }
            }
        }
    }

    return QVariant();
}

bool EventFilterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!m_blockEventFilter) {
        return false;
    }

    AbstractEventFilter * eventFilter = m_blockEventFilter->eventFilterList().at(index.row());

    return true;
}

bool EventFilterModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(count <= 0 || !m_blockEventFilter) {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);

    for(int i = 0; i < count; ++i) {
        AbstractEventFilter * filter = new SchemeEventFilter();
        filter->setTitle(tr("enter filter name ..."));
        m_blockEventFilter->insertEventFilter(filter, row + i);
    }

    endInsertRows();

    return true;
}

bool EventFilterModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(count <= 0 || !m_blockEventFilter) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);

    for(int i = row; i < row + count; ++i) {
        AbstractEventFilter * filter = m_blockEventFilter->eventFilterList().at(row);
        m_blockEventFilter->removeEventFilter(filter);
    }

    endRemoveRows();

    return true;
}

Qt::ItemFlags EventFilterModel::flags(const QModelIndex &index) const
{
    Q_UNUSED( index )
    return
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsEditable;
}
