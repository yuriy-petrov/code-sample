#ifndef BLOCKEVENTFILTERMODEL_H
#define BLOCKEVENTFILTERMODEL_H

#include <QAbstractListModel>

#include <StageEventFilter.h>

class BlockEventFilterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum { COL_TITLE = 0, COL_OPERATION = 1, COL_TIME_INTERVAL_TYPE = 2, COL_TIME_INTERVAL = 3};

public:
    explicit BlockEventFilterModel(QObject *parent = 0);

    void setStageEventFilter(StageEventFilter * stageEventFilter);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    StageEventFilter * m_stageEventFilter;
};

#endif // BLOCKEVENTFILTERMODEL_H
