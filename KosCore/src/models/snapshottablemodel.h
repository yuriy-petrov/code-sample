#ifndef SNAPSHOTTABLEMODEL_H
#define SNAPSHOTTABLEMODEL_H

#include <QAbstractTableModel>
#include <snapshot.h>

class SnapshotTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum { COL_VALUE };

public:
    explicit SnapshotTableModel(QObject *parent = 0);

    virtual void setSnapshot(Snapshot* snapshot);
    virtual void setValues(const QList<Snapshot::Key>& values);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
    Snapshot* m_Snapshot;
    QList<Snapshot::Key> m_Values;
};

#endif // SNAPSHOTTABLEMODEL_H
