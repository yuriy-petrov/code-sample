#ifndef SNAPSHOTCONDITIONMODEL_H
#define SNAPSHOTCONDITIONMODEL_H

class SnapshotCondition;

#include <QAbstractTableModel>

class SnapshotConditionModel : public QAbstractTableModel
{

public:

    enum Column
    {
        Key = 0,
        Type,
        ValueMin,
        ValueMax,
        Inverse
    };

    SnapshotConditionModel(QObject * parent = 0);
    ~SnapshotConditionModel();

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QVariant data(const QModelIndex & index, int role) const;
    virtual bool setData(const QModelIndex & index, const QVariant &value, int role);
    virtual bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
    virtual Qt::ItemFlags flags(const QModelIndex & index) const;

    SnapshotCondition * snapshotCondition() const;
    void setSnapshotCondition(SnapshotCondition * snapshotCondition);

private:

    SnapshotCondition * m_snapshotCondition;
    QHash<Column,QString> m_columnTitles;
};

#endif // SNAPSHOTCONDITIONMODEL_H
