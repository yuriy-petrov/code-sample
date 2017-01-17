#ifndef EVENTFILTERMODEL_H
#define EVENTFILTERMODEL_H

#include <QAbstractListModel>

#include <BlockEventFilter.h>

class EventFilterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum { COL_FILTER_DESCR };

public:
    explicit EventFilterModel(QObject *parent = 0);

    void setBlockEventFilter(BlockEventFilter * blockEventFilter);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    BlockEventFilter * m_blockEventFilter;
};

#endif // EVENTFILTERMODEL_H
