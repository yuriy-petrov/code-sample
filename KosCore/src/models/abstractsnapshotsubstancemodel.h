#ifndef ABSTRACTSNAPSHOTSUBSTANCEMODEL_H
#define ABSTRACTSNAPSHOTSUBSTANCEMODEL_H

#include "snapshottablemodel.h"
#include "KosTypes.h"

class AbstractSnapshotSubstanceModel : public SnapshotTableModel
{
    Q_OBJECT
public:
    explicit AbstractSnapshotSubstanceModel(QObject *parent = 0);

public:
    static QStringList substanceNames();
    static QString substanceName(KosTypes::SubstanceType substance);
    static KosTypes::SubstanceType substanceByName(const QString &name);

    // QAbstractItemModel interface
public:
    void setSnapshot(Snapshot *snapshot);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const = 0;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
    virtual int substanceColumn() const = 0;
    virtual QVariant newTypedValue() = 0;
    virtual KosTypes::SubstanceType substance(const Snapshot::Key& value) const = 0;
    virtual void setSubstance(const Snapshot::Key& value, KosTypes::SubstanceType substance) = 0;

private:
    static const QMap<KosTypes::SubstanceType, QString> m_SubstanceNamesMap;
};

#endif // ABSTRACTSNAPSHOTSUBSTANCEMODEL_H
