#ifndef SNAPSHOTSEPARATORSMODEL_H
#define SNAPSHOTSEPARATORSMODEL_H

#include "snapshottablemodel.h"

class SnapshotSeparatorsModel : public SnapshotTableModel
{
    Q_OBJECT

public:
    enum { COL_GAS_SUBSTANCE, COL_FLUID_SUBSTANCE, COL_FLUID_LEVEL };

public:
    explicit SnapshotSeparatorsModel(QObject *parent = 0);

    // QAbstractItemModel interface
public:
    void setSnapshot(Snapshot *snapshot);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // SNAPSHOTSEPARATORSMODEL_H
