#ifndef CONDITIONSMODEL_H
#define CONDITIONSMODEL_H

#include "snapshottablemodel.h"

class ConditionsModel : public SnapshotTableModel
{
    Q_OBJECT
public:
    explicit ConditionsModel(QObject *parent = 0);

    bool checkConditions();

signals:
    void conditionsFullfilled(bool value);

    // QAbstractItemModel interface
public:
    void setSnapshot(Snapshot *snapshot);
    void setValues(const QList<Snapshot::Key> &values);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // CONDITIONSMODEL_H
