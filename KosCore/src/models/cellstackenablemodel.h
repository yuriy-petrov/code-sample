#ifndef CELLSTACKSENABLEMODEL_H
#define CELLSTACKSENABLEMODEL_H

#include <snapshottablemodel.h>

class CellStackEnableModel : public SnapshotTableModel
{
    Q_OBJECT
public:
    explicit CellStackEnableModel(QObject *parent = 0);


    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // CELLSTACKSENABLEMODEL_H
