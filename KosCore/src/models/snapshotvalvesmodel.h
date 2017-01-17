#ifndef SNAPSHOTVALVESMODEL_H
#define SNAPSHOTVALVESMODEL_H

#include "snapshottablemodel.h"

class SnapshotValvesModel : public SnapshotTableModel
{
    Q_OBJECT

public:
    enum {
        COL_POSITION,
        COL_CLOSING_LEVEL,
        COL_STATUS
    };

public:
    explicit SnapshotValvesModel(QObject *parent = 0);

    // QAbstractItemModel interface
public:
    void setSnapshot(Snapshot *snapshot);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // SNAPSHOTVALVESMODEL_H
