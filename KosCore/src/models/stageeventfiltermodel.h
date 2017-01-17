#ifndef STAGEEVENTFILTERMODEL_H
#define STAGEEVENTFILTERMODEL_H

#include <QAbstractListModel>

#include <EventFilterProvider.h>

class StageEventFilterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum { COL_TITLE, COL_FILTER_DESCR };

public:
    explicit StageEventFilterModel(QObject *parent = 0);

    void setEventFilterProvider(EventFilterProvider * eventFilterProvider);

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
    EventFilterProvider * m_eventFilterProvider;
};

#endif // STAGEEVENTFILTERMODEL_H
